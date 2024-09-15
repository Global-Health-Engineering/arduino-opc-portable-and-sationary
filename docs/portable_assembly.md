# Assembly of the Portable Monitor 

The assembly of the portable monitor core is fairly simple thanks to the Adafruit DLS. Only basic soldering skills and a bit of wire crimping are required to complete it.

![portable_monitor](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_monitor.jpg)

#### Parts List

| Item                    | Value/note              | Quantity              |
| ----------------------- | ----------------------- | :-------------------: |
| Arduino UNO             | R3/R4 Minima            | 1                     |
| Adafruit DLS            | Rev. C                  | 1                     |
| Headers for DLS         | included w/ DLS         | 1 complete set        |
| Wire-to-board connector | 2 pin                   | 1 set (male & female) |
| Wire-to-board connector | 6 pin                   | 1 set (male & female) |
| USB cable               | type matching powerbank | 1                     |
| OPC connector/cable     | 6 pin Molex Pico-Clasp  | 1 (male)              |
| Resistor                | $2'200 \ \Omega$        | 1                     |
| Resistor                | $3'300 \ \Omega$        | 1                     |
| Wire                    | $0.25 \ \textrm{mm}^2$  | 4 colours             |
| CR1220 battery          | -                       | 1                     |
| SD card                 | max. $32 \ \textrm{GB}$, FAT formatted | 1                     |

- For the wire-to-board connectors on the DLS, any type with a pitch of $\sim 2.5 \ \textrm{mm}$ works. JST XH connectors are a good choice as they are pretty resistant aginst pull out and fairly compact. Alternatively, the wires _could_ be soldered directly to the DLS, skipping the use of connectores, however this is not recommended as it makes swapping any component a lot more work.

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

## Step 1: Assembling the DLS

As the first step, the DLS is populated with all the required components and connectors.  

### Step 1.0: Installing the DLS Headers

