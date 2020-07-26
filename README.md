# RubberBandGun
A high-tech imagining of the rubber band gun

![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/image_orange.png "Jim has been busy on the hardware side of the Science Fiction Rubber Band Gun without LED rings")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/IMG_2209_orange.png "Jim has been busy on the hardware side of the Science Fiction Rubber Band Gun without LED rings")


![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/RBG_wiring_20200314_184839_800_600.png "Mark has been busy on the software side of the Science Fiction Rubber Band Gun and has also been wiring up the RBG")


Jim and I are working on a Science-Fiction Rubber Band Gun!

It will have three rings of WS2812b 5050 RGB LED Ring proceeding up the barrel, each one larger than the previous in a "blunderbuss" shape. Note: this shape when applied to a handgun was known as a dragon, from which the term dragoon; see https://en.m.wikipedia.org/wiki/Blunderbuss

When fired, it will play a sequence similar to the "soundified" rendition of two neutron stars colliding in 2017
https://qz.com/1103444/ligo-listen-to-a-kilonova-the-sound-of-two-stars-colliding-in-space/
or maybe from the two black holes colliding in 2015
https://journals.aps.org/prl/abstract/10.1103/PhysRevLett.116.061102
or a simulation of this. We will shamelessly Hollywoodify this sound to make it ridiculously cool!

At the same time as the sound, the LED rings will be doing trippy patterns to make it look like they are being charged up followed by a sequential pulsing that would convince anyone who knows absolutely less than nothing about such things that a rail-gun effect is propelling the rubber band down the central tube.

Here is a video of the software running on a prototype: https://youtu.be/luf1rrovRuw

# Parts List
We are close to prototype stage using these parts:
- 1 @ clothespin in homage to rubber band guns everywhere
- 1 @ power switch: ***source TBS***
- 1 @ trigger button: ***source TBS***
- 2 @ sets of 5050 WS2812B LED rings, one facing forward and one facing back: https://smile.amazon.com/gp/product/B07437X7SL/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1
- 1 @ V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3 with 32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM: source: my spare parts bin, so some very old ones...
- 1 @ SN74HCT125N quadruple bus buffer so one clone Arduino Nano can drive both sets of WS2812B rings: https://www.digikey.com/product-detail/en/texas-instruments/SN74HCT125N/296-8386-5-ND/376860
- 1 @ small solenoid for rubber-band release coordinated with sound/light effects: https://www.adafruit.com/product/2776 or https://www.aliexpress.com/item/33016945460.html
- 1 @ driver circuit for selenoid: see https://cdn-shop.adafruit.com/product-files/412/solenoid_driver.pdf
  - 1 @ TIP120 Power Darlington Transistor https://www.adafruit.com/product/976
  - 1 @ 1N4004 diode 1A 400V https://www.digikey.com/products/en?keywords=1n4004&utm_adgroup=Multiple%20Suppliers&utm_source=google&utm_medium=cpc&utm_campaign=EN_Product_SKU_E&utm_term=1n4004&utm_content=Multiple%20Suppliers&gclid=Cj0KCQjwu8r4BRCzARIsAA21i_DFDfoGLLpHX4K-k49QZr31T8fjfTEeH7rxbAJlpK54-oPjMCnOPTAaArCGEALw_wcB
  - 1 @ 2.2K Ohm resistor, 1/4 watt
- 1 @ UBEC 3Amp: https://smile.amazon.com/2-Pieces-Hobbywing-Switch-mode-UBEC-Helicopter-Quadcopter/dp/B01GHMW0C0/ref=sr_1_4?keywords=3+amp+ubec&qid=1584751195&sr=8-4
- 2 @ Button top 18650 Rechargeable Batteries: https://smile.amazon.com/gp/product/B07VGC84Q6/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1
- 1 @ YX5200 sound player: https://smile.amazon.com/Anmbest-YX5200-DFPlayer-Supporting-Arduino/dp/B07JGWMPTF/
- 1 @ small speaker: https://smile.amazon.com/Uxcell-a15080600ux0275-Internal-Magnet-Speaker/dp/B0177ABRQ6/
- 3 @ colored push-buttons for configuration of effects: https://www.amazon.com/gp/product/B07C7211PJ/ref=ppx_yo_dt_b_asin_image_o08_s00?ie=UTF8&psc=1
- 1 @ DigiKey (https://digikey.com) 4610X-AP1-103LFCT-ND RES ARRAY 9 RES 10K OHM 10SIP
- 1 @ 220 Ohm resistor, 1/4 watt (optional)
- 1 @ 1K Ohm resistor, 1/4/watt (absolutely needed)

The barrel of the Rubber Band Gun is made from wood, with a sliding barrel attachment to assist in stringing the rubber band through the LED rings. The rest including the handgrip is 3-D printed.

# Other Parts
The YX5200 uses FAT32-formatted TF or microSD card up to 32 GByte

These look like a helpful sites for the YX5200:

https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299

https://github.com/DFRobot/DFRobotDFPlayerMini

This one is a re-write of the DFRobot library; also includes an English language spec sheet in the "extras" directory.
https://https://github.com/PowerBroker2/DFPlayerMini_Fast

For a description of my experiences with using this module (I had some challenges), see the Readme.md in https://github.com/Mark-MDO47/RubberBandGun/tree/master/RBG_arduino.

# Sounds

See the Readme.md in https://github.com/Mark-MDO47/RubberBandGun/tree/master/sounds for attribution and other information about the sounds that are used in this project.

The sounds reside on a 16Gbyte SD card inserted in the YX5200 module. Also on that SD card is an ATTRIBUTION directory containing an HTML file with attributions for the sounds used in this project.

Note that the sounds were de-stereo'd, chopped up, and in many cases modified and/or combined with other sounds. There is not a one-to-one onto relationship between the source of the sounds and the sounds as played by the Rubber Band Gun.
