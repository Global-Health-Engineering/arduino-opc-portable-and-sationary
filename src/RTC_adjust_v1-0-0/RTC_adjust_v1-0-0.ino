/* --------------------
RTC_adjust
v1-0-0

Code for adjusting the RTC on the Adafruit Data Logger Shield (Rev C, using PCF8523). Sets the time & date to the current system time & date, make sure this is set correctly!
Any delay between compiling and uploading will lead to an error in the RTC. For best results use the "Upload" button to compile and immediately upload to the Arduino.
Replace the code on the Arduino with something else without reseting/unpowering it, otherwise the RTC will not be accurate.
-------------------- */


/* -------- Libraries & definitions -------- */


#include <RTClib.h>


RTC_PCF8523 RTC;


/* -------- Setup -------- */


void setup() {
  Serial.begin(9600); // Start serial port with 9600 baud rate.

  Serial.println("Starting setup.");

  if (! RTC.begin()) { // Check if the RTC is connected.
    Serial.println("Couldn't find RTC.");
    Serial.flush();
    while (1) delay(10); // Wait until reset.
  }

  delay(2000); // Wait 2 seconds for PCF8523's crystal oscillator to stabilise before trying to adjust.

  RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC to current system time & date.
  RTC.start(); // Clear the stop bit of the RTC.
}


/* -------- Main loop -------- */


void loop() {
  DateTime now = RTC.now(); // Update "now" to current time & date.

  Serial.println(now.timestamp()); // Print current time & date to serial port.

  delay(5000);
}


/* -------- End of file -------- */
