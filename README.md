# Portable and stationary PM monitoring with Arduino UNO and Alphasense OPC-N3

## 1. Overview

This repository allows for the building of particulate matter monitoring systems using Arduino UNOs and Alphasense OPC-N3 optical particle counter modules.

There are two variants:

- A portable monitor to measure the personal exposure to particulate matter.
- A stationary monitor for remote long-term deployment.

The aim of this project was to provide a simple and free guide for others to build their own low-cost PM monitoring systems. The monitors described in this repository can either be copied directly or used as a basis for custom units adapted to specific needs. The project itself is licensed under the the 'CC-BY 4.0' license, however some of the software libraries use different licenses. For more details on this see section 5. of this README file.

### 1.1. Cost breakdown

One goal of the project was to keep the cost of the monitors low, so they are built from readily available and affordable components. The only real exception is the Alphasense OPC-N3, this is rather pricey but could be substituted by a cheaper sensor module if not all of its functionality is needed (be aware, replacing the OPC migth require changing the data-read interface).

The following tables give a rough breakdown of the costs of each of the monitors. The links are only for reference, sourcing the parts locally is most likely the cheapest option!

**Portable monitor - Total: ~570.-**

| Name                                   | Source                                                                                                         | Approx. price (CHF)    |
| -------------------------------------- | -------------------------------------------------------------------------------------------------------------- | ---------------------: |
| Arduino UNO (R3/R4 Minima)             | [Mouser](https://www.mouser.ch/ProductDetail/Arduino/ABX00080?qs=ulEaXIWI0c9tbG%2FHj5EzRA%3D%3D)               | 20.-                   |
| Adafruit Data Logger Shield (Rev. C)   | [Mouser](https://www.mouser.ch/ProductDetail/Adafruit/1141?qs=GURawfaeGuAe9uOWyGs1aw%3D%3D)                    | 15.-                   |
| SD card (32 GB)                        | [Mouser](https://www.mouser.ch/ProductDetail/SanDisk/SDSDAA-032G?qs=EgF7oUuTQmpUPFrDZtLtsQ%3D%3D)              | 20.-                   |
| RTC battery (CR1220)                   | [Digitec](https://www.digitec.ch/en/s1/product/energizer-cr1220-lithium-1-pcs-cr1220-40-mah-batteries-8762860) | 5.-                    |
| Powerbank                              | [Digitec](https://www.digitec.ch/en/s1/product/sbs-power-bank-10000-mah-5-w-37-wh-powerbanks-19791017)         | 35.-                   |
| Alphasense OPC-N3                      | N/A                                                                                                            | ~500.-                 |
| Small components (LEDs, resistors, wires, etc.) | N/A                                                                                                   | ~10.-                  |

**Stationary monitor - Total: ~670.-**

| Name                                   | Source                                                                                                                        | Approx. price (CHF)    |
| -------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------- | ---------------------: |
| Arduino UNO (R3/R4 Minima)             | [Mouser](https://www.mouser.ch/ProductDetail/Arduino/ABX00080?qs=ulEaXIWI0c9tbG%2FHj5EzRA%3D%3D)                              | 20.-                   |
| Adafruit Data Logger Shield (Rev. C)   | [Mouser](https://www.mouser.ch/ProductDetail/Adafruit/1141?qs=GURawfaeGuAe9uOWyGs1aw%3D%3D)                                   | 15.-                   |
| SD card (32 GB)                        | [Mouser](https://www.mouser.ch/ProductDetail/SanDisk/SDSDAA-032G?qs=EgF7oUuTQmpUPFrDZtLtsQ%3D%3D)                             | 20.-                   |
| RTC battery (CR1220)                   | [Digitec](https://www.digitec.ch/en/s1/product/energizer-cr1220-lithium-1-pcs-cr1220-40-mah-batteries-8762860)                | 5.-                    |
| Alphasense OPC-N3                      | N/A                                                                                                                           | ~500.-                 |
| UPS board                              | Aliexpress                                                                                                                    | ~5.-                   |
| UPS batteries (2x 18650)               | [Digitec](https://www.digitec.ch/en/s1/product/samsung-lithium-ion-battery-type-18650-1-pcs-18650-285-mah-batteries-16208254) | 30.-                   |
| DFRobot SIM7600CE-T                    | [Mouser](https://www.mouser.ch/ProductDetail/DFRobot/TEL0124?qs=17u8i%2FzlE88MEbXRJuYFsA%3D%3D)                               | 60.-                   |
| Small components (LEDs, resistors, wires, etc.) | N/A                                                                                                                  | ~15.-                  |

The cost breakdowns do **NOT** include a housing for the monitors, as this is very dependant on the exact use case. They could be as simple as a plastic food container. For this project, the housings were 3D-printed using a consumer grade FDM printer. For more details on these, see section 1.2. of this README file.

### 1.2. 3D printed housings --TODO

CAD files for 3D printable enclosures are located in `cad` directory. They are also shown below.

![Portable housing](/img/Portable_CAD.png)

![Stationary housing](/img/Stationary_CAD.png)

## 2. Hardware assembly

### 2.1. Portable monitor

The assembly of the portable monitor is fairly simple, mainly thanks to the Adafruit DLS. Only basic soldering skills and a bit of wire crimping are required.

#### Step 1: Assembling RTC shield

First, the DLS is prepared with all the required components and connectors

#### Step 2: Preparing OPC cable

#### Step 3: Putting it all together

### 2.2. Stationary monitor

The assembly of the stationary is a bit more involved than that of the portable one. The main reason for this is a pin conflict between the Adafruit DLS and the DFRobot SIM shield. Other than this, the process is very similar to that of the portable one.












## 3. Uploading the software

### 3.1. Portable monitor

### 3.2. Stationary monitor

## 4. Using the monitors










## 5. Software library licensing

The code provided in this repository makes use of the libraries listed in the following table. When using any code from this repository, make sure you follow any applicable licenses of the used libraries in addition to the license of the project. A copy of the licenses is provided in the 'LICENSES' directory.

| Library | License |
| ------- | ------- |
| [SPI.h](https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/SPI)                     | LGPL v2.1 |
| [SD.h](https://github.com/arduino-libraries/SD)                                                   | GPL v3    |
| [RTClib](https://github.com/adafruit/RTClib)                                                      | MIT       | 
| [SoftwareSerial](https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/SoftwareSerial) | LGPL v2.1 |

## 6. Change log

## Tree --TODO update

    .
    ├── CITATION.cff
    ├── LICENSE.md
    ├── README.md
    ├── cad
    │   ├── Portable
    │   │   ├── Portable_v1-0-0.f3d
    │   │   ├── Portable_v1-0-0.step
    │   │   ├── Portable_v1-0-0.stl
    │   │   └── test.stl
    │   ├── README.md
    │   ├── Stationary
    │   │   ├── Stationary_v1-0-0.f3d
    │   │   ├── Stationary_v1-0-0.step
    │   │   └── Stationary_v1-0-0.stl
    │   └── misc
    │       ├── Alphasense_OPC-N3.f3d
    │       ├── Alphasense_OPC-N3.step
    │       ├── Arduino_UNO_PCB.f3d
    │       ├── Arduino_UNO_PCB.step
    │       ├── SBS_TTBB1000FASTA.f3d
    │       └── SBS_TTBB1000FASTA.step
    ├── img
    │   ├── Portable_CAD.png
    │   ├── README.md
    │   └── Stationary_CAD.png
    └── src
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

