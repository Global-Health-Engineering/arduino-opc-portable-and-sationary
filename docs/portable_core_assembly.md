# Portable monitor assembly

--TODO IMAGE_PORTABLE_OVERVIEW

The assembly of the portable monitor is fairly simple thanks to the Adafruit DLS. Only basic soldering skills and a bit of wire crimping are required to get a working PM monitor.

## BOM for the portable monitor --TODO order
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

## Required tools
- Soldering iron
- Solder (ideally lead-free)
- Soldering stand (optional)
- Wire cutters
- Wire strippers
- Crimping tool (appropriate version for the chosen connectors)

## Step 1: Assembling RTC shield

First, the DLS is built up with all the required components and connectors. For the connectors, any type with a pitch of ~2.5 mm works, JST XH connectors are a good choice as they are pretty resistant aginst pull out and fairly compact. Alternatively, the wires _could_ be soldered directly to the DLS, skipping the use of connectores, however this is not recommended as it makes swapping any component a lot more work.

### Step 1.0: Installing DLS headers

This step is only required if you bought a DLS that does not have the headers installed yet. For this step, follow the step `Installing the Headers` in [Adafruit's DLS manual](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-data-logger-shield.pdf).

### Step 1.1: Soldering the power and OPC connectors

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
