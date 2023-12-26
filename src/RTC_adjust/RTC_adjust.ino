/*
Arduino code for setting the time on the RTC of the Adafruit Data Logger Shield Rev C (PCF8523)

- This code sets the RTC to the current system time at compilation. Make sure the system time is set correctly!
- Any delay between compiling and uploading will lead to an error in the RTC. For best results use the "Upload" button to compile and immediately upload to the Arduino.
*/


#include <RTClib.h>


RTC_PCF8523 RTC;


void setup() {
  Serial.begin(9600);

  Serial.println("Starting Arduino");

  if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  delay(2000); // Wait 2 seconds for PCF8523's crystal oscillator to stabilise before trying to adjust

  RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC to current system time
  RTC.start(); // Clear the stop bit of the RTC
}


void loop() {
  DateTime now = RTC.now();

  Serial.println(now.timestamp());

  delay(10000);
}

