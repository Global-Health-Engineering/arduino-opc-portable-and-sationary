# Portable and Stationary PM Monitors using Arduino UNO and Alphasense OPC-N3

## 1. Overview

This repository provides instructions for the building of particulate matter monitoring systems using the Arduino UNO and Alphasense OPC-N3 optical particle counter module.

There are two variants:

- A portable monitor to measure the personal exposure to particulate matter.
- A stationary monitor for remote long(er)-term deployment.

This repository is part of a bachelor's thesis whose goal it was to develope adaptable low-cost PM monitors and provide a simple and free guide for others also looking to build such systems. The monitors described in this repository can either be copied directly or used as the basis for custom units adapted to specific needs. The project itself is licensed under the the [`CC-BY 4.0`](LICENSE.md) license, however some of the software libraries used are come with different licenses. For more details on this, see [`section 5`](#5-software-library-licensing) of this README file.

### 1.1. System Overview

The core of both the portable and stationary monitors is a stack made up of an Arduino UNO and an Adafruit Data Logger Shield (DLS). The stationary monitor also includes a DFRobot SIM7600CE-T shield for wireless data transmission to Google Drive. Both monitors feature local data storage on an SD card and proper timestamping using the DLS' real-time clock. To interface with the Alphasense OPC-N3 module, a voltage divider is required to drop the SPI lines from 5 V to 3 V. The handy prototyping area of the DLS is used to implement this and also to host all of the required connectors for power, communication and (optional) status LEDs.

### 1.2. Cost breakdown

One goal of the project was to keep the cost of the monitors low, so they are built from readily available and affordable components. The only real exception is the Alphasense OPC-N3. This is rather pricey but could be substituted by a cheaper sensor module if not all of its particular functionality is needed (be aware, replacing the OPC migth require changing the hardware and software interface).

The following tables give a rough breakdown of the costs of each of the monitors. The links are for reference only as sourcing the parts locally is most likely the cheapest option!

`Cost breakdown of the portable monitor.`
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

`Cost breakdown of the stationary monitor.`
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

