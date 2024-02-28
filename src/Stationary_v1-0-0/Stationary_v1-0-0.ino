/* --------------------
Stationary
v1-0-0

Code for the Arduino of the stationary monitor. Check the README file for documentation.
-------------------- */


/* -------- Libraries & definitions -------- */


#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include <SoftwareSerial.h>

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

// Pins for serial communication
#define SIM_RX 0
#define SIM_TX 1
#define SIM_PWR 8

// Pins for external status LEDs
#define GreenLED 5
#define RedLED 6
#define BlueLED 7


/* -------- User parameters -------- */


String SIM_PIN = "0000"; // Pin code for the SIM card

unsigned int MeasInterval = 10000; // Measurment interval in (ms)
unsigned long Timeout = 1000; // Timeout for SIM commands in (ms)

String FileExtension = ".csv"; // File extension of the local save file (.csv or .txt)
String ScriptURL = "Google Script URL"; // URL of the Google Sheet script


/* -------- Variables -------- */


struct OPCData // Struct for storing the measurement data
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

  uint16_t LaserStatus;

  uint16_t ChecksumReceived;
  uint16_t ChecksumCalculated;
  bool ChecksumMatch;
};

// SPI buffer for reading data from the OPC.
unsigned char SPI_Buffer[86];
unsigned int SPI_Buffer_Index;

unsigned long CurrentTime;
unsigned long NextMeas;

bool FirstMeas; // Used to discard the first set of measurements

bool NetworkStatus;


RTC_PCF8523 RTC;
DateTime Now;

String Filename;

OPCData Data;

SoftwareSerial myserial(SIM_RX, SIM_TX); // Serial connection for communication with the SIM module


/* -------- Setup -------- */


void setup()
{
  Serial.begin(9600);

  delay(2000);

  // Configure LED pins
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  SetLED(GreenLED, LOW);
  SetLED(RedLED, HIGH);
  SetLED(BlueLED, LOW);

  // Configure SPI CS pins
  pinMode(SPI_OPC_CS, OUTPUT);
  pinMode(SPI_DLS_CS, OUTPUT);
  SetCS(SPI_OPC_CS, HIGH);
  SetCS(SPI_DLS_CS, HIGH); 

  NetworkStatus = false;

  delay(2000);

  delay(10000); // Allow the SIM module power to stabilise.

  SPI.begin();

  // Start all devices
  RTCstart();
  Serial.println("RTC started!");
  SDstart();
  Serial.println("SD started!");
  SDcreateFile();
  Serial.println("SD file started!");
  OPCstart();
  Serial.println("OPC started!");
  SIMstart(SIM_PIN);
  Serial.println("SIM started!");

  NetworkStatus = SIMcheckNetwork();

  CurrentTime = millis();
  NextMeas = CurrentTime;

  SetLED(GreenLED, HIGH);
  delay(1000);
  SetLED(RedLED, LOW);
}


/* -------- Main loop -------- */


void loop()
{
  if (FirstMeas == true) // Discard the first set of measurements.
  {
    Data = OPCreadData();
    FirstMeas = false;
  }

  CurrentTime = millis(); // Update current time form RTC
  NetworkStatus = SIMcheckNetwork(); // Check if network is connected

  if (CurrentTime >= NextMeas)
  {
    NextMeas = CurrentTime + MeasInterval; // Next measurement will be triggered after MeasInterval from now.

    Data = OPCreadData(); // Read the data from the OPC

    SDsaveData(Data, Filename); // Save the data to the SD card.

    bool Sent = SIMsendAll(Data); // Send the data to Google Sheet.

    SDsaveSent(Sent, Filename); // Save wheter the send was succesful to the SD card.
  }

}


/* -------- RTC functions -------- */


void RTCstart (void) // Start the RTC.
{
  int Tries = 0;

  while (!RTC.begin()) // Try starting the RTC.
  {
    if ((Tries == 5) && !RTC.begin()) HardError(); // Error out after 5 tries (if this happens, check the DLS/RTC).

    delay(200); // Wait 200 ms and try again.

    Tries++;
  }

  delay(2000); // Wait 2 seconds for the PCF8523's crystal oscillator to stabilise before trying to adjust the RTC.

  RTC.start(); // Clear the stop bit of the RTC.

  return;
}


/* -------- SD card functions -------- */


