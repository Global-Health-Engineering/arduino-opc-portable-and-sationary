/* --------------------
Portable
v1-0-0

Code for the Arduino of the portable monitor. Check the README file for documentation.
-------------------- */


/* -------- Libraries & definitions -------- */


#include <SPI.h> // CHECK LICENSE
#include <SD.h> // CHECK LICENSE
#include <RTClib.h> // CHECK LICENSE

// Pins for SPI
#define SPI_SCK 13 // Clock
#define SPI_SDI 12 // SDI
#define SPI_SDO 11 // SDO

// SPI chipselect pins
#define SPI_OPC_CS 9
#define SPI_DLS_CS 10

// OPC status bytes
#define OPC_busy 0x31
#define OPC_ready 0xF3

// Pins for external status LEDs
#define GreenLED 3
#define RedLED 4


/* -------- User parameters -------- */


unsigned int MeasInterval = 10000; // Measurement interval in (ms)
unsigned long Timeout = 1000; // Timeout in (ms)

String FileExtension = ".csv"; // File extension of the local save file (.csv or .txt)


/* -------- Variables -------- */


struct OPCData // Struct for storing the data from the OPC
{
  String MeasDate;
  String MeasTime;

  uint16_t BinCount[24];

  float SamplingPeriod;
  float SampleFlowRate;
  float Temperature;
  float Humidity;

  float PMA;
  float PMB;
  float PMC;

  uint16_t LaserStatus; // Laser status of the OPC, 550 < LaserStatus < 650 during normal operation

  uint16_t ChecksumReceived;
  uint16_t ChecksumCalculated;
  bool ChecksumMatch;
};

// SPI buffer for reading data from the OPC.
unsigned char SPI_Buffer[86];
unsigned int SPI_Buffer_Index;

unsigned long CurrentTime;
unsigned long NextMeas;

unsigned long RetryTimer = 0;

bool FirstMeas; // Used to discard the first set of measurements


RTC_PCF8523 RTC;
DateTime Now;

String Filename;

OPCData Data;


/* -------- Setup -------- */


void setup()
{
  Serial.begin(9600);

  delay(2000);

  // Configure LED pins
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  SetLED(GreenLED, LOW);
  SetLED(RedLED, HIGH);

  // Configure SPI CS pins
  pinMode(SPI_OPC_CS, OUTPUT);
  pinMode(SPI_DLS_CS, OUTPUT);
  SetCS(SPI_OPC_CS, HIGH);
  SetCS(SPI_DLS_CS, HIGH); 

  delay(2000);

  SPI.begin();

  // Start all devices
  StartRTC();
  Serial.println("RTC started!");
  StartSD();
  Serial.println("SD started!");
  CreateSDFile();
  Serial.println("SD file started!");
  StartOPC();
  Serial.println("OPC started!");

  CurrentTime = millis();
  NextMeas = CurrentTime;

  SetLED(GreenLED, HIGH);
  delay(1000);
  SetLED(RedLED, LOW);
}


/* -------- Main loop -------- */


void loop()
{
  CurrentTime = millis();

  if (CurrentTime >= NextMeas)
  {
    NextMeas = CurrentTime + MeasInterval;

    Data = ReadOPCData();

    if (FirstMeas == false)
    {
      SaveSDData(Data, Filename);
    }
    else
    {
      FirstMeas == false;
    }
  }

}


/* -------- RTC functions -------- */


void StartRTC (void) // Start the RTC.
{
  RetryTimer = 0; // Reset the timeout timer to 0.

  while (!RTC.begin()) // Try starting the RTC.
  {
    RetryTimer += 200; // Increase the timeout timer.

    if (RetryTimer >= Timeout) // Error out if the RTC doesn't start within Timeout (if this happens, check the DLS/RTC).
    {
      HardError();
    }

    delay(200); // Wait 200 ms and try again
  }

  delay(2000); // Wait 2 seconds for the PCF8523's crystal oscillator to stabilise.

  RTC.start(); // Clear the stop bit of the RTC.
  
  return;
}


/* -------- SD card functions -------- */


void StartSD (void) // Start communication with the SD card
{
  RetryTimer = 0;

  while (!SD.begin(SPI_DLS_CS)) // Try starting communication with the SD card
  {
    RetryTimer += 200;

    if (RetryTimer >= Timeout) // Error out if communication doesn't start within Timeout 
    {
      HardError();
    }

    delay(200); // Wait 200 ms and try again
  }
}


