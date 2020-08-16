# Parts Info

## Arduino Nano and ATMEGA 328P
Lots of info on the Arduino Nano is found here (diagrams, not schematics)
* https://www.circuitstoday.com/arduino-nano-tutorial-pinout-schematics

The ATMEGA 328P chip used in the Arduino Nano is described here
* http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf

Mapping the ports to the internal registers is described here
* https://www.arduino.cc/en/Reference/PortManipulation

## Sound and BlueTooth Modules
Information on the YX5200 sound module and my experience with it is found here
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/YX5200.md

Best datasheet I could find on the YX5200 chip is found here
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/RBG_arduino/YX5200_info/FN-M16P%2BEmbedded%2BMP3%2BAudio%2BModule%2BDatasheet.pdf

Information on the BlueTooth audio transmitter is found here (along with ordering info)
* https://www.aliexpress.com/item/33058710334.html

## WS2812 LED and serial communications
Information on the WS2812B is found here
* https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf

The dimensions of the particular ring we used is found here
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/LED_Dimensions.png

A top-level description of the WS2812B serial protocol (per spec) is found here
* https://www.arrow.com/en/research-and-events/articles/protocol-for-the-ws2812b-programmable-led

Information on doing quick WS2812B I/O is found here (I used this for the single internal LED)
* https://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/
* https://github.com/bigjosh/SimpleNeoPixelDemo