void SDstart (void) // Start communication with the SD card.
{
  int Tries = 0;

  while (!SD.begin(SPI_DLS_CS)) // Try starting communication with the SD card.
  {
    if ((Tries == 5) && !SD.begin()) HardError(); // Error out after 5 tries (if this happens, check the DLS/SD card).

    delay(200); // Wait 200 ms and try again

    Tries++;
  }

  return;
}


void SDcreateFile (void) // Create a new file on the SD card and write the file header to it.
{
  Now = RTC.now(); // Get the current date & time from the RTC.

  char NameFormat[] = "DDhhmmss"; // Filename will be DDHHMMSS.ext
  Filename = (Now.toString(NameFormat) + FileExtension);

  if (SD.exists(Filename)) HardError();// Check if a file with this name already exists and error out if this is the case.

  File DataFile = SD.open(Filename, FILE_WRITE); // Open the file.

  if (DataFile) // Write the file header to the file.
  {
    DataFile.print(F("date,time")); // Date & time

    for (int i = 0; i < 24; i++) // Bin numbers
    {
      DataFile.print(",bin");

      if (i < 10)
      {
        DataFile.print(0); // Add a leading 0 for single digit bin numbers.
      }

      DataFile.print(i); // Bin number
    }

    DataFile.println(",SP(s),SFR(ml/s),T(C),RH(%),PM_A(ug/m^3),PM_B(ug/m^3),PM_C(ug/m^3),CSmatch,sent"); // Other columns

    DataFile.close();
  }
  else HardError(); // Error out if the file can not be opened.

  return;
}


void SDsaveData (OPCData Data, String SaveFile) // Save the data from the struct Data to the file SaveFile.
{
  if (SD.exists(SaveFile)) // Check if the file exists.
  {
    File DataFile = SD.open(SaveFile, FILE_WRITE); // Open the file in WRITE mode.

    if (DataFile) // Write the data to the file.
    {
      DataFile.print(Data.MeasDate);
      SDaddSep(DataFile);
      DataFile.print(Data.MeasTime);
      SDaddSep(DataFile);

      for (int i = 0; i < 24; i++) // Save the BinCounts to the file.
      {
        DataFile.print(Data.BinCount[i]);
        SDaddSep(DataFile);
      }

      DataFile.print(Data.SamplingPeriod);
      SDaddSep(DataFile);
      DataFile.print(Data.SampleFlowRate);
      SDaddSep(DataFile);
      DataFile.print(Data.Temperature);
      SDaddSep(DataFile);
      DataFile.print(Data.Humidity);
      SDaddSep(DataFile);

      DataFile.print(Data.PMA);
      SDaddSep(DataFile);
      DataFile.print(Data.PMB);
      SDaddSep(DataFile);
      DataFile.print(Data.PMC);
      SDaddSep(DataFile);

      DataFile.print(Data.ChecksumMatch);

      DataFile.close();
    }
    else HardError(); // Error out if the file can not be opened.
  }
  else HardError(); // Error out if the file does not exist.

  return;
}


void SDsaveSent (bool Success, String SaveFile) // Save to the SD card whether the data has successfully been sent.
{
  if (SD.exists(SaveFile)) // Check if the file exists.
  {
    File DataFile = SD.open(SaveFile, FILE_WRITE); // Open the file.

    if (DataFile) // Write the data to the file.
    {
      DataFile.println(Success);

      DataFile.close(); // Close the file.
    }
    else HardError(); // If the file cannot be opened, error out.
  }
  else HardError(); // If the file cannot be found on the SD card, error out.

  return;
}


void SDaddSep (File SaveFile) // Print a column seperator to the file.
{
  SaveFile.print(","); // Separator for columns (typically ',')

  return;
}


/* -------- OPC functions -------- */


void OPCstart (void) // Start the OPC.
{
  // Start the laser.
  OPCquery(0x03);
  SPI.transfer(0x07);
  SetCS(SPI_OPC_CS, LOW);
  SPI.endTransaction();
  delay(1000);

  // Start the fan and wait for it to spin up.
  OPCquery(0x03);
  SPI.transfer(0x03);
  SetCS(SPI_OPC_CS, LOW);
  SPI.endTransaction();
  delay(5000);

  return;
}