void CreateSDFile (void) // Create a new file on the SD card and write the file header to it
{
  Now = RTC.now(); // Get the current date & time from the RTC

  char NameFormat[] = "DDhhmmss"; // Filename will be DDHHMMSS.ext
  Filename = (Now.toString(NameFormat) + FileExtension);

  if (SD.exists(Filename)) // Check if a file with this name already exists and halt if this is the case
  {
    HardError();
  }

  File DataFile = SD.open(Filename, FILE_WRITE); // Open the file

  if (DataFile) // Write the file header to the file
  {
    DataFile.print(F("date,time")); // Date & time

    for (int i = 0; i < 24; i++) // Add a leading 0 for single digit bin numbers
    {
      DataFile.print(",bin");

      if (i < 10)
      {
        DataFile.print(0);
      }

      DataFile.print(i); // Bin number
    }

    DataFile.println(",SP(s),SFR(ml/s),T(C),RH(%),PM_A(ug/m^3),PM_B(ug/m^3),PM_C(ug/m^3),CSmatch"); // Other columns

    DataFile.close();
  }
  else
  {
    HardError();
  }
}


void SaveSDData (OPCData Data, String SaveFile) // Save the data from the struct Data to the file SaveFile
{
  if (SD.exists(SaveFile)) // Check if the file exists
  {
    File DataFile = SD.open(SaveFile, FILE_WRITE);

    if (DataFile) // Write the data to the file
    {
      DataFile.print(Data.MeasDate);
      AddSep(DataFile);
      DataFile.print(Data.MeasTime);
      AddSep(DataFile);

      for (int i = 0; i < 24; i++) // Save the BinCounts to the file
      {
        DataFile.print(Data.BinCount[i]);
        AddSep(DataFile);
      }

      DataFile.print(Data.SamplingPeriod);
      AddSep(DataFile);
      DataFile.print(Data.SampleFlowRate);
      AddSep(DataFile);
      DataFile.print(Data.Temperature);
      AddSep(DataFile);
      DataFile.print(Data.Humidity);
      AddSep(DataFile);

      DataFile.print(Data.PMA);
      AddSep(DataFile);
      DataFile.print(Data.PMB);
      AddSep(DataFile);
      DataFile.print(Data.PMC);
      AddSep(DataFile);

      DataFile.println(Data.ChecksumMatch);

      DataFile.close();
    }
    else
    {
      HardError();
    }
  }
  else
  {
    HardError();
  }
}


void AddSep (File OutFile) // Print a column seperator to the file OutFile
{
  OutFile.print(",");
}


/* -------------------- OPC Functions -------------------- */


void StartOPC (void) //--TODO
{
  // Start the laser
  QueryOPC(0x03);
  SPI.transfer(0x07);
  SetCS(SPI_OPC_CS, LOW);
  SPI.endTransaction();
  delay(1000);

  // Start the fan and wait for it to spin up
  QueryOPC(0x03);
  SPI.transfer(0x03);
  SetCS(SPI_OPC_CS, LOW);
  SPI.endTransaction();
  delay(5000);
}


