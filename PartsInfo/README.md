# Parts Info

**Table Of Contents**

## Arduino Nano and ATMEGA 328P
Lots of info on the Arduino Nano is found here (diagrams, not schematics)
* https://www.circuitstoday.com/arduino-nano-tutorial-pinout-schematics

The ATMEGA 328P chip used in the Arduino Nano is described here
* http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf

Mapping the ports to the internal registers is described here
* https://www.arduino.cc/en/Reference/PortManipulation

## Sound Module
The YX5200 uses FAT32-formatted TF or microSD card up to 32 GByte. It can play multiple sound file formats including *.wav and *.mp3

Information on the YX5200 sound module and my experience with it can be found in either of these places
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/YX5200.md
* https://github.com/Mark-MDO47/AudioPlayer-YX5200

Best datasheet I could find on the YX5200 chip is found here
* https://github.com/PowerBroker2/DFPlayerMini_Fast/blob/master/extras/FN-M16P%2BEmbedded%2BMP3%2BAudio%2BModule%2BDatasheet.pdf

These look like a helpful sites for the YX5200:
* https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299
* https://github.com/DFRobot/DFRobotDFPlayerMini

This one is a re-write of the DFRobot library; also includes an English language spec sheet in the "extras" directory.
* https://https://github.com/PowerBroker2/DFPlayerMini_Fast

## Bluetooth Module
Get tips and some code for programming the KCX_BT_EMITTER Bluetooth Audio Transmitter module
* https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER

Information on the Bluetooth audio transmitter module is found here (along with ordering info)
* https://www.aliexpress.com/item/33058710334.html

Best information on the Bluetooth module I could find is here; need to translate from Chinese (see next link)
* https://item.taobao.com/item.htm?spm=a21wu.12321156-tw.0.0.7e76d1c7xEOcFZ&id=570274835710

Some more usage info on the Bluetooth module, especially English information on controlling with serial AT commands
* https://www.electro-tech-online.com/threads/kcx_bt_emitter-low-cost-bluetooth-bt-audio-module.158156/

## WS2812 LED and serial communications
FastLED is the library I use for controlling these color addressable LEDs
* https://www.arduino.cc/reference/en/libraries/fastled/
* https://github.com/FastLED/FastLED

If you are new to FastLED, look at this famous demo code to see how easy it can be
* https://github.com/FastLED/FastLED/blob/master/examples/DemoReel100/DemoReel100.ino

Information on the WS2812B is found here
* https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf

The dimensions of the particular ring we used is found here
* https://github.com/Mark-MDO47/RubberBandGun/blob/master/PartsInfo/LED_Dimensions.png

A top-level description of the WS2812B serial protocol (per spec) is found here
* https://www.arrow.com/en/research-and-events/articles/protocol-for-the-ws2812b-programmable-led

Information on doing quick WS2812B I/O is found here (I didn't wind up using it but it was fascinating)
* https://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/
* https://github.com/bigjosh/SimpleNeoPixelDemo
