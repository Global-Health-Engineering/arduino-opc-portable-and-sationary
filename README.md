# Portable and stationary PM monitoring with Arduino and Alphasense OPC-N3

This repository allows for building the air quality monitoring asseblies with OPC sensors.

## List of components

### Portable monitor - bill of materials

| Name | Source | Approx. price (CHF) |
| ---- | ------ | ----------------------- |
| Arduino UNO (R3/R4 Minima)             | [Mouser](https://www.mouser.ch/ProductDetail/Arduino/ABX00080?qs=ulEaXIWI0c9tbG%2FHj5EzRA%3D%3D) | 18.- |
| Adafruit Data Logger Shield (Rev. C)   | [Mouser](https://www.mouser.ch/ProductDetail/Adafruit/1141?qs=GURawfaeGuAe9uOWyGs1aw%3D%3D) | 12.- |
| SD card (32 GB)                        | [Mouser](https://www.mouser.ch/ProductDetail/SanDisk/SDSDAA-032G?qs=EgF7oUuTQmpUPFrDZtLtsQ%3D%3D) | 20.- |
| RTC battery (CR1220)                   | N/A | 2.- |
| Alphasense OPC-N3                      | N/A | ~500.- |
| Small components (LEDs, resistors, wires, etc.) | N/A | ~10.- |

### Stationary monitor - bill of materials

| Name | Source | Approx. price (CHF) |
| ---- | ------ | ----------------------- |
| Arduino UNO (R3/R4 Minima)             | [Mouser](https://www.mouser.ch/ProductDetail/Arduino/ABX00080?qs=ulEaXIWI0c9tbG%2FHj5EzRA%3D%3D) | 18.- |
| Adafruit Data Logger Shield (Rev. C)   | [Mouser](https://www.mouser.ch/ProductDetail/Adafruit/1141?qs=GURawfaeGuAe9uOWyGs1aw%3D%3D) | 12.- |
| SD card (32 GB)                        | [Mouser](https://www.mouser.ch/ProductDetail/SanDisk/SDSDAA-032G?qs=EgF7oUuTQmpUPFrDZtLtsQ%3D%3D) | 20.- |
| RTC battery (CR1220)                   | N/A | 2.- |
| Alphasense OPC-N3                      | N/A | ~500.- |
| UPS board                              | N/A |  |
| UPS batteries (2x 18650)               | N/A |  |
| DFRobot SIM7600CE-T                    | N/A |  |
| Small components (LEDs, resistors, wires, etc.) | N/A | ~15.- |

## Instructions

### Portable monitor

#### Assembly

#### Usage

### Stationary monitor

#### Assembly

#### Usage

## 3D printed housings

CAD files for designed casings can be located in `cad` directory. They are also shown below.

![Portable housing](/img/Portable_CAD.png)

![Stationary housing](/img/Stationary_CAD.png)

## Tree

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

