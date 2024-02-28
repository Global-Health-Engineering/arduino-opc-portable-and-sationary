# Stationary

Author: Valentin Hirsch

Version: v1-0-0

Publish date: 28-02-24

License: 

Description:

## Functions

### Adafruit Data Logging Shield (RTC & SD)

- RTCstart
-- Return: void
-- Parameters: void
-- Description: Lorem Ipsum

- SDstart
-- Return: void
-- Parameters: void
-- Description: Lorem Ipsum

- SDcreateFile
-- Return: void
-- Parameters: void
-- Description: Lorem Ipsum

- SDsaveData
-- Return: void
-- Parameters: OPCData Data, String Filename
-- Description: Lorem Ipsum

- SDsavePosition **MOVE TO SD**
-- Return: void
-- Parameters: GPSPosition Position, String Filename
-- Description: Lorem Ipsum

- SDsaveSent **MOVE TO SD**
-- Return: void
-- Parameters: bool Success, String Filename
-- Description: Lorem Ipsum

- SDaddSep
-- Return: void
-- Parameters: File SaveFile
-- Description: Lorem Ipsum


### Alphasense OPC-N3

- OPCstart
-- Return: void
-- Parameters: void
-- Description: Lorem Ipsum

- OPCreadData
-- Return: OPCData NewData
-- Parameters: void
-- Description: Lorem Ipsum

- OPCquery
-- Return: void
-- Parameters: unsigned char Command
-- Description: Lorem Ipsum

- ChecksumCalc
-- Return: unsigned int Checksum
-- Parameters: unsigned char SPI_Data[], unsigned char DataBytes
-- Description: Lorem Ipsum


### DFRobot SIM7600CE-T

- SIMstart
-- Return: void
-- Parameters: String PIN
-- Description: Lorem Ipsum

- SIMsendCommand
-- Return: String Response
-- Parameters: String Command, const uint16_t Timeout
-- Description: Lorem Ipsum

- SIMsendAll
-- Return: bool -
-- Parameters: OPCData Data, GPSPosition Position
-- Description: Lorem Ipsum

- SIMcheckNetwork
-- Return: bool -
-- Parameters: void
-- Description: Lorem Ipsum

- GPSstart
-- Return: void
-- Parameters: void
-- Description: Lorem Ipsum

- GPSgetPosition
-- Return: GPSPosition NewPosition
-- Parameters: void
-- Description: Lorem Ipsum


### Misc

- SetLED
-- Return: void
-- Parameters: int Pin, bool State
-- Description: Lorem Ipsum

- SetCS	
-- Return: void
-- Parameters: int Pin, bool State
-- Description: Lorem Ipsum

- HardError
-- Return: void
-- Parameters: void
-- Description: Lorem Ipsum

---