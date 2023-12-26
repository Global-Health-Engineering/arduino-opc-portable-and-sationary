/*
Stage I - v0-9-0

For Arduino UNO R3, Alphasense OPC-N3 (OPC) and Adafruit Data Logger Shield Rev C (DLS) with included real-time clock (RTC).
Measurement mode: continuous operation of the OPC with a reading every MeasurementInterval (1-5 seconds)

- OPC-N3 part adapted from Alphasense example code.

Diagnostic LEDs:

- solid green LED: sensor is running normally (main loop)
- solid red LED: sensor is starting up (setup function)
- flashing red LED: error has occured, check that everything is plugged in correctly and reset the Arduino
*/


#include <SPI.h>
#include <SD.h>
#include <RTClib.h>


#define SPI_OPC_busy 0x31 // Indicates that OPC is busy
#define SPI_OPC_ready 0xF3 // Indicates that OPC is ready for SPI communication

// Pins used for SPI communication with OPC and DLS
#define SPI_SCK 13 // SPI Clock
#define SPI_SDI 12 // SDI (= MISO)
#define SPI_SDO 11 // SDO (= MOSI)

#define SPI_OPC_CS 9 // ChipSelect pin for OPC
#define SPI_DLS_CS 10 // ChipSelect pin for DLS

// Pins for diagnostic LEDs on DLS
#define GreenLED 3
#define RedLED 4


struct OPCData // Struct containing OPC histogram data
{
  String MeasDate; // Date of measurement
  String MeasTime; // Time of measurement

  unsigned int BinCounts[24]; // Sample counts for each of the 24 bins

  float SamplingPeriod; // Sampling Period in (s)
  float SampleFlowRate; // Sample Flow Rate in (ml/s)
  float Temperature; // Temperature in (°C)
  float Humidity; // Relative Humidity in (%)

  float PMA; // PM_A = PM_1 in (ug/m^3) --CHECK
  float PMB; // PM_B = PM_2.5 in (ug/m^3) --CHECK 
  float PMC; // PM_C = PM_10 in (ug/m^3) --CHECK

  unsigned int LaserStatus; // Status of the laser, 550 < LaserStatus < 650 during normal operation

  unsigned int Checksum; // Checksum sent by the sensor
  bool CheckMatch; // 0 = Checksums don't match, 1 = Checksums match
};

unsigned int MeasurementInterval = 10000; // Measurement interval in (ms)
unsigned long CurrentTime;
unsigned long IsItTime; // Time of next measurement

unsigned char SPI_Buffer[86]; // SPI communication buffer
unsigned int SPI_Buffer_Index; // Index of SPI communication buffer

bool FirstHist = true;

OPCData Data;
String Filename;
File DataFile; // The output file

RTC_PCF8523 RTC; // Older revisions of the DLS use a different RTC!
DateTime Now;


void (* ResetFunc) (void) = 0; // This resets the Arduino as if the Reset button was pressed


void setup()
{
  delay (2000);

  // Initiate LED pins
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  SetLED(GreenLED, LOW);
  SetLED(RedLED, HIGH);

  // Set ChipSelect pins of OPC and DLS to output and set HIGH
  pinMode(SPI_OPC_CS, OUTPUT);
  pinMode(SPI_DLS_CS, OUTPUT);
  SetCSpin(SPI_OPC_CS, HIGH);
  SetCSpin(SPI_DLS_CS, HIGH); 

  delay(2000); // Delay in case of noisy power supply

  SPI.begin(); // Enable SPI

  // Initialise devices
  StartRTC();
  StartSD();
  CreateSDFile();
  StartOPC();
  
  // Check if OPC is running normally
  Data = ReadOPCdata();
  if (Data.LaserStatus < 550)
  {
    HardError();
  }

  CurrentTime = millis();
  IsItTime = CurrentTime;

  SetLED(GreenLED, HIGH);
  SetLED(RedLED, LOW);
}


