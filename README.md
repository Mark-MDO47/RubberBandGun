# RubberBandGun
A high-tech imagining of the rubber band gun

![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/image_orange.png "Jim has been busy on the hardware side of the Science Fiction Rubber Band Gun without LED rings")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/IMG_2294_480_640.png "Jim has all the LED rings working")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/RBG_googly_eyes_20200919_210308.png "Mark is debugging the brains and the RBG has sprouted googly-eyes and a mouth!")

Jim and I are working on a Science-Fiction Rubber Band Gun!

Here is a NEW (2020-09-25) video of the software running on a prototype: https://youtu.be/njpYX-5Zv9Y

Just got Bluetooth audio working! Here is a demo of the breadboard firing on an S1 Pro Bluetooth speaker: https://youtu.be/NL99PbIK0Ms

It will have three rings of WS2812b 5050 RGB LED Ring proceeding up the barrel, each one larger than the previous in a "blunderbuss" shape. Note: this shape when applied to a handgun was known as a dragon, from which the term dragoon; see https://en.m.wikipedia.org/wiki/Blunderbuss

When fired, it will play a sequence similar to the "soundified" rendition of two neutron stars colliding in 2017
* https://qz.com/1103444/ligo-listen-to-a-kilonova-the-sound-of-two-stars-colliding-in-space/
or maybe from the two black holes colliding in 2015
* https://journals.aps.org/prl/abstract/10.1103/PhysRevLett.116.061102
or a simulation of this. We will shamelessly Hollywoodify this sound to make it ridiculously cool!

At the same time as the sound, the LED rings will be doing trippy patterns to make it look like they are being charged up followed by a sequential pulsing that would convince anyone who knows absolutely less than nothing about such things that a rail-gun effect is propelling the rubber band down the central tube.

# Parts List
We are close to prototype stage using these parts:
- https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsList.md

The barrel of the Rubber Band Gun is made from wood, with a sliding barrel attachment to assist in stringing the rubber band through the LED rings. The rest including the handgrip is 3-D printed.

# Sounds

See the Readme.md in https://github.com/Mark-MDO47/RubberBandGun/tree/master/sounds for attribution and other information about the sounds that are used in this project.

The sounds reside on a 16Gbyte SD card inserted in the YX5200 module. Also on that SD card is an ATTRIBUTION directory containing an HTML file with attributions for the sounds used in this project.

Note that the sounds were de-stereo'd, chopped up, and in many cases modified and/or combined with other sounds. There is not a one-to-one onto relationship between the source of the sounds and the sounds as played by the Rubber Band Gun.

# Extras

The basic information from the references below is also on this repository, but the repositories below are more standalone and better for using on your own projects.

Get tips and some code for using the YX5200 Audio module: https://github.com/Mark-MDO47/AudioPlayer-YX5200

Get tips and some code for programming the KCX_BT_EMITTER Bluetooth Audio Transmitter module: https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER
