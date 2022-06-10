# RubberBandGun
A high-tech SciFi imagining of the rubber band gun.

Both working prototypes were shown at the Asheville Maker Faire on May 07, 2022 in Asheville, N.C. Estimates are that 100 people fired rubber bands out of the RBG!
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/IMG_6875_AshelandMakerFaire2022.png "Both Rubber Band Guns at Asheville Maker Faire on May 2022")

**Table of Contents**
* [Top](#rubberbandgun "Top")
* [Videos](#videos "Videos")
* [Images](#images "Images")
* [Introduction](#introduction "Introduction")
* [Parts List](#parts-list "Parts List")
* [Sounds](#sounds "Sounds")
* [LED Patterns](#led-patterns "LED Patterns")
* [Extras](#extras "Extras")
* [Guide to README and Other Docs](#guide-to-readme-and-other-docs "Guide to README and Other Docs")

## Videos
Here is a NEW (2020-09-25) video of the software running on a prototype:
* https://youtu.be/njpYX-5Zv9Y

## Images
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/RBG_lockedloaded_600x800.png "Top View of Jim's assembled SINGLETON SILVER RBG with solenoid and sliding barrel")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/both_800_600.png "Both RBGs side by side")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/RBG_loaded_800x350.png "Loading a rubber band in Jim's assembled SINGLETON SILVER RBG with solenoid and sliding barrel")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/OrangeExtended_854_641.jpg "Extended view of ORANGE SIDEWINDER Science Fiction Rubber Band Gun with Motor attachment")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/OrangeTop_854_641.jpg "Top view of ORANGE SIDEWINDER Science Fiction Rubber Band Gun with Motor attachment")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/OrangeMotorElec_854_641.jpg "View of ORANGE SIDEWINDER Science Fiction Rubber Band Gun Motor electronics")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/OrangeDisplayStand_854_641.jpg "View of Display Stand for ORANGE SIDEWINDER Science Fiction Rubber Band Gun")

## Introduction
Jim and I made a Science-Fiction Rubber Band Gun!

It has three rings of WS2812b 5050 RGB LED Ring proceeding up the barrel, each one larger than the previous in a "blunderbuss" shape. Note: this shape when applied to a handgun was known as a dragon, from which the term dragoon; see https://en.m.wikipedia.org/wiki/Blunderbuss

When fired, it plays a chosen sound. This could be a sequence similar to a "soundified" rendition of two neutron stars colliding
* https://www.gw-openscience.org/audiogwtc1 - search for GW170817

See the [Sounds](#sounds "Sounds") section below and the sounds README for more info.
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/sounds/README.md

At the same time as the sound, the LED rings do patterns to make it look like they are being charged up followed by a sequential pulsing that would convince anyone who knows absolutely less than nothing about such things that a rail-gun effect is propelling the rubber band down the central tube. These rings are composed of WS2812B individually addressable color LEDs controlled by the fantastic FastLED library. See the [LED Patterns](#led-patterns "LED Patterns") section below and the PartsInfo README for more info.
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/README.md

And the RBG is a talking Rubber Band Gun! It can use its own built-in speaker or connect to a Bluetooth speaker, it has voice menus to allow configuration of sounds and LED effects. The video at https://youtu.be/njpYX-5Zv9Y goes through some of the menus using a Bluetooth speaker.

## Parts List
We have two working prototypes using these parts. The prices and parts availability have not been updated recently.
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsList.md

The barrel of the Rubber Band Gun is made from wood, with a sliding barrel attachment to assist in stringing the rubber band through the LED rings. The rest including the handgrip is 3-D printed.

### Release Mechanism

The "SILVER" SINGLETON RBG uses the solenoid release mechanism through the CLOTHESPIN to fire the rubber band.

Jim felt like this wasn't reliable enough and designed a SIDEWINDER mechanism that uses a motor to release one or more rubber bands at a time; this was used on the "ORANGE" RBG.

The current parts list and schematics contain both the CLOTHESPIN (SOLENOID) and the SIDEWINDER (MOTOR) mechanisms.

Git tag Silver-1.0 is the version of software that is in the SILVER CLOTHESPIN (SOLENOID) RBG
* There is a definition of DLYSOLENOID in RBG_SciFi_StatesAndInputs.h that needs to be adjusted to account for the differences. See the comments near that definition if interested.

Development is continuing to make a minimum as well as a maximum activation time for the solenoid or motor mechanism. This will get a tag when complete and tested.
* This uses DLYSOLENOID_MIN and DLYSOLENOID_MAX. The Silver-1.0 version DLYSOLENOID corresponds to DLYSOLENOID_MAX in the later versions.

## Sounds

All sounds for the RBG were processed by Audacity, which can be found at https://www.audacityteam.org/

Voice sounds were generated by the eSpeak text-to-speech program version 1.48.04. The original code can be found at http://espeak.sourceforge.net/ while current development is at https://github.com/espeak-ng/espeak-ng
* Postprocessing was done by Audacity

The sounds reside on a 16Gbyte SD card inserted in the YX5200 audio module. Also on that SD card is an ATTRIBUTION directory containing an HTML file with attributions for the sounds used in this project.

Note that the sounds were de-stereo'd, chopped up, and in many cases modified and/or combined with other sounds. There is not a one-to-one onto relationship between the source of the sounds and the sounds as played by the Rubber Band Gun.

* As for many aspects of the RGB, the text-to-speech is semi-automated with StateTable_minimal.xlsx used to control generation and to associate sounds with RBG events.
* See https://github.com/Mark-MDO47/RubberBandGun/blob/master/sounds/README.md

### Sound Effects
See the Readme.md in https://github.com/Mark-MDO47/RubberBandGun/tree/master/sounds for attribution and other information about the sounds that are used in this project.

See https://github.com/Mark-MDO47/RubberBandGun/blob/master/RBG_arduino/README.md for how sounds are integrated into the Arduino code.

### Voice Audio
A few of the voices are recordings of members of my family or of me. The remainder are generated by the eSpeak text to speech program and post-processed by Audacity.

## LED Patterns
FastLED is the library I use for controlling these color addressable LEDs

* https://www.arduino.cc/reference/en/libraries/fastled/
* https://github.com/FastLED/FastLED

If you are new to FastLED, look at this famous demo code to see how easy it can be

* https://github.com/FastLED/FastLED/blob/master/examples/DemoReel100/DemoReel100.ino

See https://github.com/Mark-MDO47/RubberBandGun/blob/master/RBG_arduino/README.md for how LED Patterns are integrated into the Arduino code.
* As for many aspects of the RGB, the LED Patterns are semi-automated with StateTable_minimal.xlsx to associate LED Patterns with RBG events.

## Extras

The basic information from the references below is also on this repository, but the repositories below are more standalone and better for using on your own projects.

Get tips and some code for using the YX5200 Audio module: https://github.com/Mark-MDO47/AudioPlayer-YX5200

Get tips and some code for programming the KCX_BT_EMITTER Bluetooth Audio Transmitter module: https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER
Be aware that the KCX_BT_EMITTER module expects 5V power and 5V serial interface signals; I have heard of people who found that the ESP32 did not work when directly used as the Programming Arduino. This can be easily accommodated by using a true Arduino version or a cheap clone Arduino Uno or Arduino Nano classic.

## Guide to README and Other Docs
Here are the README docs available on this repository:
* [This README File](https://github.com/Mark-MDO47/RubberBandGun/blob/master/README.md "This README File")
* [Parts List](https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsList.md "Parts List")
* [Arduino Code Description](https://github.com/Mark-MDO47/RubberBandGun/blob/master/RBG_arduino/README.md "Arduino Code Description")
* [Parts Info Overview](https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/README.md "Parts Info Overview")
* [YX5200 Audio Module Info](https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/YX5200.md "YX5200 Audio Module Info")
* [Sound Sources and Attribution](https://github.com/Mark-MDO47/RubberBandGun/blob/master/sounds/README.md "Sound Sources and Attribution")
* [KiCad files for Schematic-Style Rubber Band Gun Wiring PDF](https://github.com/Mark-MDO47/RubberBandGun/blob/master/KiCad/README.md "KiCad files for Schematic-Style Rubber Band Gun Wiring PDF")
* [Autocad Fusion 360 files for 3D Printed Parts](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/ReadME.md "Autocad Fusion 360 files for 3D Printed Parts")


Here are some other docs available on this repository:
* [Schematic-Style Rubber Band Gun Wiring PDF](https://github.com/Mark-MDO47/RubberBandGun/blob/master/RubberBandGun_Wiring.pdf "Schematic-Style Rubber Band Gun Wiring PDF")
* [Overview of Building the Rubber Band Gun Software](https://github.com/Mark-MDO47/RubberBandGun/blob/master/BuildRubberBandGunSoftware.pdf "Overview of Building the Rubber Band Gun Software")
* [How To Program the KCX-BT-EMITTER BlueTooth Module](https://github.com/Mark-MDO47/RubberBandGun/blob/master/ProgrammingArduino_SerialMonitor_SampleOutput.pdf "How To Program the KCX-BT-EMITTER BlueTooth Module")
* [Wiring Tips when Building the FOOF RBG](https://github.com/Mark-MDO47/RubberBandGun/blob/master/FOOF_RBG_Wiring.pdf "Wiring Tips when Building the FOOF RBG")

Here are some other useful docs etc. available on other repositories:
* [Details of Microchip Technology ATMega Processors including 328P used in Arduino Nano](http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf "Details of Microchip Technology ATMega Processors including 328P used in Arduino Nano")
* [Best Detailed YX5200 Audio Module DataSheet I Could Find](https://github.com/PowerBroker2/DFPlayerMini_Fast/blob/master/extras/FN-M16P%2BEmbedded%2BMP3%2BAudio%2BModule%2BDatasheet.pdf "Best Detailed YX5200 Audio Module DataSheet I Could Find")
* [AT Commands for KCX-BT-EMITTER Bluetooth Audio Module (use Google Translate)](https://item.taobao.com/item.htm?spm=a21wu.12321156-tw.0.0.7e76d1c7xEOcFZ&id=570274835710 "AT Commands for KCX-BT-EMITTER Bluetooth Audio Module (use Google Translate)")
* [Electro-Tech-Online.com Forum Discussion on AT Commands for KCX-BT-EMITTER](https://www.electro-tech-online.com/threads/kcx_bt_emitter-low-cost-bluetooth-bt-audio-module.158156/ "Electro-Tech-Online.com Forum Discussion on AT Commands for KCX-BT-EMITTER")
* [Details of WorldSemi WS2812B LED Operation](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf "Details of WorldSemi WS2812B LED Operation")
* [Solenoid Driver Circuit from Adafruit](https://cdn-shop.adafruit.com/product-files/412/solenoid_driver.pdf "Solenoid Driver Circuit")