OPCData ReadOPCData (void) //--TODO add comments
{
  OPCData NewData;
  Now = RTC.now(); // Get the timestamp for the current measurement

  QueryOPC(0x30);

  // Read the full histogram from the OPC
  for (SPI_Buffer_Index = 0; SPI_Buffer_Index < 86; SPI_Buffer_Index++)
  {
    delayMicroseconds(10);
    SPI_Buffer[SPI_Buffer_Index] = SPI.transfer(0x01);
  }

  SetCS(SPI_OPC_CS, HIGH);
  SPI.endTransaction();

  // Transfer the histogram data from the SPI_Buffer to the NewData struct
  unsigned int BinIndex = 0; // Index for the 24 bins
  uint16_t *pUInt16; // Pointer to unisgned int values
  uint16_t ConvInt; // Used to temporarilly store the unsigned int values
  float *pFloat; // Pointer to float values

  char DateFormat[] = "YYYY-MM-DD"; // Date format
  char TimeFormat[] = "hh:mm:ss"; // Time format

  // Transfer/convert the data from the SPI_Buffer to the NewData struct

  // Time & date
  NewData.MeasDate = Now.toString(DateFormat);
  NewData.MeasTime = Now.toString(TimeFormat);

  // Bin counts for all 24 bins
  for (SPI_Buffer_Index = 0; SPI_Buffer_Index < 48; SPI_Buffer_Index += 2)
  {
    pUInt16 = (uint16_t *)&SPI_Buffer[SPI_Buffer_Index];
    NewData.BinCount[BinIndex] = *pUInt16;

    BinIndex++;
  }

  // Sampling period
  pUInt16 = (uint16_t *)&SPI_Buffer[52];
  ConvInt = *pUInt16;
  NewData.SamplingPeriod = (float)ConvInt/100;

  // Sample flow rate
  pUInt16 = (uint16_t *)&SPI_Buffer[54];
  ConvInt = *pUInt16;;
  NewData.SampleFlowRate = (float)ConvInt/100;

  // Temperature
  pUInt16 = (uint16_t *)&SPI_Buffer[56];
  ConvInt = *pUInt16;
  NewData.Temperature = -45 + 175*(float)ConvInt/65535;

  // Relative Humidity
  pUInt16 = (uint16_t *)&SPI_Buffer[58];
  ConvInt = *pUInt16;
  NewData.Humidity = 100*(float)ConvInt/65535;

  // PM_A
  pFloat = (float *)&SPI_Buffer[60];
  NewData.PMA = *pFloat;
  // PM_B
  pFloat = (float *)&SPI_Buffer[64];
  NewData.PMB = *pFloat;
  // PM_C
  pFloat = (float *)&SPI_Buffer[68];
  NewData.PMC = *pFloat;

  // Laser status
  pUInt16 = (uint16_t *)&SPI_Buffer[82];
  NewData.LaserStatus = *pUInt16;

  // Checksums and comparison
  pUInt16 = (uint16_t *)&SPI_Buffer[84];
  NewData.ChecksumReceived = *pUInt16;

  NewData.ChecksumCalculated = ChecksumCalc(SPI_Buffer, 84); // Calculate the checksum from the received data

  if (NewData.ChecksumReceived == NewData.ChecksumCalculated) // Compare the received and calculated checksums
  {
    NewData.ChecksumMatch = true;
  }
  else
  {
    NewData.ChecksumMatch = false;
  }

  return NewData;
}


void QueryOPC (unsigned char Command) // Start SPI communication with the OPC --TODO add comments/explanations
{
  unsigned char Response;
  int Tries;

  SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE1));

  Response = SPI.transfer(Command); // Read a byte to clear the OPC's SPI buffer

  delay (1);

  do
  {
    SetCS(SPI_OPC_CS, LOW);
    Tries = 0;

    do
    {
      Response = SPI.transfer(Command);

      if (Response != OPC_ready)
      {
        delay(1);
      }

      Tries++;
    }
    while ((Tries < 20) && (Response != OPC_ready));

    if (Response != OPC_ready)
    {
      if (Response == OPC_busy) // If the OPC indicates that it is busy, set the CS pin of the OPC high and wait a few seconds before trying again
      {
        SetCS(SPI_OPC_CS, HIGH);

        delay(2000);
      }
      else // If the response is neither OPC_ready nor OPC_busy, stop SPI communication and delay before trying again
      {
        SetCS(SPI_OPC_CS, HIGH);
        SPI.endTransaction();

        delay(5000);

        SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE1));
      }
    }
  }
  //while (Response != OPC_ready);
  while ((Response != OPC_ready) && (Serial.available() == 0)); //--CHECK if works with other line

  delay(10);
}


unsigned int ChecksumCalc (unsigned char SPI_Data[], unsigned char DataBytes) // Calculate the checksum from the received data --TODO add comments/explanations of how this works
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


/* -------------------- Misc Functions -------------------- */


void SetLED (int Pin, bool State) // Set the LED pin Pin to state State
{
  digitalWrite(Pin, State);
}


void SetCS (int Pin, bool State) // Set the chip select pin Pin to state State
{
  digitalWrite(Pin, State);
}


void HardError (void) // Blink the red LED and halt until the Arduino is reset
{
  SetLED(GreenLED, LOW);

  while (1)
  {
    SetLED(RedLED, HIGH);
    delay(500); 
    SetLED(RedLED, LOW);
    delay(500);
  }
}


/* -------- End of file -------- */
