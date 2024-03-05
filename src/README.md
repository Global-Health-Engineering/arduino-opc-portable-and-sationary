# src

This directory contains the source code for Arduino and for receiving data sent by Arduino.

    .
    ├── Data_Reception
    │   └── Google_Sheet_Script.txt
    ├── Portable_v1-0-0
    │   └── Portable_v1-0-0.ino
    ├── Portable_v2-0-0
    │   └── Portable_v2-0-0.ino
    ├── README.md
    ├── RTC_adjust
    │   ├── README.md
    │   └── RTC_adjust_v1-0-0.ino
    └── Stationary
        ├── README.md
        └── Stationary_v1-0-0.ino

| name | description |
| - | - |
| `Google_Sheet_Script.txt` | Google Sheets script for pulling data from the stationary monitor |
| `Portable_v1-0-0.ino` | ? |
| `Portable_v2-0-0.ino` | Code for the portable monitor. |
| `RTC_adjust_v1-0-0.ino` | Code for adjusting the RTC on Adafruit DLS |
| `Stationary_v1-0-0.ino` | Code for the stationary monitor. |

## Portable monitor

The microcontroller for portable monitoring collects data from the Alphasense OPC-N3 every *XXX* seconds and stores it on the SD card.
Its runtime on a *XXX* mAh battery is *XXX* hours.

## Stationary monitor

The microcontroller for portable monitoring collects data from the Alphasense OPC-N3 every *XXX* seconds and stores it on the SD card.

In normal operation, the system runs connected to the electrical grid. However, it switches without interruption to the battery power supply once the grid is down.

It sends data to the cloud though 2G/3G/4G communication every *XXX* min(hours?). The communication shield is switched off when not used to limit power consumption.

---
