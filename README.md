# Portable and Stationary PM Monitors using Arduino UNO and Alphasense OPC-N3

## 1. Overview

This repository provides instructions for the building of particulate matter monitoring systems using the Arduino UNO and Alphasense OPC-N3 optical particle counter module.

There are two variants:

- A portable monitor to measure the personal exposure to particulate matter.
- A stationary monitor for remote long(er)-term deployment.

This repository is part of a bachelor's thesis whose goal it was to develope adaptable low-cost PM monitors and provide a simple and free guide for others also looking to build such systems. The monitors described in this repository can either be copied directly or used as the basis for custom units adapted to specific needs. The project itself is licensed under the the [`CC-BY 4.0`](LICENSE.md) license, however some of the software libraries used are come with different licenses. For more details on this, see [`Section 3`](#3-software-library-licensing) of this README file.

### 1.1. System Overview

The core of both the portable and stationary monitors is a stack made up of an Arduino UNO and an Adafruit Data Logger Shield (DLS). The stationary monitor also includes a DFRobot SIM7600CE-T shield for wireless data transmission to Google Drive. Both monitors feature local data storage on an SD card and proper timestamping using the DLS' real-time clock. To interface with the Alphasense OPC-N3 module, a voltage divider is required to drop the SPI lines from 5 V to 3 V. The handy prototyping area of the DLS is used to implement this and also to host all of the required connectors for power, communication and (optional) status LEDs.

--TODO IMAGE_PORTABLE_SCHEMATIC_OVERVIEW

--TODO IMAGE_STATIONARY_SCHEMATIC_OVERVIEW

### 1.2. Cost breakdown

One goal of the project was to keep the cost of the monitors low, so they are built from readily available and affordable components. The only real exception is the Alphasense OPC-N3. This is rather pricey but could be substituted by a cheaper sensor module if not all of its particular functionality is needed (be aware, replacing the OPC migth require changing the hardware and software interface).

The following tables give a rough breakdown of the costs of each of the monitors. The links are for reference only as sourcing the parts locally is most likely the cheapest option!

#### Cost breakdown of the portable monitor.

| Name                                   | Source                                                                                                         | Approx. price (CHF)    |
| -------------------------------------- | -------------------------------------------------------------------------------------------------------------- | ---------------------: |
| Arduino UNO (R3/R4 Minima)             | [Mouser](https://www.mouser.ch/ProductDetail/Arduino/ABX00080?qs=ulEaXIWI0c9tbG%2FHj5EzRA%3D%3D)               | 20.-                   |
| Adafruit Data Logger Shield (Rev. C)   | [Mouser](https://www.mouser.ch/ProductDetail/Adafruit/1141?qs=GURawfaeGuAe9uOWyGs1aw%3D%3D)                    | 15.-                   |
| SD card (32 GB)                        | [Mouser](https://www.mouser.ch/ProductDetail/SanDisk/SDSDAA-032G?qs=EgF7oUuTQmpUPFrDZtLtsQ%3D%3D)              | 20.-                   |
| RTC battery (CR1220)                   | [Digitec](https://www.digitec.ch/en/s1/product/energizer-cr1220-lithium-1-pcs-cr1220-40-mah-batteries-8762860) | 5.-                    |
| Powerbank                              | [Digitec](https://www.digitec.ch/en/s1/product/sbs-power-bank-10000-mah-5-w-37-wh-powerbanks-19791017)         | 35.-                   |
| Alphasense OPC-N3                      | N/A                                                                                                            | ~500.-                 |
| Small components (LEDs, resistors, wires, etc.) | N/A                                                                                                   | ~10.-                  |
| **Total**                              |                                                                                                                | ~570.-                 |

#### Cost breakdown of the stationary monitor.

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
| **Total**                              |                                                                                                                               | ~670.-                 |

The cost breakdowns do **NOT** include housings for the monitors, as this is very dependant on the exact use case. They could be as simple as a plastic food container. For this project, the housings were 3D-printed on a consumer grade FDM printer. More details on these can be found in [`Section 1.3.`](#13-3d-printed-housings) of this README file.

### 1.3. 3D-Printed Housings

The files for the 3D-printed housings can be found in the [`cad`](cad) directory. This also contains some simplified CAD models of the UNO and OPC to allow you to design your own housings.

The designs provided can be printed on standard consuer grade FDM printers. They should be printed from a material such as PETG or ASA to make sure they are strong enough and not easily damaged by UV radiation.

#### 1.3.1. Portable Monitor Housing

The housing for the portabel monitor is designed to be used with a GoPro 'Chesty' chest harness. This allows the monitor to be worn somewhat comfortably. A list of all the hardware required for the portable monitor housing is provided below.

![Portable housing](/img/Portable_CAD.png)

#### Parts List of the Portable Monitor Housing

| Item                | Note        | Quantity       |
| ------------------- | ----------- | :------------: |
| 3D-printed parts    | PETG or ASA | 1 complete set |
| Threaded inserts M3 | -           | 7              |
| Threaded inserts M4 | -           | 8              |
| M3x8 screws         | button head | 7              |
| M3x16 screws        | button head | 2              |
| M4x10 screws        | button head | 8              |
| GoPro 'Chesty'      | -           | 1              |

#### 1.3.2. Stationary Monitor Housing

![Stationary housing](/img/Stationary_CAD.png)

A list of all the hardware required for the stationary monitor housing is provided below.

#### Parts List of the Portable Monitor Housing --TODO

| Item                | Note        | Quantity       |
| ------------------- | ----------- | :------------: |
| 3D-printed parts    | PETG or ASA | 1 complete set |

## 2. Instructions

To build your own PM monitors, first follow the assembly guide for you chosen version. To use you monitors, have a look at the usage guides. These can be found in the [`docs`](docs) directory. Alternatively, the table below provides direct links to individual guides.

| Portable                                | Stationary                                |
| :-------------------------------------: | :---------------------------------------: |
| [`Assembly`](docs/portable_assembly.md) | [`Assembly`](docs/stationary_assembly.md) |
| [`Usage`](docs/portable_usage.md)       | [`Usage`](docs/stationary_usage.md)       |

## 3. Software Library Licensing

The code provided in this repository makes use of the libraries listed in the following table. When using any code from this repository, make sure you follow any applicable licenses of the libraries in addition to the license of the project. A copy of the licenses is provided in the [`licenses`](licenses) directory.

| Library | License |
| ------- | ------- |
| [SPI.h](https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/SPI)                     | `LGPL v2.1` |
| [SD.h](https://github.com/arduino-libraries/SD)                                                   | `GPL v3`    |
| [RTClib](https://github.com/adafruit/RTClib)                                                      | `MIT`       | 
| [SoftwareSerial](https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/SoftwareSerial) | `LGPL v2.1` |

## 4. Change Log

## Tree --TODO UPDATE

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