void loop() // Main loop
{
  // The main loop does the following:
  // Check if MeasurementInterval time has passed since the last sensor reading
  // If so, get a histogram from the OPC
  // Save the histogram with a timestamp to the SD card (the first histogram is not saved as this contains nonsense data)
  // Repeat every MeasurementInterval

  CurrentTime = millis();

  if (CurrentTime >= IsItTime) // Check if MeasurementInterval has passed since last sensor reading
  {
    IsItTime += MeasurementInterval;

    Data = ReadOPCdata(); // Read a histogram from OPC

    if (FirstHist != true) // Save the data to SD card except if it is the first one (this contains nonsense data)
    {
      SaveSDData(); // Save the current data to the SD card
    }
    else
    {
      FirstHist = false;
    }
  }
}


OPCData ReadOPCdata (void) // Read a histogram from OPC
{
  OPCData newData;
  Now = RTC.now();

  // Read histogram from OPC to SPI_Buffer
  GetReadyResponseOPC(0x30);
  for (SPI_Buffer_Index = 0; SPI_Buffer_Index < 86; SPI_Buffer_Index++)
  {
    delayMicroseconds(10);
    SPI_Buffer[SPI_Buffer_Index] = SPI.transfer(0x01); // Value of outgoing byte doesn't matter
  }
  SetCSpin(SPI_OPC_CS, HIGH);
  SPI.endTransaction();
  delay(10);

  //Transfer data from SPI_Buffer to newData
  unsigned int BufferIndex; // Index for iterating over SPI_Buffer
  unsigned int BinIndex = 0; // Index for iterating over the BinCounts in newData struct
  unsigned int *pUInt16; // Pointer for 16 bit unsigned int values
  float *pFloat; // Pointer for float values

  char DateFormat[] = "YYYY-MM-DD";
  char TimeFormat[] = "hh:mm:ss";

  newData.MeasDate = Now.toString(DateFormat);
  newData.MeasTime = Now.toString(TimeFormat);

  // Bin counts
  for (BufferIndex = 0; BufferIndex < 48; BufferIndex += 2) // Transfer the bin counts from SPI_Buffer to newData
  {
    pUInt16 = (unsigned int *)&SPI_Buffer[BufferIndex];
    newData.BinCounts[BinIndex] = *pUInt16;

    BinIndex++;
  }

  // Sampling Period
  pUInt16 = (unsigned int *)&SPI_Buffer[52];
  newData.SamplingPeriod = (float)*pUInt16/100; // --TODO check 3dp
  // Sample Flow Rate
  pUInt16 = (unsigned int *)&SPI_Buffer[54];
  newData.SampleFlowRate = (float)*pUInt16/100; // --TODO check 3dp
  // Temperature
  pUInt16 = (unsigned int *)&SPI_Buffer[56];
  newData.Temperature = TemperatureCalc(*pUInt16); // --TODO check 3dp
  // Relative Humidity
  pUInt16 = (unsigned int *)&SPI_Buffer[58];
  newData.Humidity = RelativeHumidityCalc(*pUInt16); // --TODO check 3dp

  // PM_A
  pFloat = (float *)&SPI_Buffer[60];
  newData.PMA = *pFloat; // --TODO check 3dp
  // PM_B
  pFloat = (float *)&SPI_Buffer[64];
  newData.PMB = *pFloat; // --TODO check 3dp
  // PM_C
  pFloat = (float *)&SPI_Buffer[68];
  newData.PMC = *pFloat; // --TODO check 3dp

  pUInt16 = (unsigned int *)&SPI_Buffer[82];
  newData.LaserStatus = *pUInt16;

  // Checksum
  pUInt16 = (unsigned int *)&SPI_Buffer[84];
  newData.Checksum = *pUInt16;

  if(*pUInt16 == ChecksumCalc(SPI_Buffer, 84)) // Compare the received checksum with the calculated one
  {
    newData.CheckMatch = true;
  }
  else
  {
    newData.CheckMatch = false;
  }

  return newData;
}


float TemperatureCalc (unsigned int OPCT) // Convert SHT31 ST output to Temperature (C)
{
  return -45 + 175*(float)OPCT/65535;
}


