# Assembly of the Portable Monitor Core

The assembly of the portable monitor core is fairly simple thanks to the Adafruit DLS. Only basic soldering skills and a bit of wire crimping are required to complete it.

--TODO IMAGE_PORTABLE_CORE_OVERVIEW

### Parts List

| Item                     | Value/note             | Qty                   |
| ------------------------ | ---------------------- | :-------------------: |
| Arduino UNO              | R3/R4 Minima           | 1                     |
| Adafruit DLS             | Rev. C                 | 1                     |
| Headers for DLS          | included w/ DLS        | 1 complete set        |
| Connector                | 2 pin                  | 1 set (male & female) |
| Connector                | 6 pin                  | 1 set (male & female) |
| OPC connector/cable      | 6 pin Molex Pico-Clasp | 1 (male)              |
| Resistor                 | VALUE_1                | 1                     |
| Resistor                 | VALUE_2                | 1                     |
| Wire                     | GAUGE                  | ? colours             |
| CR1220 battery           | -                      | 1                     |
| SD card                  | max. 32 GB             | 1                     |

- For the connectors on the DLS, any type with a pitch of ~2.5 mm works, JST XH connectors are a good choice as they are pretty resistant aginst pull out and fairly compact. Alternatively, the wires _could_ be soldered directly to the DLS, skipping the use of connectores, however this is not recommended as it makes swapping any component a lot more work.

--TODO IMAGE_JST_CONNECTOR_2_AND_6_PIN

- For the OPC you need a 6 pin Molex Pico-Clasp connector. This is a _tiny_ connector and you should ideally use a special (and expensive) crimping tool to properly crimp these pins. It is easier to buy a pre-crimped cable set which already has the connector on one side (--TODO ADD_EXAMPLE_LINK).

--TODO IMAGE_OPC_CABLE_BLANK

### Required Tools

- Soldering iron
- Solder (ideally lead-free)
- PPE (safety glasses/goggles and mask/respirator)
- Wire cutters
- Wire strippers
- Crimping tool (appropriate version for the chosen connectors)

Additionally, a soldering stand (third hand) is really helpful but not absolutely necessary.

## Step 1: Assembling RTC Shield

As the first step, the DLS is populated with all the required components and connectors. 

--TODO IMAGE_DLS_EMPTY_WITH_HEADERS_ISO_VIEW

### Step 1.0: Installing DLS Headers

This step is only required if you bought a DLS that does not have the headers installed yet. For this step, follow the step `Installing the Headers` in [Adafruit's DLS manual](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-data-logger-shield.pdf).

### Step 1.1: Soldering the Power and OPC Connectors

In this step, the 2 pin power connector and 6 pin connector for the OPC are soldered onto the DLS. 

- First, position the 2 pin power connector as shown in the schematic below in the holes labeled `Vin` and `GND` and take note of its orientation. 

--TODO IMAGE_PORTABLE_CORE_SCHEMATIC_PWR_CONNECTOR

- If you're using JST XH connectors you might have to trim a little bit of the plastic housing to clear the tips of the headers on the outside. Do this _very carefully_ with a sharp hobby knife.

--TODO IMAGE_JST_INTERFERENCE_TRIMMED

- Once the header is positioned, solder it from the underside, ensuring that no two adjacent pins are shorted.

--TODO IMAGE_PORTABLE_CORE_SCHEMATIC_PWR_CONNECTOR_SOLDERED_UNDERSIDE

- Next, position the 6 pin OPC connector as shown in the schematic below. Note that it is positioned so that the two pins towards the edge are on the rows labeled `5.0V` and `GND` and how it is orientated.

--TODO IMAGE_PORTABLE_CORE_SCHEMATIC_OPC_CONNECTOR

- Again, solder this from the underside, ensuring that no two adjacent pins are shorted.

Your DLS should now look like the one in the image below.

--TODO IMAGE_PORTABLE_CORE_CONNECTORS_SOLDERED_TOPSIDE

### Step 1.2: Soldering the Resistors

In this step, the two resistors for the OPC voltage divider are soldered onto the DLS.

- First, take the `VALUE_1` resistor and bend its legs so that it fits into the holes as shown in the image below.

--TODO IMAGE_PORTABLE_CORE_SCHEMATIC_VALUE_1_RESISTOR

- Once positioned correctly, solder the resistor from the underside and trim the legs.

--TODO IMAGE_PORTABLE_CORE_RESISTOR_SOLDERED_UNDERSIDE

- For the `VALUE_2` resistor, position it as shown in the schematic below and repeat the same process as for the first resistor.

--TODO IMAGE_PORTABLE_CORE_SCHEMATIC_VALE_2_RESISTOR

Your DLS should now look like the one in the image below.

--TODO IMAGE_PORTABLE_CORE_CONNECTORS_RESISTORS_SOLDERED_TOPSIDE

--TODO IMAGE_PORTABLE_CORE_CONNECTORS_RESISTORS_SOLDERED_UNDERSIDE

### Step 1.3: Connecting Everything

With the connectors and resistors soldered, it is time to connect everything with short bits of wire. The general process for this is to cut an appropriate length of wire, strip the ends, pre-tin them and then solder the wire ends to the appropriate holes or pins.

The required connections are shown in the image below. It helps to use differently coloured wires to keep a better overview of what needs to be connected where (plus it looks neat).

--TODO IMAGE_PORTABLE_CORE_SCHEMATIC_WIRE_CONNECTONS_UNDERSIDE

--TODO describe/tips for each connection

Your DLS should now look like the one in the image below.

--TODO IMAGE_PORTABLE_CORE_WIRE_CONNECTIONS_SOLDERED_UNDERSIDE

### Step 1.4: Connecting the LEDs (optional)

In this optional step, the two status LEDs on the DLS are connected.

- Connect the holes labeled `L1` and `L2` to holes `3` and `4` respectively, as shown in the schematic below. This can either be done by two _very_ short bits of wire or more easily by using bits of the resistors' trimmed off legs. You can do the connection on either side of the DLS.

--TODO IMAGE_PORTABLE_CORE_SCHEMATIC_LED_CONNECTIONS

--TODO IMAGE_PORTABLE_SCORE_LED_CONNECTIONS_SOLDERED

## Step 2: Preparing the (USB) Power Cable

--TODO instructions for making USB power cable

## Step 3: Preparing the OPC Cable

--TODO instructions for making OPC cable

## Step 4: Putting It All Together

With the DLS, power cable and OPC cable prepared, take the Arduino UNO and place the DLS on top. Make sure to line up all of the headers correctly and carefully push the DLS down onto the UNO. Next, insert a CR1220 button cell battery and the SD card into their slots on the DLS and connect the OPC using the 6 pin connector and OPC cable.

If you printed the housings, it might be easier to screw the UNO onto its mountng spots before putting the DLS on top and to screw in the OPC before connecting its cable to the DLS.

Congratulations, the core of your portable PM monitor is now fully assembled! Next, have a look at --TODO LINK_FIRMWARE_UPLOAD to finish the monitor by uploading the firmware.
