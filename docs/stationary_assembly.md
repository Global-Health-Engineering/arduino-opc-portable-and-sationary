# Assembly of the Stationary Monitor Core

The assembly of the stationary monitor core is a bit more involved than that of the portable one. The main reason for this is a pin conflict between the Adafruit DLS and the DFRobot SIM shield. Other than this, the process is very similar to that of the portable monitor.

![stationary_core_ISO](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/stationary_core_ISO.jpg)

#### Parts List --TODO merge into lower list


| LED headers              | 3 pin              | 2         |


| Item                    | Value/note               | Quantity              |
| ----------------------- | ------------------------ | :-------------------: |
| Arduino UNO             | R3/R4 Minima             | 1                     |
| Adafruit DLS            | Rev. C                   | 1                     |
| Headers for DLS         | included w/ DLS          | 1 complete set        |
| DFRobot SIM7600CE-T     | w/ stacking headers      | 1                     |
| SIM card                | w/ data subscription     | 1                     |
| Wire-to-board connector | 2 pin                    | 1 set (male & female) |
| Wire-to-board connector | 6 pin                    | 1 set (male & female) |
| USB cable               | type matching powerbank  | 1                     |
| OPC connector/cable     | 6 pin Molex Pico-Clasp   | 1 (male)              |
| Resistor                | $2'200 \ \Omega$         | 1                     |
| Resistor                | $3'300 \ \Omega$         | 1                     |
| Wire                    | $0.25 \ \textrm{mm}^2$   | 4 colours             |
| LEDs                    | $3$ or $5 \ \textrm{mm}$ | 3 (green, red, blue)  |
| LED headers             | 3 pin                    | 2 (matching LEDs)     |
| CR1220 battery          | -                        | 1                     |
| SD card                 | max. $32 \ \textrm{GB}$  | 1                     |

- For the wire-to-board connectors on the DLS, any type with a pitch of $\sim 2.5 \ \textrm{mm}$ works, JST XH connectors are a good choice as they are pretty resistant aginst pull out and fairly compact. Alternatively, the wires _could_ be soldered directly to the DLS, skipping the use of connectores, however this is not recommended as it makes swapping any component a lot more work.

![JST_connectors](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/JST_connectors.jpg)

- For the OPC you need a 6 pin Molex Pico-Clasp connector. This is a _tiny_ connector and you should ideally use a special (and expensive) crimping tool to properly crimp these pins. It is easier to buy a [pre-crimped cable](https://www.aliexpress.com/item/1005005897060590.html) set which already has the connector on one side.

![Pico-Clasp_connector](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/Pico-Clasp_connector.jpg)

### Required Tools

- Soldering iron
- Solder (ideally lead-free)
- PPE (safety glasses/goggles and mask/respirator)
- Wire cutters
- Wire strippers
- Crimping tool (appropriate version for the chosen connectors)
- Pliers
- Multimeter

Additionally, a soldering stand (third hand) is really helpful but not absolutely necessary.

## Step 1: Assembling RTC Shield

For the assembly of the DLS, first follow `Step 1` in the [assembly guide of the portable monitor]().

### Step 1.5: Soldering the External LED Headers (optional)

To facilitate the connection of external status LEDs, headers are soldered to pins `5`, `6` and `7` as well as to the `GND` row on the DLS.

![female_headers]()

## Step 2: Preparing the Power Cables

--TODO

## Step 3: Preparing the OPC Cable

--TODO

#### Step 4: Replacing the UNO's Headers

--TODO

#### Step 5: Soldering the SIM Shield Jumper Wire

--TODO

#### Step 6: Putting it all together

--TODO