float RelativeHumidityCalc (unsigned int OPCRH) // Convert SHT31 SRH output to Telative Humidity (%)
{
  return 100*(float)OPCRH/65535;
}


void SaveSDData (void) // Save data including timestamp to SD card
{
  if (SD.exists(Filename)) // Check if SD card is present and file exists
  {
    DataFile = SD.open(Filename, FILE_WRITE); // Open file
    if (DataFile)
    {
      //DataFile.print(Data.Timestamp); // Write Timestamp to file
      //AddComma(DataFile);
      
      DataFile.print(Data.MeasDate);
      AddComma(DataFile);
      DataFile.print(Data.MeasTime);
      AddComma(DataFile);
      

      for (int i = 0; i < 24; i++) // Write BinCounts to file
      {
        DataFile.print(Data.BinCounts[i]);
        AddComma(DataFile);
      }
  
      // --TODO File.writer OR File.print?!
      DataFile.print(Data.SamplingPeriod) ; // Write Sampling Period to file with 3 decimal places --TODO check 3dp
      AddComma(DataFile);
      DataFile.print(Data.SampleFlowRate); // Write Sample Flow Fate to file with 3 decimal places --TODO check 3dp
      AddComma(DataFile);
      DataFile.print(Data.Temperature) ; // Write Temperature to file with 1 decimal place --TODO check 1dp
      AddComma(DataFile);
      DataFile.print(Data.Humidity); // Write Relative Humidity to file with 1 decimal place --TODO check 1dp
      AddComma(DataFile);

      DataFile.print(Data.PMA); // Write PM_A to file --TODO check 3dp
      AddComma(DataFile);
      DataFile.print(Data.PMB); // Write PM_B to file --TODO check 3dp
      AddComma(DataFile);
      DataFile.print(Data.PMC); // Write PM_C to file --TODO check 3dp
      AddComma(DataFile);

      DataFile.print(Data.Checksum); // Write Checksum sent by OPC to file
      AddComma(DataFile);
      DataFile.print(Data.CheckMatch); // Write Checksum match to file

      DataFile.println(); // Add new line to file
      DataFile.close(); // Close file
    }
    else
    {
    HardError(); // --TODO ask and potentially change to SoftError loop
    }
  }
  else
  {
    HardError(); // --TODO ask and potentially change to SoftError loop
  }
}


void StartOPC (void) // Start OPC --TODO add check/retry to ensure OPC is properly running before returning
{
  // Laser power ON
  GetReadyResponseOPC(0x03);
  SPI.transfer(0x07); // Turn ON laser power
  SetCSpin(SPI_OPC_CS, HIGH);
  SPI.endTransaction();
  delay(10);

  delay(1000); // Delay may be necessary to seperate power ON of fan and laser

  // Fan DAC ON
  GetReadyResponseOPC(0x03);
  SPI.transfer(0x03); // Turn ON fan DAC
  SetCSpin(SPI_OPC_CS, HIGH);
  SPI.endTransaction();
  delay(10);

  // Wait for fan to reach full speed (and for multiple attempts by OPC firmware to turn on fan)
  for (byte i = 0; i < 5; i++)
  {
    delay(1000);
  }
}


void StartRTC (void) // Start RTC, no calibration
{
  while (! RTC.begin()) // Try starting communication with RTC
  {
    // Add orange? status LED --TODO
    delay(10); // Wait until the RTC has started
  }

  delay(2000); // Wait 2 seconds for PCF8523's crystal oscillator to stabilise before trying to adjust

  //RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC time to current system time (make sure this is set correctly!) -ONLY LEAVE THIS ENABLED WHEN RUNNING THE SENSOR UNIT FROM A PC-

  RTC.start(); // Clear stop bit of RTC
}


void StartSD (void) // Start SPI communication with SD card --TODO rework
{ 
  while (!SD.begin(SPI_DLS_CS)) // Try starting the SD card
  {
    HardError(); // --TODO ask and potentially change to SoftError loop
  }
}


