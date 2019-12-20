# RubberBandGun
A high-tech imagining of the rubber band gun

![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/mockup.png "Mockup of Science Fiction Rubber Band Gun without LED rings")
![alt text](https://github.com/Mark-MDO47/RubberBandGun/blob/master/3D_model/Handle_640_646.png "Handle of Science Fiction Rubber Band Gun")


Jim and I are working on a Science-Fiction Rubber Band Gun!

It will have three rings of WS2812b 5050 RGB LED Ring proceeding up the barrel, each one larger than the previous in a "blunderbuss" shape. Note: this shape when applied to a handgun was known as a dragon, from which the term dragoon; see https://en.m.wikipedia.org/wiki/Blunderbuss

When fired, it will play a sequence similar to the "soundified" rendition of two neutron stars colliding in 2017
https://qz.com/1103444/ligo-listen-to-a-kilonova-the-sound-of-two-stars-colliding-in-space/
or maybe from the two black holes colliding in 2015
https://journals.aps.org/prl/abstract/10.1103/PhysRevLett.116.061102
or a simulation of this. We will shamelessly Hollywoodify this sound to make it ridiculously cool!

At the same time as the sound, the LED rings will be doing trippy patterns to make it look like they are being charged up followed by a sequential pulsing that would convince anyone who knows absolutely less than nothing about such things that a rail-gun effect is propelling the rubber band down the central tube.

# Parts List
We are still in the design stages but expect to use these parts or similar:
- 1 @ clothespin in homage to rubber band guns everywhere
- 1 @ knife switch: https://smile.amazon.com/American-Educational-7-KS-1-Switch-Plastic/dp/B008FRGN06
- 2 @ sets of LED rings: https://smile.amazon.com/gp/product/B07437X7SL/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1
- 2 @ V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3 with 32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM: ***source TBS***
- 1 @ small solenoid for rubber-band release coordinated with sound/light effects: perhaps https://www.adafruit.com/product/2776 or https://www.aliexpress.com/item/33016945460.html
- 1 @ driver circuit for selenoid: ***source TBS*** maybe https://www.adafruit.com/product/2448
https://learn.adafruit.com/adafruit-tb6612-h-bridge-dc-stepper-motor-driver-breakout or maybe https://smile.amazon.com/Youngneer-Raspberry-Arduino-Channel-Opto-Isolated/dp/B07M88JRFY
- 1 @ UBEC 3Amp: ***source TBS***
- 2 @ Button top 18650 Rechargeable Batteries: https://smile.amazon.com/gp/product/B07VGC84Q6/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1
- 1 @ YX5200 sound player: https://smile.amazon.com/Anmbest-YX5200-DFPlayer-Supporting-Arduino/dp/B07JGWMPTF/
- 1 @ small speaker: https://smile.amazon.com/Uxcell-a15080600ux0275-Internal-Magnet-Speaker/dp/B0177ABRQ6/

The body of the Rubber Band Gun is expected to be made from wood, with a sliding barrel attachment to assist in stringing the rubber band through the LED rings. The handgrip is expected to be 3-D printed.

# Other Parts
The YX5200 uses FAT32-formatted TF or microSD card up to 32 GByte

These look like a helpful sites for the YX5200:

https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299

https://github.com/DFRobot/DFRobotDFPlayerMini
