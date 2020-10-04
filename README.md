# RubberBandGun
A high-tech SciFi imagining of the rubber band gun.

**Table of Contents**
* [Top](#rubberbandgun "Top")
* [Images and Videos](#images-and-videos "Images and Videos")
* [Introduction](#introduction "Introduction")
* [Images](#images "Images")
* [Parts List](#parts-list "Parts List")
* [Sounds](#sounds "Sounds")
* [LED Patterns](#led-patterns "LED Patterns")
* [Extras](#extras "Extras")

## Images and Videos
Here is a NEW (2020-09-25) video of the software running on a prototype:
* https://youtu.be/njpYX-5Zv9Y

![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/image_orange.png "Jim has been busy on the hardware side of the Science Fiction Rubber Band Gun without LED rings")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/IMG_2294_480_640.png "Jim has all the LED rings working")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/RBG_googly_eyes_20200919_210308.png "Mark has the RBG brains working and the RBG has sprouted googly-eyes and a mouth!")

## Introduction
Jim and I are working on a Science-Fiction Rubber Band Gun!

It has three rings of WS2812b 5050 RGB LED Ring proceeding up the barrel, each one larger than the previous in a "blunderbuss" shape. Note: this shape when applied to a handgun was known as a dragon, from which the term dragoon; see https://en.m.wikipedia.org/wiki/Blunderbuss

When fired, it plays a chosen sound. This could be a sequence similar to a "soundified" rendition of two neutron stars colliding
* https://www.gw-openscience.org/audiogwtc1 - search for GW170817

See the [Sounds](#sounds "Sounds") section below and the sounds README for more info.
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/sounds/README.md

At the same time as the sound, the LED rings do patterns to make it look like they are being charged up followed by a sequential pulsing that would convince anyone who knows absolutely less than nothing about such things that a rail-gun effect is propelling the rubber band down the central tube. These rings are composed of WS2812B individually addressable color LEDs controlled by the fantastic FastLED library. See the [LED Patterns](#led-patterns "LED Patterns") section below and the PartsInfo README for more info.
* https://github.com/Mark-MDO47/RubberBandGun/edit/master/PartsInfo/README.md

## Parts List
We are close to working prototype stage using these parts:
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsList.md

The barrel of the Rubber Band Gun is made from wood, with a sliding barrel attachment to assist in stringing the rubber band through the LED rings. The rest including the handgrip is 3-D printed.

The remaining work will mostly be the solenoid release mechanism for the rubber band.

## Sounds
See the Readme.md in https://github.com/Mark-MDO47/RubberBandGun/tree/master/sounds for attribution and other information about the sounds that are used in this project.

See https://github.com/Mark-MDO47/RubberBandGun/blob/master/RBG_arduino/README.md for how sounds are integrated into the Arduino code.

The sounds reside on a 16Gbyte SD card inserted in the YX5200 audio module. Also on that SD card is an ATTRIBUTION directory containing an HTML file with attributions for the sounds used in this project.

Note that the sounds were de-stereo'd, chopped up, and in many cases modified and/or combined with other sounds. There is not a one-to-one onto relationship between the source of the sounds and the sounds as played by the Rubber Band Gun.

## LED Patterns
FastLED is the library I use for controlling these color addressable LEDs

* https://www.arduino.cc/reference/en/libraries/fastled/
* https://github.com/FastLED/FastLED

If you are new to FastLED, look at this famous demo code to see how easy it can be

* https://github.com/FastLED/FastLED/blob/master/examples/DemoReel100/DemoReel100.ino

See https://github.com/Mark-MDO47/RubberBandGun/blob/master/RBG_arduino/README.md for how LED Patterns are integrated into the Arduino code.

## Extras

The basic information from the references below is also on this repository, but the repositories below are more standalone and better for using on your own projects.

Get tips and some code for using the YX5200 Audio module: https://github.com/Mark-MDO47/AudioPlayer-YX5200

Get tips and some code for programming the KCX_BT_EMITTER Bluetooth Audio Transmitter module: https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER

## Guide To README docs
Here are the README docs available on this repository:
* README.md
* PartsList.md
* 3D_model/ReadME.md
* KiCad/README.md
* PartsInfo/README.md
* PartsInfo/YX5200.md
* RBG_arduino/README.md
* sounds/README.md

Here are the other docs available on this repository:
* BuildRubberBandGunSoftware.pdf
* RubberBandGun_wiring.pdf
* FOOF_RBG_Wiring.pdf
* ProgrammingArduino_SerialMonitor_SampleOutput.pdf
* PartsInfo/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
* PartsInfo/Bluetooth Audio Transmitter Module Board 4.1 Stereo Audio GFSK Transceiver Wireless Speaker Headphones KCX_BT_EMITTER 5V_Integrated Circuits_ - AliExpress.pdf
* PartsInfo/FN-M16P+Embedded+MP3+Audio+Module+Datasheet.pdf
* PartsInfo/Gravitech_Arduino_Nano3_0.pdf
* RBG_arduino/YX5200_info/FN-M16P+Embedded+MP3+Audio+Module+Datasheet.pdf
