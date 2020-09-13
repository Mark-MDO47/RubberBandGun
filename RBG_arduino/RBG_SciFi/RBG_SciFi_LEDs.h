// Mark Olson 2020-08
//
// Major kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC FastLED library and examples!!!
//    A sad note that Daniel Garcia, co-author of FastLED library, was on the dive boat that caught fire and has passed. 
//    Here is some info on the FastLED Reddit https://www.reddit.com/r/FastLED/
//
// I am using an Arduino Nano with a USB mini-B connector
//   example: http://www.ebay.com/itm/Nano-V3-0-ATmega328P-5V-16M-CH340-Compatible-to-Arduino-Nano-V3-Without-Cable/201804111413?_trksid=p2141725.c100338.m3726&_trkparms=aid%3D222007%26algo%3DSIC.MBE%26ao%3D1%26asc%3D20150313114020%26meid%3Dea29973f227743f78772d7a22512af53%26pid%3D100338%26rk%3D1%26rkt%3D30%26sd%3D191602576205
//            V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3
//            32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM
//            http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf
//            http://www.pighixxx.com/test/pinouts/boards/nano.pdf
//
// Using the biggest three of two sets of LED rings: https://smile.amazon.com/gp/product/B07437X7SL/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1
//
// Here is a (somewhat) spec on the 2812b LEDs: https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
// Here is a Worldsemi WS2812B document for download: http://www.world-semi.com/solution/list-4-1.html#108
//
// Kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC Arduino FastLED library and examples!!!
//    https://github.com/FastLED/FastLED
//    https://github.com/FastLED/FastLED/blob/master/examples/Fire2012WithPalette/Fire2012WithPalette.ino
//
// The Arduino pattern code here is pretty much done from scratch by me using the FastLED library.
//    I also tried a few items from Mark Kriegsman's classic DemoReel100.ino https://gist.github.com/kriegsman/062e10f7f07ba8518af6
//
// These LEDs use power that adds up. Can use this to estimate the power
//   http://fastled.io/docs/3.1/group___power.html
//     calculate_max_brightness_for_power_vmA(lots of parameters)
//   https://github.com/FastLED/FastLED/blob/master/power_mgt.cpp
//     static const uint8_t gRed_mW   = 16 * 5; // 16mA @ 5v = 80mW
//     static const uint8_t gGreen_mW = 11 * 5; // 11mA @ 5v = 55mW
//     static const uint8_t gBlue_mW  = 15 * 5; // 15mA @ 5v = 75mW
//     static const uint8_t gDark_mW  =  1 * 5; //  1mA @ 5v =  5mW
//   about 42 milliamps per LED at max brightness WHITE
//
// Calculating wire size (Google for instance wire gauge ampacity 5v dc):
//    https://electronics.stackexchange.com/questions/148648/minimum-wire-gauge-for-5-volt-5-amp-system
//
// connections:
//    Data Pin 3 is used for serial communications with the LEDs for the three rings of LEDs using FastLED
//    Data Pin 2 is used for serial communications with the single LED in the handle
// 
// Recommendations -  ;^)
//    Before connecting the WS2812 to a power source, connect a big capacitor from power to ground.
//      A cap between 100microF and 1000microF should be good. Try to place this cap as close to your WS2812 as possible.
//      Electrolytic Decoupling Capacitors 
//    Placing a small-ish resistor between your Arduino's data output and the WS2812's data input will help protect the data pin. A resistor between 220 and 470 O should do nicely. Try to place the resistor as close to the WS2812 as possible.
//    Keep Wires Short!
//    https://github.com/FastLED/FastLED/wiki/Wiring-leds
//
//

#define BRIGHTMAX 40 // set to 250 for final version

// I am using the biggest three of 6 rings from a 93-LED disk - 72 LEDs
#define NUM_DISKS 1 // definitely not enough room for multiple disks in one Arduino
#define NUM_LEDS_PER_DISK 72
#define NUM_RINGS_PER_DISK 3
#define MAX_LEDS_PER_RING 32
#define MIN_LEDS_PER_RING 16
#define GCD_LEDS_PER_RING 96 // they all divide into 96 evenly
#define NUM_SHADOWS 0  // number of shadow disks

// LED count - number of LEDs in each ring in order of serial access
const uint16_t  leds_per_ring[NUM_RINGS_PER_DISK]  = { MAX_LEDS_PER_RING, 24, 16 }; // MAX_LEDS_PER_RING = 32
const uint8_t   start_per_ring[NUM_RINGS_PER_DISK] = {  0, 32, 56 };
// const uint16_t  leds_per_ringqrtr[NUM_RINGS_PER_DISK]  = { 8, 6, 4 };

#define LED_TYPE     WS2812B
#define COLOR_ORDER  GRB
// #define FRAMES_PER_SECOND  120
// #define deltaMsLED ((unsigned long) (1000 / FRAMES_PER_SECOND))

// Creates an array with the length set by NUM_LEDS_PER_DISK above
// This is the array the library will read to determine how each LED in the strand should be set
static uint32_t data_guard_before = 0x55555555;
static CRGB led_display[(1+NUM_SHADOWS)*NUM_LEDS_PER_DISK]; // 1st set is for display, then shadow1 then shadow2 etc.
static uint32_t data_guard_after = 0x55555555;

// static CRGB led_tmpRing[MAX_LEDS_PER_RING]; // for temp storage
static CRGB led_tmp1; // for temporary storage
static CRGB led_BLACK  = CRGB::Black;
static CRGB led_RED    = CRGB::Red;
static CRGB led_GREEN  = CRGB::Green;
static CRGB led_BLUE   = CRGB::Blue;
static CRGB led_YELLOW = CRGB::Yellow;
static CRGB led_WHITE  = CRGB::White;

typedef struct _brightSpots_t {
  uint8_t posn; // position relative to start of ring; + = counterclockwise. 255 or mNONE terminates list
  CRGB hue;     // color for that position
} brightSpots_t; // end definition

// for RBG_rotateRingAndFade(), only need to do ring 0 and others follow suit
static brightSpots_t windup1BrightSpots[] = {
  { .posn=0, .hue=CRGB::Red },
  { .posn=8, .hue=CRGB::Green },
  { .posn=16, .hue=CRGB::Blue },
  { .posn=24, .hue=CRGB::Yellow },
  { .posn=mNONE, .hue=CRGB::Black },
}; // end windup_ring[] definition


// a few of Mark Kriegsman's classic DemoReel100.ino patterns
void rainbow();
void rainbowWithGlitter();
void confetti();
void bpm();
void juggle();

#define FASTLED_SNGLPTRNLEN 32 // number of shades to cycle through
#define FASTLED_SNGLDWELL  10000 // number of loops to dwell
static CRGB led_sngl_array[FASTLED_SNGLPTRNLEN]; // pattern for handle colors
static CRGB led_sngl = CRGB::Blue; // storage for current color for single LED
static uint8_t which_led_sngl = 0;
static int16_t dwell_led_sngl = 0; // forces first call to output LED