This step is only required if you bought a DLS that does not have the headers installed yet. For this step, follow the step `Installing the Headers` in [Adafruit's DLS manual](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-data-logger-shield.pdf).

### Step 1.1: Soldering the Power and OPC Connectors

In this step, the 2 pin power connector and 6 pin connector for the OPC are soldered onto the DLS. 

- First, position the 2 pin power connector as shown in the photo below in the holes labeled `5v` and `GND` and take note of its orientation. 

![portable_power_connector](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_power_connector.jpg)

- If you're using JST XH connectors you might have to trim a little bit of the plastic housing to clear the tips of the headers on the outside. Do this _very carefully_ with a sharp hobby knife.

![JST_trimmed](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/JST_trimmed.jpg)

- Once the header is positioned, solder it from the underside, ensuring that the pins are not shorted.

- Next, position the 6 pin OPC connector as shown in the photo below. Note that it is positioned so that the two pins towards the edge are on the rows labeled `5.0V` and `GND` and how it is orientated.

![portable_OPC_connector](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_OPC_connector.jpg)

- Again, solder this from the underside, ensuring that no two adjacent pins are shorted.

### Step 1.2: Soldering the Resistors

In this step, the two resistors for the OPC voltage divider are soldered onto the DLS.

- First, take the `2'200 ohm` resistor and bend its legs so that it fits into the holes as shown in the photo below.
![portable_R1](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_R1.jpg)

- Once positioned correctly, solder the resistor from the underside and trim the legs.

- For the `3'300 ohm` resistor, position it as shown in the schematic below and repeat the same process as for the first resistor.

![portable_R2](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_R2.jpg)

### Step 1.3: Connecting Everything

With the connectors and resistors soldered, it is time to connect everything with short bits of wire. The general process for this is to cut an appropriate length of wire, strip the ends, pre-tin them and then solder the wire ends to the appropriate holes or pins.

The required connections are shown in the photo below. It helps to use differently coloured wires to keep a better overview of what needs to be connected where (plus it looks neat).

![portable_wire_4](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_wire_4.jpg)

- For the first connection, prepare a short piece of wire and solder it as shown in the photo below. Note that is soldered to **both** resistors.

![portable_wire_1](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_wire_1.jpg)

For the following connections, bend one end of the prepared wires as shown in the photo below. These can be pushed through the holes on the DLS like the legs of connectors or resistors.

![wire_bent](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/wire_bent.jpg)

- Next, connect the blue, purple and yellow wires as shown in the photos below.

![portable_wire_2](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_wire_2.jpg)

![portable_wire_3](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_wire_3.jpg)

![portable_wire_4](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_wire_4.jpg)

With all the wires soldered it is a good idea to use a multimeter to check all connections are working and no pins are shorted together.

### Step 1.4: Connecting the LEDs (optional)

In this optional step, the two status LEDs on the DLS are connected.

- Connect the holes labeled `L1` and `L2` to holes `3` and `4` respectively, as shown in the schematic below. This can either be done by two _very_ short bits of wire or more easily by using bits of the resistors' trimmed off legs. You can do the connection on either side of the DLS. The easiest way to solder these connections is to fill the holes on the DLS with solder and then hold the wire/leg in place with a pair of pliers while soldering.

![portable_LEDs](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_LEDs.jpg)

Your DLS is now complete and should look like the one in the photos below.

![portable_DLS_topside](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_DLS_topside.jpg)

![portable_DLS_underside](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_DLS_underside.jpg)

## Step 2: Preparing the USB Power Cable

- For the USB power cable, trim off the USB Type-A end of an old USB cable. The length of this is dependant on the location and orientation of the components in your chosen housing. If the cable is too short you can lengthen it by soldering on lengths of additional wire.

- Strip the cut end of the USB cable to expose the individual wires inside. You should see four wires: white, green, red and black.

![USB-A_cable_stripped](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/USB-A_cable_stripped.jpg)

- Trim the white and green wires  so they are flush with the insulation of the whole cable.

![USB-A_cable_trimmed](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/USB-A_cable_trimmed.jpg)

- Strip the red and black wires of the USB cable and crimp on the JST connector pins. Then insert the pins into the connector in the orientation shown in the photo below. Note that the clasp side of the JST connector is facing the camera.

![JST_power_orientation](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/JST_power_orientation.jpg)

If you decide to use the 3D-printable housing files provided in this repository, you will have to remove the shell of the USB Type-A connector to make the cable fit. You can do this by carefully cutting throught the plastic of the connector housing and peeling it away. You might also have to remove some of the sheet metal connector housing underneath. You should end up with a cable as shown in the photo below.

![USB_connector_naked](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/USB_connector_naked.jpg)

## Step 3: Preparing the OPC Cable

- Take the pre-crimped Pico-Clasp cable and crimp JST connector pins on the free ends of the wires.

- Push the JST connector pins into the JST connector housing by matching the wires according to the two following Tables. Note that the clasp side of the connectors is facing the camera and that the numbering of the pins is from left to right.

![OPC-DLS_connector](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/OPC-DLS_connector.jpg)

#### DLS side connector wire order.

| Pin | Wire   |
| --- | ------ |
| 1   | `5.0V` |
| 2   | `GND`  |
| 3   | `DATA` |
| 4   | `MOSI` |
| 5   | `MISO` |
| 6   | `SCK`  |

![OPC_connector](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/OPC_connector.jpg)

#### OPC side connector wire order.

| Pin | Wire   |
| --- | ------ |
| 1   | `5.0V` |
| 2   | `SCK`  |
| 3   | `MISO` |
| 4   | `MOSI` |
| 5   | `DATA` |
| 6   | `GND`  |

## Step 4: Putting It All Together

- With the DLS, power cable and OPC cable prepared, take the Arduino UNO and place the DLS on top. Make sure to line up all of the headers correctly and carefully push the DLS down onto the UNO.

- Next, insert a CR1220 button cell battery and the SD card into their slots on the DLS and connect the OPC using the 6 pin connector and OPC cable.

If you printed the housings, it might be easier to screw the UNO onto its mountng spots before putting the DLS on top and to screw in the OPC before connecting its cable to the DLS.

![portable_core_ISO](https://github.com/Global-Health-Engineering/arduino-opc-portable-and-sationary/blob/main/img/portable_core_ISO.jpg)

Congratulations, the core of your portable PM monitor is now fully assembled! Next, keep following the steps below to get it ready for using.

## Step 5: Adjusting the RTC

To adjust the RTC on the DLS follow the steps outlined below.The OPC and SD card may be connected for this but don't have to be.

- Start the Arduino IDE on your PC

- Connect the UNO to you PC. Make sure the coin battery is properly inserted into the holder on the DLS. before doing so

- Upload the file `RTC_adjust.ino` to the UNO and let it run for at east a few seconds. You should see the current time and date being echoed to the serial monitor.

- Do not disconnect the UNO from your PC until you have completed `Step 6`! If you do, the timestamps will be wrong.

## Step 6: Uploading the Firmware

- Upload the file `Portable.ino` to the UNO

Phew, you made it! Your portable PM monitor is now ready to start collecting measurements. Have a look at the [`usage guide`](portable_usage.md) to help you with this.
