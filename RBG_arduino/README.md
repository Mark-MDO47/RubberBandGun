# Arduino Code for the Rubber Band Gun (RBG): RBG_SciFi.ino
The Arduino and its sketch RBG_SciFi.ino handily manage all the tasks including voice menus, storage of user configuration, LED rings, and sound generation. It can do this because RBG_SciFi.ino has pre-computed tables built in that guide it, especially for state transitions and special effects.

**Table of Contents**
* [Generating Tables for the Code](#generating-tables-for-the-code "Generating Tables for the Code")
* [RBG_SciFi_StatesAndInputs.h](#rbg_scifi_statesandinputsh "")
  * [RBG_SciFi_StatesAndInputs.h - Effect Types and Ranges](#rbg_scifi_statesandinputsh---effect-types-and-ranges "RBG_SciFi_StatesAndInputs.h - Effect Types and Ranges")
  * [RBG_SciFi_StatesAndInputs.h - Factory Reset Configurations](#rbg_scifi_statesandinputsh---factory-reset-configurations "RBG_SciFi_StatesAndInputs.h - Factory Reset Configurations")
* [Libraries and Capabilities Used](#libraries-and-capabilities-used "Libraries and Capabilities Used")
* [The Code Itself](#the-code-itself "The Code Itself")
  * [Special Code Topic: LED Patterns](#special-code-topic-led-patterns "Special Code Topic: LED Patterns")
* [Reprogramming in the Completed Rubber Band Gun](#reprogramming-in-the-completed-rubber-band-gun "Reprogramming in the Completed Rubber Band Gun")
  * [RBG_SciFi.ino](#rbg_scifiino "RBG_SciFi.ino")
  * [Sounds](#sounds "Sounds")
  * [Separate Programming Arduino for Bluetooth Module](#separate-programming-arduino-for-bluetooth-module "Separate Programming Arduino for Bluetooth Module")

## Generating Tables for the Code
See the following for an overview of generating the tables for the RBG_SciFi.ino code:
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/BuildRubberBandGunSoftware.pdf

The file **StateTable_minimal.xlsx** is the heart of RBG_SciFi.ino. It has multiple tabs that are used to generate the code for the RBG.
* **StateTable:** the main tab, used in generating the myStateTable struct and associated #define's. This is done by running makeStateTable.py. This tab controls the overall action of the RBG.
* **RULES:** a list of things to keep in mind when changing the StateTable tab. Sorry, not a tutorial, just notes.
* **debugging:** where I capture serial port debugging info to diagnose why my stupid code doesn't do what I want and not what I say.
  * There is a list of "grep" commands used to filter this down; then I load the mdo2.txt into a spreadsheet in column B, put the Excel formula after the grep's in A1, and copy down the length. I then sort and remove duplicates. This uses my tiny mdoUniq.py routine to get rid of lines that are duplicate between a start and end string.
* **YX5200 info:** a bunch of info from other sources referenced in the parts directory. Could delete this tab now but it took me a while to make things work reliably.
* **Sounds:** this includes the text for use in text-to-speech synthesis for the robotic sounds. This is generated by running RobotSounds.py. The sound numbers are used in the StateTable tab. This is described more in https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/YX5200.md.
* **LEDpatterns:** this helps me organize the LED patterns by number and generate lookupLEDpatternTbl. There is a short description in this tab of the use of the fabulous FastLED library and the generation and organization of the LED patterns.
* **FactorySettings:** the EEPROM stores four configurable settings for all the sounds and LED effects. In PROGMEM storage is the factory configuration for these four configurable settings. This tab organizes the factory settings and helps me generate the factory_effect_configs table. There are four EEPROM configurations; there is a factory configuration for each of the EEPROM configurations.
  * 0: running configuration
  * 1: saved auxilliary configuration 1
  * 2: saved auxilliary configuration 2
  * 3: saved auxilliary configuration 3

## RBG_SciFi_StatesAndInputs.h
If StateTable_minimal.xlsx is the heart of RBG_SciFi.ino, then... OK, I won't continue down that path.

### RBG_SciFi_StatesAndInputs.h - Effect Types and Ranges
Search for **mEFCT_** until you find mEFCT_WIND_UP and you will see a list of effect types in groups of 10. There are up to 9 (sorry, I wasted one for convenience) LED and Sound effects for each one of these effect groups. cfgMaxSoundForType and cfgMaxLEDForType show the end range for these effects per type. The effect type max ranges are: 001 to 009 - wind-up effects; 011 to 019 - shoot effects; 021 to 029 - open barrel effects; 031 to 039 - lock and load barrel effects; 041 to 049 - initial power-up effects; 051 to 059 - waiting for trigger. The last one is different: 061 to 127 - unique effects used to navigate menus or other activities.
* For each of the configurable settings, there is a number in that range stored in EEPROM for both LED and Sound effects for each of the effect groups (except for the unique effects). These are changeable via voice menu as seen in the "Operations" chart in https://github.com/Mark-MDO47/RubberBandGun/blob/master/BuildRubberBandGunSoftware.pdf. To change one of the settings for one of the configurations, make that configuration the current configuration then choose the path **Config**, **Sound or LED**, and **When, What, Choose**. The "When" refers to one of the ranges, for instance "wind-up effects". The "What" refers to either the **Sound** effect or the **LED** effect. After that you choose among the effects through the range stored in cfgMaxSoundForType or cfgMaxLEDForType as appropriate.

### RBG_SciFi_StatesAndInputs.h - Factory Reset Configurations
Search for factory_effect_configs and you will find the table with the Factory Reset configurations for Sound and LED patterns for all four configurable settings. These are organized with 32 bytes per configurable setting, both for convenience and for expansion. 16 bytes are for Sound effects and 16 bytes are for LED effects. The first 6 of these 16-byte regions are used for the Effect Types we discussed above. The number stored is in the range [1-9], the effect type is implicit in the position of the byte.
* If you do lots of configuration changes to the RBG and then just want to go back to the factory reset configuration, follow the "Operations" chart in https://github.com/Mark-MDO47/RubberBandGun/blob/master/BuildRubberBandGunSoftware.pdf and choose the path **Config**, **Cfg Reset Copy**, and **Fctry Rst Copy**. The option to choose would be "Erase the running setting and erase all saved auxilliary settings and reset to the factory settings".

## Libraries and Capabilities Used
Once all those tables and #defines are generated and installed in the Arduino code, we still have the rest of the code.

Major libraries used are mostly described in the following:
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/README.md

One other important general thing I use is PROGMEM and associated F() macro to store constants (strings and various numbers) in program storage instead of RAM. Here are a couple of useful articles about this capability:
* http://www.gammon.com.au/progmem
* https://www.arduino.cc/reference/en/language/variables/utilities/progmem/

## The Code Itself
I won't go into too much detail here, but this is a bit of a roadmap to **RBG_SciFi.ino**.
* **getButtonInput()** retrieves a bit mask for all the buttons and a few other states like end-of-sound and lock-and-load-status
* **RBG_processStateTable()** is used to go through the state table in the myStateTable struct
  * it may call **RBG_startEffectLED()** and/or **RBG_startEffectSound()**
* **RBG_waitForInput()** is where we wait for results of getButtonInput() to match something that would cause a state transition; also some logic for what we would do in certain circumstances.
* **doPattern()** is used to continue an LED time-sequence pattern. Sounds continue by themselves to completion, so no such routine for sounds
* **eeprom_check_init()** is used to verify we have a valid EEPROM configuration and if not to load the factory configuration

#### Special Code Topic: LED Patterns
I thought this could use some more explanation.

FastLED is the library I use for controlling these WS2812B color addressable LEDs:
* https://www.arduino.cc/reference/en/libraries/fastled/
* https://github.com/FastLED/FastLED

If you are new to FastLED, look at this famous demo code to see how easy it can be
* https://github.com/FastLED/FastLED/blob/master/examples/DemoReel100/DemoReel100.ino

In the RBG I use four unmodified routines from DemoReel100. These routines take no parameters.
* **bpm()**
* **confetti()**
* **juggle()**
* **rainbowWithGlitter()**

I also use three modified routines from DemoReel100. The first routine takes no parameters, but the other two take a parameter.
* **RBG_bpm_rings()**
* **RBG_confetti_fadeby()**
* **RBG_juggle_numdot_ring()**

I also use two routines of my own invention; these routines take parameter(s).
* **RBG_diskDownTheDrainOrRotate()**
* **RBG_RailGunEffect()**

The LED patterns can string these routines together to make one composite pattern.

FYI diskDownTheDrainOrRotate() was originally written for the Graduation Cap project https://github.com/Mark-MDO47/GraduationCap2017. Some modifications were made for use in the RBG.

## Reprogramming in the Completed Rubber Band Gun

### RBG_SciFi.ino
Take the clear acrylic cover off, **pull back the barrel/solenoid assembly** as if loading, turn the RBG power on, plug in the USB connector, and program. Reverse to disconnect.

NOTE: when the RBG power is on and the USB connector initially gets connected, it continuously resets and pulses the solenoid at an interval of about 1.5 seconds. This might eventually damage the solenoid or its circuitry, so it is important to pull back the barrel/solenoid assembly.

NOTE: I suggest powering on the RBG while programming so the entire RBG is not being powered through our inexpensive clone Arduino Nano.

### Sounds
Take the clear acrylic cover off, turn the RBG power off, hold the YX5200 on the far end while pushing the SD card in and releasing. The SD card should pop out partway; remove it. Connect to your PC and use the instructions for copyem.py described in https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/YX5200.md. Eject the SD card, hold the YX5200 on the far end while pushing the SD card back in. The SD card should stay almost all the way in. Put the clear acrylic cover back on.


### Separate Programming Arduino for Bluetooth Module
There is an Arduino routine **ProgrammingArduino.ino** run on a physically separate Arduino to program the KCX_BT_EMITTER module to recognize your bluetooth speaker or headphones and not just connect to the first one it sees. You can read about this process here:
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/ProgrammingArduino_SerialMonitor_SampleOutput.pdf