The cost breakdowns do **NOT** include housings for the monitors, as this is very dependant on the exact use case. They could be as simple as a plastic food container. For this project, the housings were 3D-printed on a consumer grade FDM printer. For more details on these, see [`section 1.3.`](#13-3d-printed-housings) of this README file.

### 1.3. 3D printed housings

--TODO





The files for the 3D-printed housings can be found in the [`cad`](cad) directory. This also contains some simplified CAD models of the UNO and OPC to allow you to design your own housings.




CAD files for 3D printable enclosures are located in `cad` directory. They are also shown below.

![Portable housing](/img/Portable_CAD.png)

![Stationary housing](/img/Stationary_CAD.png)



#### 1.3.1. Portable monitor

The housing for the portable monitor is designed to be used with a 'GoPro Chesty' harness. 



#### 1.3.2. Stationary monitor


## 2. Hardware assembly

### 2.1. Portable monitor

The assembly of the portable monitor is fairly simple, mainly thanks to the Adafruit DLS. Only basic soldering skills and a bit of wire crimping are required to get a working PM monitor.

`BOM for the portable monitor --TODO order`
| Item                     | Value/note         | Qty       |
| ------------------------ | ------------------ | :-------: |
| Adafruit DLS             | Rev. C             | 1         |
| Headers for DLS          | included w/ DLS    | 1 set     |
| Connector                | 2 pin              | 1 set     |
| Connector                | 6 pin              | 1 set     |
| Resistor                 | VALUE_1            | 1         |
| Resistor                 | VALUE_2            | 1         |
| Wire                     | GAUGE              | ? colours |
| OPC cable                | w/ small connector | 1         |
| Arduino UNO              | R3/R4 Minima       | 1         |
| CR1220 battery           | -                  | 1         |
| SD card                  | max. 32 GB         | 1         |

`Required tools`
- Soldering iron
- Solder (ideally lead-free)
- Soldering stand (optional)
- Wire cutters
- Wire strippers
- Crimping tool (appropriate version for the chosen connectors)

#### Step 1: Assembling RTC shield

First, the DLS is built up with all the required components and connectors. For the connectors, any type with a pitch of ~2.5 mm works, JST XH connectors are a good choice as they are pretty resistant aginst pull out and fairly compact. Alternatively, the wires _could_ be soldered directly to the DLS, skipping the use of connectores, however this is not recommended as it makes swapping any component a lot more work.

##### Step 1.0: Installing DLS headers

This step is only required if you bought a DLS that does not have the headers installed yet. For this step, follow the step `Installing the Headers` in [Adafruit's DLS manual](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-data-logger-shield.pdf).

##### Step 1.1: Soldering the power and OPC connectors

In this step, the 2 pin power connector and 6 pin connector for the OPC are soldered onto the DLS. 

First, position the power connector as shown in the image below in the holes labeled `Vin` and `GND`. If you're using JST XH connectors you might have to trim a little bit of the plastic housing to clear the tips of the headers on the outside. Do this _very carefully_ with a sharp hobby knife.

--TODO IMAGE_POWER_CONNECTOR_POSITION 

Once the header is positioned, solder it from the underside, ensuring that no two adjacent pins are shorted.

Next, position the OPC connector as shown in the image below. Note that it is positioned so that the two pins towards the edge are on the rows labeled `5.0V` and `GND`.

--TODO IMAGE_OPC_CONNECTOR_POSITION

Again, solder this from the underside, ensuring that no two adjacent pins are shorted.

##### Step 1.2: Soldering the resistors

In this step, the two resistors for the OPC voltage divider are soldered onto the DLS.

First, take the `VALUE_1` resistor and bend its legs so that it fits into the holes like shown in the image below.

--TODO IMAGE_VALUE_1_RESISTOR_POSITION

Once positioned correctly, solder the resistor from the underside and trim the legs.

For the `VALUE_2` resistor, position it as shown in the image below and repeat the same process as for the first resistor.

##### Step 1.3: Connecting everything

With the connectors and resistors soldered, it is time to connect everything with short bits of wire. The general process for this is to cut an appropriate length of wire, strip the ends, pre-tin them and then solder the wire to the appropriate holes or pins.

The required connections are shown in the image below. It helps to use differently coloured wires to keep a better overview of what needs to be connected where (plus it looks neat).

--TODO IMAGE_WIRE_CONNECTONS_DLS_UNDERSIDE

##### Step 1.4: Connecting the LEDs (optional)

In this step, the two LEDs on the DLS are connected. This step is optional.

Connect the holes labeled `L1` and `L2` to holes `3` and `4` respectively, as shown in the image below. This can either be done by two _very_ short bits of wire or more easily by using bits of the resistors' trimmed off legs. You can do the connection on either side of the DLS.

--TODO IMAGE_OPTIONAL_LED_CONNECTION

#### Step 2: Preparing OPC cable

In this step, the wire to connect the OPC to the DLS is prepared.

--TODO

#### Step 3: Preparing the (USB) power cable

--TODO

#### Step 4: Putting it all together

With the DLS and OPC cable prepared, take the Arduino UNO and place the DLS on top. Make sure to line up all of the headers correctly and carefully push the DLS down onto the UNO. Next, insert a CR1220 button cell battery into the holder on the DLs and connect the OPC using the 6 pin connector. If you printed the housings, it might be easier to screw the UNO onto its mountng spots before putting the DLS on top and to screw in the OPC before connecting its cable to the DLS.

Congratulations, the core of your PM monitor is now fully assembled! Next, have a look at section 3. of this README file to finish the monitors by uploading the firmware.

### 2.2. Stationary monitor

The assembly of the stationary is a bit more involved than that of the portable one. The main reason for this is a pin conflict between the Adafruit DLS and the DFRobot SIM shield. Other than this, the process is very similar to that of the portable monitor.

`BOM for the stationary monitor --TODO order`
| Item                     | Value/note         | Qty       |
| ------------------------ | ------------------ | :-------: |
| Adafruit DLS             | Rev. C             | 1         |
| Headers for DLS          | included w/ DLS    | 1 set     |
| Connector                | 2 pin              | 1 set     |
| Connector                | 6 pin              | 1 set     |
| Resistor                 | VALUE_1            | 1         |
| Resistor                 | VALUE_2            | 1         |
| Wire                     | GAUGE              | ? colours |
| OPC cable                | w/ small connector | 1         |
| Arduino UNO              | R3/R4 Minima       | 1         |
| CR1220 battery           | -                  | 1         |
| SD card                  | max. 32 GB         | 1         |
| DFRobot SIM7600CE-T      | -                  | 1         |
| LED                      | Red                | 1         |
| LED                      | Green              | 1         |
| LED                      | Blue               | 1         |
| LED headers              | 3 pin              | 2         |
| SIM card                 | with data subscription| 1      |
| Stacking headers         | for Arduino UNO    | 1         |

`Required tools`
- Soldering iron
- Solder (ideally lead-free)
- Soldering stand (optional)
- Wire cutters
- Wire strippers
- Crimping tool (appropriate version for the chosen connectors)

#### Step 1: Assembling RTC shield

--TODO

#### Step 2: Preparing the OPC cable

--TODO

#### Step 3: Preparing the power cable

--TODO

#### Step 4: Replacing the UNO's headers

--TODO

#### Step 5: Soldering the SIM shield jumper wire

--TODO

#### Step 6: Putting it all together

--TODO

## 3. Uploading the software

With the hardware ready, the UNOs need to be flashed with the appropriate firmware. However, before doing so the RTC on the DLS needs to be set correctly. This process is the same for the portable and stationary monitors.

### 3.1. Adjusting the RTC

--TODO

### 3.2. Portable monitor

--TODO

### 3.3. Stationary monitor

--TODO

## 4. Using the monitors

--TODO

### 4.1. Portable monitor

--TODO

### 4.2. Stationary monitor

--TODO

## 5. Software library licensing

The code provided in this repository makes use of the libraries listed in the following table. When using any code from this repository, make sure you follow any applicable licenses of the libraries in addition to the license of the project. A copy of the licenses is provided in the [`LICENSES`](LICENSES) directory.

| Library | License |
| ------- | ------- |
| [SPI.h](https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/SPI)                     | `LGPL v2.1` |
| [SD.h](https://github.com/arduino-libraries/SD)                                                   | `GPL v3`    |
| [RTClib](https://github.com/adafruit/RTClib)                                                      | `MIT`       | 
| [SoftwareSerial](https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/SoftwareSerial) | `LGPL v2.1` |

## 6. Change log

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