OPCData OPCreadData (void) // Read a set of measurements form the OPC.
{
  OPCData NewData;
  Now = RTC.now(); // Get the timestamp for the current measurement.

  OPCquery(0x30);

  // Read the full histogram from the OPC.
  for (SPI_Buffer_Index = 0; SPI_Buffer_Index < 86; SPI_Buffer_Index++)
  {
    delayMicroseconds(10);
    SPI_Buffer[SPI_Buffer_Index] = SPI.transfer(0x01);
  }

  SetCS(SPI_OPC_CS, HIGH);
  SPI.endTransaction();

  // Transfer the histogram data from the SPI_Buffer to the NewData struct.
  unsigned int BinIndex = 0; // Index for the 24 bins
  uint16_t *pUInt16; // Pointer to unisgned int values
  uint16_t ConvInt; // Used to temporarilly store the unsigned int values.
  float *pFloat; // Pointer to float values

  char DateFormat[] = "YYYY-MM-DD"; // Date format
  char TimeFormat[] = "hh:mm:ss"; // Time format

  // Transfer/convert the data from the SPI_Buffer to the NewData struct.

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

  // Relative humidity
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

  NewData.ChecksumCalculated = ChecksumCalc(SPI_Buffer, 84); // Calculate the checksum from the received data.

  if (NewData.ChecksumReceived == NewData.ChecksumCalculated) // Compare the received and calculated checksums.
  {
    NewData.ChecksumMatch = true;
  }
  else
  {
    NewData.ChecksumMatch = false;
  }

  return NewData;
}


void OPCquery (unsigned char Command) // Start SPI communication with the OPC.
{
  unsigned char Response;
  int Tries;

  SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE1));

  Response = SPI.transfer(Command); // Read a byte to clear the OPC's SPI buffer.

  delay (1);

  do
  {
    SetCS(SPI_OPC_CS, LOW); // Pull OPC SPI CS pin low to start transmission.
    Tries = 0;

    do
    {
      Response = SPI.transfer(Command);

      if (Response != OPC_ready) // Check if the OPC reports ready for communiation.
      {
        delay(1);
      }

      Tries++;
    }
    while ((Tries < 20) && (Response != OPC_ready));

    if (Response != OPC_ready)
    {
      if (Response == OPC_busy) // If the OPC indicates that it is busy, set the CS pin of the OPC high and wait a few seconds before trying again.
      {
        SetCS(SPI_OPC_CS, HIGH);

        delay(2000);
      }
      else // If the response is neither OPC_ready nor OPC_busy, stop SPI communication and delay before trying again.
      {
        SetCS(SPI_OPC_CS, HIGH);
        SPI.endTransaction();

        delay(5000);

        SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE1));
      }
    }
  }
  while ((Response != OPC_ready) && (Serial.available() == 0));

  delay(10);

  return;
}


unsigned int ChecksumCalc (unsigned char SPI_Data[], unsigned char DataBytes) // Calculate the checksum.
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


/* -------- SIM functions -------- */


void SIMstart (String PIN) // Start the SIM module and unlock the SIM card.
{
  String Status = ""; // String for Storing the Response from the SIM Module
  int Tries;

  myserial.begin(115200); // Begin the serial connection with the SIM module using 115200 baud.

  delay(1000);

  // Set the power PIN of the SIM module HIGH.
  pinMode(SIM_PWR, OUTPUT);
  digitalWrite(SIM_PWR, HIGH);

  delay(1000);

  Status = SIMsendCommand("AT+CFUN?", 1000); // Check the current SIM module status.
  Tries = 0;

  delay(500);

  while (Status.indexOf("+CFUN: 1") == -1) // Set the SIM module to full functionality mode.
  {
    if (Tries > 4) HardError(); // Error out after 5 tries (if this happens check the SIM module).

    SIMsendCommand("AT+CFUN=1", 1000);
    delay(1000);
    Status = SIMsendCommand("AT+CFUN?", 1000);

    delay(500);
    Tries++;
  }

  delay(500);

  Status = SIMsendCommand("AT+CPIN?", 1000); // Check for the SIM unlock status.
  Tries = 0;

  delay(500);

  while(Status.indexOf("+CPIN: READY") == -1) // Unlock the SIM card.
  {
    if (Status.indexOf("+CPIN: SIM PIN") > -1)
    {
      delay(500);

      SIMsendCommand("AT+CPIN=" + PIN, 1000); // Send the SIM PIN to the SIM module.
    }

    delay(1000);

    Status = SIMsendCommand("AT+CPIN?", 1000); // Check for the SIM unlock status.

    if (Tries > 4) HardError(); // Error out after 5 tries (if this happens check the SIM card).

    delay(500);
    Tries++;
  }

  return;
}