void CreateSDFile (void) // Create file on SD card with name Filename and write file header
{
  Now = RTC.now();
  String FileExtension = F(".csv"); // File extension, .csv or .txt
  Filename = (Now.toString("DDhhmmss") + FileExtension); // Name of file is DDHHMMSS.EXT

  if (SD.exists(Filename)) // Stop if file with name Filename already exists, this prevents the overwriting of data
  {
    HardError();
  }

  DataFile = SD.open(Filename, FILE_WRITE); // Open file
  if (DataFile) // Write file header to file
  {
    DataFile.print(F("date,time")); // Header Timestamp

    for (int i = 0; i < 24; i++) // Header for Bins
    {
      DataFile.print(F(",bin"));
      if (i < 10) DataFile.print(F("0")); // Leading 0 for single digit Bins
      DataFile.print(i, DEC);
    }

    DataFile.println(F(",SP(s),SFR(ml/s),T(C),RH(%),PM_A(ug/m^3),PM_B(ug/m^3),PM_C(ug/m^3),checksum,cs_match")); // Header for other columns

    DataFile.close(); // Close file
  }
  else // Halt if file could not be created or opened
  {
    HardError();
  }
}


void GetReadyResponseOPC (unsigned char SPIcommand) // Check if OPC is ready for SPI communication --TODO rework
{
  unsigned char Response;

  SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE1)); // Set SPI mode

  // Try reading a byte here to clear out anything remnant of SD card SPI activity
  Response = SPI.transfer(SPIcommand);
  delay(1);

  do
  {
    SetCSpin(SPI_OPC_CS, LOW);
    unsigned char Tries = 0;
    do
    {
      Response = SPI.transfer(SPIcommand);
      if (Response != SPI_OPC_ready) delay(1);
    }
    while ((Tries++ < 20) && (Response != SPI_OPC_ready));

    if (Response != SPI_OPC_ready)
    {
      if (Response == SPI_OPC_busy)
      {
        SetCSpin(SPI_OPC_CS, HIGH);
        delay(2000);
      }
      else
      {
        // End SPI and wait a few seconds for it to be cleared
        SetCSpin(SPI_OPC_CS, HIGH);
        SPI.endTransaction();
        delay(6000); // Wait 6 s here for buffer to be cleared
        SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE1));
      }
    }
  }
  while ((Response != SPI_OPC_ready) && (Serial.available() == 0)); // Don't hang on this if SPI data is being received
  delay(10);
}


unsigned int ChecksumCalc (unsigned char SPI_Data[], unsigned char DataBytes) // Calculate checksum from received data --TODO add comments
{
  #define Polynom 0xA001
  #define InitVal 0xFFFF

  unsigned char _bit;
  unsigned int Checksum = InitVal;
  unsigned char Count;

  for(Count = 0; Count < DataBytes; Count++)
  {
    Checksum ^= (unsigned int)SPI_Data[Count];
    for(_bit = 0; _bit < 8; _bit++)
    {
      if (Checksum & 1)
      {
        Checksum >>= 1;
        Checksum ^= Polynom;
      }
      else
        Checksum >>= 1;
    }
  }
  return Checksum;
}


void AddComma (File OutFile) // Print comma to OutFile (seperator for columns)
{
  OutFile.print(F(","));
}


void SetCSpin (int Pin, bool PinState) // Set ChipSelect Pin to PinState, PinState is HIGH or LOW
{
  digitalWrite(Pin, PinState);
}


void SetLED (int Pin, bool PinState) // Set LED Pin to PinState, PinState is HIGH or LOW
{
  digitalWrite(Pin, PinState);
}


void HardError (void) // Flash the red LED and halt until Arduino is reset -TODO add check for open file and close AND stop OPC (turn off fan and laser)
{
  while (1)
  {
    SetLED(GreenLED, LOW);
    SetLED(RedLED, HIGH);
    delay(500); 
    SetLED(RedLED, LOW);
    delay(500);
  }
}

