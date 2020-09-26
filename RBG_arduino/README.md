# Arduino Code for the Rubber Band Gun (RBG)
The Arduino handily manages all the tasks including voice menus, storage of user configuration, LED rings, and sound generation. It can do this because it has pre-computed tables built in that guide it, especially for state transitions and special effects.

## Generating Tables for the Code
See the following for an overview of generating the tables for the code:
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/BuildRubberBandGunSoftware.pdf

The file StateTable_minimal.xlsx has multiple tabs that are used to generate the code for the RBG:
* StateTable: the main tab, used in generating the myStateTable struct and associated #define's. This is done by running makeStateTable.py.
* RULES: a list of things to keep in mind when changing the StateTable tab. Sorry, not a tutorial, just notes.
* debugging: where I capture serial port debugging info to diagnose why my stupid code doesn't do what I want and not what I say.
* * There is a list of "grep" commands used to filter this down; then I load the mdo2.txt into a spreadsheet in column B, put the Excel formula after the grep's in A1, and copy down the length. I then sort and remove duplicates.
* YX5200 info: a bunch of info from other sources referenced in the parts directory. Could delete this tab now but it took me a while to make things work reliably.
* Sounds: this includes the text for use in text-to-speech synthesis for the robotic sounds. This is done by running RobotSounds.py. The sound numbers are used in the StateTable tab.
* LEDpatterns: this helps me organize the LED patterns by number and generate lookupLEDpatternTbl.
* FactorySettings: the EEPROM stores four configurable settings for all the sounds and LED effects. In PROGMEM storage is the factory configuration for these four configurable settings. This tab organizes the factory settings and helps me generate the factory_effect_configs table.

## Libraries and Capabilities Used
Once all those tables and #defines are generated and installed in the Arduino code, we still have the rest of the code.

Major libraries used are mostly described in the following:
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/README.md

One other important general thing I uses is PROGMEM and associated F() macro to store constants (strings and various numbers) in program storage instead of RAM.

## The Code Itself
I won't go into too much detail here, but this is a bit of a roadmap to RBG_SciFi.ino .
* getButtonInput() retrieves a bit mask for all the buttons and a few other states like end-of-sound and lock-and-load-status
* RBG_processStateTable() is used to go through the state table in the myStateTable struct
* * it may call RBG_startEffectLED() and/or RBG_startEffectSound()
* doPattern() is used to continue an LED time-sequence pattern. Sounds continue by themselves to completion, so no such routine for sounds
* eeprom_check_init() is used to verify we have a valid EEPROM configuration and if not to load the factory configuration