String SIMsendCommand (String Command, const uint16_t Timeout) // Send a command to the SIM module.
{
  String Response = ""; // String for the response from the SIM module.

  myserial.println(Command); // Write the command to the SIM module over the serial connection.

  unsigned long CommandTime = millis(); // Get the current time.

  while ((CommandTime + Timeout) > millis()) // If the timeout has not been reached yet, listen for and store the response from the SIM module.
  { 
    while (myserial.available() > 0)
    {
      char c = myserial.read(); // Read a char.
      Response += c; // Append the char.
    }
  }

  return Response;
}


bool SIMsendAll(OPCData Data) // Send the OPC data to Google Sheet.
{
  String Status = "";
  int Tries;

  Status = SIMsendCommand("AT+CFUN?", 1000); // Check SIM module status.
  Tries = 0;

  delay(50);

  if (Status.indexOf("+CFUN: 1") == -1)
  {
    while (Status.indexOf("+CFUN: 1") == -1)
    {
      if (Tries > 4) return 0;

      SIMsendCommand("AT+CFUN=1", 1000);
      delay(50);
      Status = SIMsendCommand("AT+CFUN?", 1000);

      delay(50);
      Tries++;
    }
  }

  delay(50);

  SIMsendCommand("AT+CGATT=1", 1000);
  SIMsendCommand("AT+CGACT=1,1", 1000);
  SIMsendCommand("AT+CGDCONT=1,\"IP\",\"apn\"", 1000);


  if (SIMcheckNetwork() == true) // If a network connection is available, send the data.
  {
    String HTTPstring = "";

    String Response = SIMsendCommand("AT+HTTPINIT\r\n", 2000);

    Serial.println(Response);

    Serial.println("Starting transmission."); //--DEBUG

    // Assemble the HTTPstring.
    HTTPstring = "AT+HTTPPARA=\"URL\",\"" + ScriptURL + "?date=" + (String)Data.MeasDate + "&time=" + (String)Data.MeasTime;
    HTTPstring = HTTPstring + "&SP=" + (String)Data.SamplingPeriod + "&SFR=" + (String)Data.SampleFlowRate;
    HTTPstring = HTTPstring + "&T=" + (String)Data.Temperature + "&RH=" + (String)Data.Humidity + "&CSmatch=" + (String)Data.ChecksumMatch;
    
    for (int i = 0; i < 24; i++)
    {
      HTTPstring = HTTPstring + "&bin";

      if (i < 10)
      {
        HTTPstring = HTTPstring + "0"; // Add a leading 0 for single digit bin numbers.
      }

      int Value = Data.BinCount[i];
      String ValueStr= (String)Value;

      HTTPstring = HTTPstring + (String)i + "=" + ValueStr;
    }

    HTTPstring = HTTPstring + "\"";

    Serial.println("HTTP String is: " + HTTPstring); //--DEBUG

    Response = SIMsendCommand(HTTPstring, 2000);
    SIMsendCommand("AT+HTTPACTION=0\r\n", 3000);

    Serial.print("Response to send is: "); //--DEBUG
    Serial.println(Response);

    delay(200);
    
    SIMsendCommand("AT+HTTPTERM\r\n", 3000);
  }

  return 1;
}


bool SIMcheckNetwork (void) // Check if the SIM module is connected to a network.
{
  String Status = SIMsendCommand("AT+CNSMOD?", 1000); // Inquire about the network status.

  if (Status[Status.indexOf(",") + 1] == '0') // Check the value to the right of the ',' in the response (0 == no service).
  {
    SetLED(BlueLED, LOW); // Turn the network indication LED OFF.
    return false; // Return false if no network is connected.
  }
  else // Any number other than 0 indicates a network connection.
  {
    SetLED(BlueLED, HIGH); // Turn the network indication LED ON.
    return true; // Return true if a network is connected.
  }
}


/* -------- Misc -------- */


void SetLED (int Pin, bool State) // Set the LED pin HIGH or LOW.
{
  digitalWrite(Pin, State);

  return;
}


void SetCS (int Pin, bool State) // Set the CS pin HIGH or LOW.
{
  digitalWrite(Pin, State);

  return;
}


void HardError (void) // Blink the red LED and halt until the Arduino is reset.
{
  SetLED(GreenLED, LOW);

  while (1)
  {
    SetLED(RedLED, HIGH);
    delay(500); 
    SetLED(RedLED, LOW);
    delay(500);
  }

  return;
}


/* -------- End of file -------- */
