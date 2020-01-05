// Author: Mark Olson 2019-11-03
//
// Rubber Band Gun - https://github.com/Mark-MDO47/RubberBandGun
// RBG - A high-tech imagining of the rubber band gun
//
// Major kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC FastLED library and examples!!!
//    A sad note that Daniel Garcia, co-author of FastLED library, was on the dive boat that caught fire and has passed. 
//    Here is some info on the FastLED Reddit https://www.reddit.com/r/FastLED/
//
// As usual, I am using a mix of my hand-coded LED patterns plus a few from Mark Kriegsman's classic DemoReel100.ino https://github.com/FastLED/FastLED/tree/master/examples/DemoReel100
//
// I am using an Arduino Nano with a USB mini-B connector
//   example: http://www.ebay.com/itm/Nano-V3-0-ATmega328P-5V-16M-CH340-Compatible-to-Arduino-Nano-V3-Without-Cable/201804111413?_trksid=p2141725.c100338.m3726&_trkparms=aid%3D222007%26algo%3DSIC.MBE%26ao%3D1%26asc%3D20150313114020%26meid%3Dea29973f227743f78772d7a22512af53%26pid%3D100338%26rk%3D1%26rkt%3D30%26sd%3D191602576205
//            V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3
//            32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM
//            http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf
//            http://www.pighixxx.com/test/pinouts/boards/nano.pdf
//
// Using the biggest three rings of two sets of LED disks, one facing forward and one facing back: https://smile.amazon.com/gp/product/B07437X7SL/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1
//
// Also using a YX5200 sound player
//   The YX5200 uses FAT32-formatted TF (or SD ?) card up to 32 GByte
//   These look like a helpful sites for the YX5200:
//   https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299
//   https://github.com/DFRobot/DFRobotDFPlayerMini
// The YX5200 interface code is based on the "FullFunction.ino" DFPlayer.
//   this uses the GNU Lesser General Public License.
//
// Thank you LIGO folks for making the fun sounds available to non-researchers!
// https://www.ligo.org/index.php
// https://www.ligo.org/detections/O1O2catalog.php
// https://www.gw-openscience.org/audiogwtc1/
// I particularly like GW170817-template.wav; it has the ramp-up and then the kick at the end.
//
// Here are the files I used, modified, and combined (or plan to use) for the sounds (other than GW170817-template.wav above)
// | Tag        | File Name                                      | URL                             | Who |
// | ---        | ---                                            | ---                             | --- |
// | zero/1.0/  | 407052__sojan__power-charge.flac               | https://freesound.org/s/193610/ | crashoverride61088 |
// | zero/1.0/  |  397254__screamstudio__loading.wav             | https://freesound.org/s/397254/ | ScreamStudio |
// | zero/1.0/  | 145209__lensflare8642__shotgun-sounds.mp3      | https://freesound.org/s/145209/ | lensflare8642 |
// | by/3.0/    | 216096__richerlandtv__u-f-o.mp3                | https://freesound.org/s/216096/ | RICHERlandTV |
// | by/3.0/    | 88635__uair01__bicycle-picture-in-spectrum.wav | https://freesound.org/s/88635/  | uair01 |
// | by/3.0/    | 7967__cfork__boing-raw.aiff                    | https://freesound.org/s/7967/   | cfork |
// | by/3.0/    | 383205__spiceprogram__loading-sound.wav        | https://freesound.org/s/383205/ | SpiceProgram  |
// | by-nc/3.0/ | 179281__timbre__boingy-sweep.flac              | https://freesound.org/s/179281/ | Timbre |
// | zero/1.0/  | 380886__morganpurkis__doom-shotgun-2017.wav    | https://freesound.org/s/380886/ | morganpurkis |
// | zero/1.0/  | 500418__dj-somar__intro-reverso-craver-microbrute.wav | https://freesound.org/s/500418/ | DJ_SoMaR |
// | by/3.0/    | 272068__ichbinjager__shotgun-action.wav        | https://freesound.org/s/272068/ | IchBinJager |
// | by/3.0/    | 431117__inspectorj__door-front-opening-a.wav   | https://freesound.org/s/431117/ | inspectorj |
// | zero/1.0/  | 404068__swordofkings128__backyard-gate-open.wav | https://freesound.org/s/404068/ | swordofkings128 |
// | by/3.0/    | 96964__gabisaraceni__porta-abrindo-5.wav       | https://freesound.org/s/96964/ | gabisaraceni |
// | by/3.0/    | 275537__wjoojoo__contact-mic-on-satellite-dish04.wav | https://freesound.org/s/275537/ | wjoojoo |
// | zero/1.0/  | 352852__josepharaoh99__game-style-laser-beam.wav | https://freesound.org/s/352852/ | josepharaoh99 |
// | by/3.0/    | 417363__xcreenplay__boing-massive-kick.wav     | https://freesound.org/s/417363/ | xcreenplay |
// | by/3.0/    | 221875__hero-of-the-winds__spring-boing.wav    | https://freesound.org/s/221875/ | hero-of-the-winds |
// | by/3.0/    | 240297__jalastram__abstract-guitar-sfx-003.wav | https://freesound.org/s/240297/ | jalastram |
// | zero/1.0/  | 383760__deleted-user-7146007__laboratory-mad-scientist-science-fiction-sci-fi.wav | https://freesound.org/s/383760/ | deleted-user-7146007 |
// | by/3.0/    | 417131__cuddlenucks__science-fiction-noise-3.wav | https://freesound.org/s/417131/ | cuddlenucks |
// | zero/1.0/  | 170136__lazr2012__machinery-bo.flac            | https://freesound.org/s/170136/ | lazr2012 |
// | by/3.0/    | 169292__lazr2012__haywirefusionator.ogg        | https://freesound.org/s/169292/ | lazr2012 |
// | by-nc/3.0/ | 165483__timbre__glitch-voice-ep-mp3.mp3        | https://freesound.org/s/165483/ | timbre |
// | zero/1.0/  | 162814__timgormly__spaceship-4.aiff            | https://freesound.org/s/162814/ | timgormly |
// | by-nc/3.0/ | 91296__timbre__bwaang-2-reverb.mp3             | https://freesound.org/s/91296/ | timbre |
//
// | Tag        | Name                                               | URL |
// | ---        | ---                                                | --- |
// | zero/1.0/  | Creative Commons 0 License                         | https://creativecommons.org/publicdomain/zero/1.0/ |
// | by/3.0/    | Creative Commons Attribution License               | https://creativecommons.org/licenses/by/3.0/ |
// | by-nc/3.0/ | Creative Commons Attribution Noncommercial License | https://creativecommons.org/licenses/by-nc/3.0/ |
//

#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port
#include <EEPROM.h>                          // to store configuration info

#include "FastLED.h"                         // to manipulate WS2812b 5050 RGB LED Rings
#include "DFRobotDFPlayerMini.h"             // to communicate with the YX5200 audio player

#include "RBG_SciFi_StatesAndInputs.h"       // state tables and input definitions
#include "RBG_SciFi_LEDs.h"                  // LED structural and pattern definitions

#define SERIALDEBUG 1                        // serial debugging
#define REAL_BUTTONS 1                       // use actual buttons

#define DONOTEXPLAINBITS 1                   // don't explain the bits - existing routine uses too much RAM
#define DEBUG_STATE_MACHINE 1                // 1 to show state machine internals for transitions
#define DEBUG_INPUTS 1                       // 1 to show all inputs
#define DEBUG_SHOW_MSEC 1                    // use globalLoopCount for millis() display not loopcount


SoftwareSerial mySoftwareSerial(DPIN_SWSRL_RX, DPIN_SWSRL_TX); // to talk to YX5200 audio player
DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player
void DFsetup();                                                // how to initialize myDFPlayer

#define DFPRINTDETAIL (1&SERIALDEBUG)     // if need detailed status from myDFPlayer
// #define DFPRINTDETAIL 0                      // will not print detailed status from myDFPlayer
#if DFPRINTDETAIL // routine to do detailed debugging
  void DFprintDetail(uint8_t type, int value); // definition of call
#else  // no DFPRINTDETAIL
  #define DFprintDetail(type, value) // nothing at all
#endif // #if DFPRINTDETAIL

static uint32_t globalLoopCount = 0;

static uint8_t gHue = 0; // rotating "base color" used by Demo Reel 100
CRGBPalette16 gPal; // palette for Fire2012WithPalette()
static uint16_t gSeed = ((uint16_t) 42); // my favorite is 47 but the whole world loves 42 and HHG2TG
#if FASTLED_FIRE_PATTERN // only used for Fire pattern
CRGB dark_color_palette[1]  = { CRGB::DarkGreen, CRGB::Red,    CRGB::Blue, CRGB::DarkOrange };
CRGB light_color_palette[1] = { CRGB::LimeGreen, CRGB::Yellow, CRGB::Aqua, CRGB::Gold };
#endif // FASTLED_FIRE_PATTERN
static uint16_t nowVinputRBG; // latest button inputs, to compare with previous in myState


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// setup()
//   initializes hardware serial port for general debug
//   initializes SoftwareSerial for DFPlayer audio player YX5200 control
//   initializes push button pins
//   initializes FastLED library
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);         // this is for general debug

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println();
  Serial.println(F("FOOF SciFi RBG init...")); 

  mySoftwareSerial.begin(9600); // this is control to DFPlayer audio player

  // initialize the input pins. Not sure if my Nano actually has a pullup...
  //    fortunately the RBG controller board has a 10K pullup resistor
  pinMode(DPIN_BTN_TRIGGER, INPUT_PULLUP); // trigger
  pinMode(DPIN_BTN_YELLOW,  INPUT_PULLUP); // configuration button
  pinMode(DPIN_BTN_GREEN,   INPUT_PULLUP); // configuration button
  pinMode(DPIN_BTN_BLACK,   INPUT_PULLUP); // configuration button
  pinMode(DPIN_BTN_EXTRA,   INPUT_PULLUP); // EXTRA configuration button
  pinMode(DPIN_AUDIO_BUSY,  INPUT_PULLUP); // tells when audio stops
  pinMode(DPIN_LOCK_LOAD,   INPUT_PULLUP); // tells if barrel is locked and loaded
  // and the output pin
  pinMode(DPIN_SOLENOID,   OUTPUT);        // fires the rubber band

  // make sure solenoid is not drawing power
  RBG_specialProcSolenoid(); // digitalWrite(DPIN_SOLENOID, LOW);

  // initialize the DFPlayer audio player
  DFsetup();

  // initialize the FastLED library for our setup
  // according to Amazon comments: Library configuration used was WS2812B GRB (not RGB). Library call: FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);. Everything worked as expected.
  //    this was for the graduation cap: FastLED.addLeds<NEOPIXEL,DPIN_FASTLED>(led_display, NUM_LEDS_PER_DISK);
  FastLED.addLeds<WS2812B,DPIN_FASTLED,GRB>(led_display, NUM_LEDS_PER_DISK);
  FastLED.setBrightness(BRIGHTMAX); // we will do our own power management
  // initialize led_display
  RBG_diskInitBrightSpots(windup1BrightSpots, &led_BLACK); // FIXME need initialize for this pattern

  // if needed, initialize EEPROM variables
  eeprom_check_init();

  printAllMyState();
  printAllMyInputs();
  Serial.println(F("FOOF SciFi RBG init COMPLETE\n"));

} // end setup()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  loop()
//     Get the inputs - buttons, barrel, sound ended
//     Use our state table and state and inputs to calculate next state
//     Determine if we need to change LED pattern and/or sound
//     If needed, release the rubber band and set timer to stop the solenoid current later
//
void loop() {

  // put your main code here, to run repeatedly:

  static uint16_t preVinputRBG = 65535;

  myState.timerNow = millis();
  #if DEBUG_SHOW_MSEC
  globalLoopCount = myState.timerNow;
  #endif // DEBUG_SHOW_MSEC

  // handle solenoid OFF processing quickly no matter how long the shooting sound is
  if ((myState.timerForceSolenoidLow > 0) && (myState.timerNow > myState.timerForceSolenoidLow)) {
    RBG_specialProcSolenoid(); // digitalWrite(DPIN_SOLENOID, LOW);
  }

  // see if time to run the state machine and process inputs
  if ((myState.timerNow-myState.timerPrevState) >= 40) { // || (myState.VinputRBG != nowVinputRBG)) { THIS MAKES RELEASING TRIGGER TOO FAST AFFECT SOUND START
    nowVinputRBG = getButtonInput();
    if (preVinputRBG != nowVinputRBG) {
      Serial.print(F("DEBUG loop() - nowVinputRBG 0x")); Serial.print(nowVinputRBG, HEX); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
    }
    preVinputRBG = nowVinputRBG;
    nowVinputRBG = RBG_processStateTable(nowVinputRBG);
    myState.timerPrevState = myState.timerNow;
    myState.VinputRBG = nowVinputRBG;
  } // end wait for next State activity

  // see if time to run the LED patterns
  if ((myState.timerNow-myState.timerPrevLEDstep) >= myState.ptrnDelayLEDstep) {
    gHue += 3; // rotating "base color" used by Demo Reel 100 patterns
    checkDataGuard();
    doPattern(myStateTable[myState.tableRow].efctLED);
    checkDataGuard();
    FastLED.show();
    myState.timerPrevLEDstep = myState.timerNow;
    globalLoopCount += 1;
  } // end wait for next LED activity

}  // end loop()

// ******************************** LED UTILITIES ****************************************

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// doPattern(efctLED) - start or step the pattern
//
#define DEBUG_DPtrn 0
//
void doPattern(uint16_t efctLED) {
  static uint16_t prevEfctLED = mNONE;
  static uint16_t numSteps = 0;
  uint16_t nowEfctLED;

  // FIXME convert via EEPROM
  nowEfctLED = (efctLED & 0x00FF); // just the effect number

  // configurable sounds are zero mod 10; we get config from EEPROM
  if (EFCT_IS_EEP(nowEfctLED)) {
    // configurable sound using EEPROM
    nowEfctLED += EEPROM.read(EEPOFFSET(nowEfctLED)+eeLEDSave);
  }

  #if DEBUG_DPtrn
  Serial.print(F(" DEBUG doPattern efctLED ")); Serial.print(efctLED); Serial.print(F(" prevEfctLED ")); Serial.print(prevEfctLED); Serial.print(F(" final myEfctLED ")); Serial.println(prevEfctLED);
  #endif // DEBUG_DPtrn

  switch (nowEfctLED) {

    case PTRNLED_OFF: // 258 = OFF
    default:
      if (prevEfctLED != efctLED) { // initialize
        for (uint8_t idx = 0; idx < NUM_RINGS_PER_DISK; idx++) {
          led_display[idx] = CRGB::Black;
        }
      } // there is no "step"
      break;

    case PTRNLED_pwron1: // RBG_diskDownTheDrainOrRotate counterclockwise, drain
      if ((prevEfctLED != efctLED) || (numSteps > (10+NUM_LEDS_PER_DISK))) { // initialize
        RBG_ringRotateAndFade(mNONE, 0, windup1BrightSpots); // FIXME - initialization from other effect
        numSteps = 0;
      } else { // step
        RBG_diskDownTheDrainOrRotate(2);
        numSteps += 1;
      }
      break;

    case PTRNLED_open1: // RBG_diskDownTheDrainOrRotate clockwise, rotate through
    case PTRNLED_lock1:
    case PTRNLED_uniq1:
      if (prevEfctLED != efctLED) { // initialize
        prevEfctLED = efctLED;
        RBG_ringRotateAndFade(mNONE, 0, windup1BrightSpots); // FIXME - initialization from other effect
        RBG_diskDownTheDrainOrRotate(0);
      } else { // step
        RBG_diskDownTheDrainOrRotate(-1);
      }
      break;

    case PTRNLED_shoot1:
      bpm();
      break;

    case PTRNLED_windup1:
      // rainbowWithGlitter();
      juggle();
      break;

    case PTRNLED_wait1:
       bpm_rings();
       // confetti();
       break;

/*
    case PTRNLED_ringRotateAndFade_windup1: // 3 = RBG_ringRotateAndFade windup pattern1
      if (prevEfctLED != efctLED) { // initialize
        prevEfctLED = efctLED;
        RBG_ringRotateAndFade(mNONE, 0, windup1BrightSpots);
      } else { // step
        
      }
      break;
    case 4: // 4 = 
      if (prevEfctLED != efctLED) { // initialize
        prevEfctLED = efctLED;
      } else { // step
        
      }
      break;
*/
  } // end switch

  // take care of previous effect so can do initialization where needed
  prevEfctLED = efctLED;
} // end doPattern()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_diskDownTheDrainOrRotate(direction) - 
//
// direction - 0="initialize", +/- 1 = rotate through, +/- 2 = down drain. With these rings, + is counter-clockwise and - is clockwise
// 
// initialize does not overwrite current colors in disk
//
// #define DEBUG_DDtD 1
void RBG_diskDownTheDrainOrRotate(int8_t direction) {
  int8_t idx;

  #ifdef DEBUG_DDtD
  Serial.print(F(" DEBUG_DDtD direction=")); Serial.println(direction);
  #endif // DEBUG_DDtD

  if (direction > (NUM_RINGS_PER_DISK-1)) {
    // initialize
    myState.ptrnDelayLEDstep = DLYLED_diskDownTheDrain;
  } else {
    // do pattern
    RBG_diskRotateOrDrain(direction, &led_BLACK);
  } // end do pattern

} // end RBG_diskDownTheDrainOrRotate()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_ringRotateAndFade(whichRing, rotate96, brightSpots) - rotate a single ring, fade to black, add in new bright spots
//
// whichRing - which ring to rotate, 0 through (NUM_RINGS_PER_DISK-1) {2 for RBG}
//                value = mNONE (255) means initialize entire disk (actually, anything > 2)
// rotate96 - fraction of GCD_LEDS_PER_RING to rotate, +/-. With these rings, + is counter-clockwise and - is clockwise
// brightSpots - list of positions within ring and color for bright spots
// 
// writes over led_tmpRing and led_display
//
// #define DEBUG_RRandF 1
void RBG_ringRotateAndFade(uint8_t whichRing, int8_t rotate96, brightSpots_t* brightSpots) {
  int8_t idx;
  static int16_t startLocPerRing[NUM_RINGS_PER_DISK]; // (95 + 95 = 190) > 127 so int8_t will not work

  if (whichRing > (NUM_RINGS_PER_DISK-1)) {
    // initialize
    #ifdef DEBUG_RRandF
    Serial.print(F(" DEBUG_RRandF initialize whichRing=")); Serial.println(whichRing);
    #endif // DEBUG_RRandF
    myState.ptrnDelayLEDstep = DLYLED_ringRotateAndFade;
    RBG_diskInitBrightSpots(brightSpots, &led_BLACK);
    for (idx=0; idx < NUM_RINGS_PER_DISK; idx++) {
      startLocPerRing[idx] = 0;
    }
    // end initialize
  } else if ((whichRing >= 0) && (whichRing <= (NUM_RINGS_PER_DISK-1)) && (0 != rotate96)) {
    // process individual ring
    int8_t num96PerLED = 96 / leds_per_ring[whichRing];
    int16_t numHere = startLocPerRing[whichRing] / num96PerLED;
    int16_t numEnd = (startLocPerRing[whichRing] + rotate96) / num96PerLED;
    int8_t moveBy;
    
    if (rotate96 < 0) {
      moveBy = -1;
    } else {
      moveBy = 1;
    }
    startLocPerRing[whichRing] = (startLocPerRing[whichRing] + rotate96) % 96;
    #ifdef DEBUG_RRandF
    Serial.print(F(" DEBUG_RRandF ERROR CALL whichRing=")); Serial.println(whichRing);
    #endif // DEBUG_RRandF
    // end process individual ring
  } // end check on whichRing
} // end RBG_ringRotateAndFade()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_diskInitBrightSpots(brightSpots, color) - 
//
// brightSpots - list of positions within ring and color for bright spots
// pColor    - pointer to color to use as fill (typically &CRGB::Black)
//
void RBG_diskInitBrightSpots(brightSpots_t* brightSpots, CRGB* pColor) {
  uint8_t idx, idxRing;

  for (idx=0; idx < NUM_LEDS_PER_DISK; idx++) {
    led_display[idx] = *pColor;
  } // end set all to pColor
  for (idxRing=0; idxRing<NUM_RINGS_PER_DISK; idxRing++) {
    for (idx=0; (brightSpots[idx].posn < leds_per_ring[idxRing]) && (idx < leds_per_ring[idxRing]); idx++) {
      led_display[brightSpots[idx].posn+start_per_ring[idxRing]] = brightSpots[idx].hue;
    } // end for all bright spots this ring
  } // end for all rings
} // end RBG_diskInitBrightSpots()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_diskRotateOrDrain(direction, pColor) - 
//
// direction - +/- 1 = rotate through, +/- 2 = down drain. With these rings, + is counter-clockwise and - is clockwise
// pColor    - pointer to color to use as fill (typically &CRGB::Black)
// 
void RBG_diskRotateOrDrain(int8_t direction, CRGB* pColor) {
  // do rotate/drain
  if (direction > 0) { // counterclockwise
    if (1 == direction) { led_tmp1 = led_display[0]; } else { led_tmp1 = *pColor; }
    for (int idx=1; idx < NUM_LEDS_PER_DISK; idx++) {
      led_display[idx-1] = led_display[idx];
    }
    led_display[NUM_LEDS_PER_DISK-1] = led_tmp1;
  } else  { // clockwise
    if (-1 == direction) { led_tmp1 = led_display[NUM_LEDS_PER_DISK-1]; } else { led_tmp1 = *pColor; }
    for (int idx=NUM_LEDS_PER_DISK-1; idx > 0; idx--) {
      led_display[idx] = led_display[idx-1];
    }
    led_display[0] = led_tmp1;
  }
} // end RBG_diskRotate()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_ringRotateOrDrain(direction, pColor, whichRing) - 
//
// direction - +/- 1 = rotate through, +/- 2 = down drain. With these rings, + is counter-clockwise and - is clockwise
// pColor    - pointer to color to use as fill (typically &CRGB::Black)
// whichRing - which ring to rotate, 0 through (NUM_RINGS_PER_DISK-1) {2 for RBG}
// 
void RBG_ringRotateOrDrain(int8_t direction, CRGB* pColor, uint8_t whichRing) {
  // do rotate/drain
  int idx;
  if (direction > 0) { // counterclockwise
    if (1 == direction) { led_tmp1 = led_display[start_per_ring[whichRing]]; } else { led_tmp1 = *pColor; }
    for (idx=start_per_ring[whichRing]+1; idx < start_per_ring[whichRing]+leds_per_ring[whichRing]; idx++) {
      led_display[idx-1] = led_display[idx];
    }
    led_display[led_display[start_per_ring[whichRing]+leds_per_ring[whichRing]-1]] = led_tmp1;
  } else  { // clockwise
    if (-1 == direction) { led_tmp1 = led_display[start_per_ring[whichRing]+leds_per_ring[whichRing]-1]; } else { led_tmp1 = *pColor; }
    for (idx=start_per_ring[whichRing]+leds_per_ring[whichRing]-1; idx > start_per_ring[whichRing]; idx--) {
      led_display[idx] = led_display[idx-1];
    }
    led_display[0] = led_tmp1;
  }
} // end RBG_ringRotateOrDrain()

void bpm_rings() { // my mod of pattern from Demo Reel 100
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62+10;
  CRGBPalette16 palette = PartyColors_p;
  int16_t beat = beatsin8( BeatsPerMinute, 0, 255);
  for ( uint8_t ring = 0; ring < NUM_RINGS_PER_DISK; ring++ ) {
    beat = -beat+255; // reverse lighting directions
    for ( uint8_t i = start_per_ring[ring]; i < (start_per_ring[ring]+leds_per_ring[ring]); i++ ) {
      led_display[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    } // end for LEDs
  } // end for rings
} // end bpm()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// a few of Mark Kriegsman's classic DemoReel100.ino patterns
//
 
void rainbow() { // pattern from Demo Reel 100
  // FastLED's built-in rainbow generator
  fill_rainbow( led_display, NUM_LEDS_PER_DISK, gHue, 7);
}

void rainbowWithGlitter() { // pattern from Demo Reel 100
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(100);
} // end rainbowWithGlitter

void addGlitter( fract8 chanceOfGlitter) { // helper routine from Demo Reel 100
  if( random8() < chanceOfGlitter) {
    led_display[ random16(NUM_LEDS_PER_DISK) ] += CRGB::White;
  }
} // end 

void confetti() { // pattern from Demo Reel 100
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( led_display, NUM_LEDS_PER_DISK, 10);
  int pos = random16(NUM_LEDS_PER_DISK);
  led_display[pos] += CHSV( gHue + random8(64), 200, 255);
} // end 

void bpm() { // pattern from Demo Reel 100
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62+10;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS_PER_DISK; i++) { //9948
    led_display[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
} // end bpm()

void juggle() { // pattern from Demo Reel 100
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( led_display, NUM_LEDS_PER_DISK, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    led_display[beatsin16(i+7,0,NUM_LEDS_PER_DISK-1)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
} // end juggle()


// ******************************** STATE TABLE UTILITIES ********************************

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_processStateTable(...) - called from main loop to do state table processing
//     Use our state table and state and inputs to calculate next state
//     Determine if we need to change LED pattern and/or sound
//     If needed, release the rubber band and set timer to stop the solenoid current later
//
// if prevRow != myState.tableRow 
//   RBG_startRow
//   prevRow = myState.tableRow
// else
//   foundInputRow = RBG_waitForInput
//   if foundInputRow != mNone, myState Row = foundInputRow
//   else if sound ended and continuous sound, RESTART SOUND
//
uint16_t RBG_processStateTable(uint16_t tmpVinputRBG) {
  static uint8_t debugThisManyCalls = DEBUG_STATE_MACHINE*10;
  static uint16_t prevRow = mNONE;
  RBGStateTable_t * thisRowPtr = &myStateTable[myState.tableRow];

  // see if need to start a new row
  if (prevRow != myState.tableRow) { // start a new row
    debugThisManyCalls = DEBUG_STATE_MACHINE*10; // will be interesting for a bit
    RBG_startRow(thisRowPtr); // just do what the row says
    if (debugThisManyCalls > 0) {
      printAllMyState(); Serial.print(F("DEBUG RBG_processStateTable() - tmpVinputRBG 0x")); Serial.print(tmpVinputRBG, HEX); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      debugThisManyCalls -= 1;
    }
    prevRow = myState.tableRow;    
  } else {
    // check if inputs are satisfied - trigger, open, lock/load, sound end
    uint16_t foundInputRow = RBG_waitForInput(tmpVinputRBG);
    if (foundInputRow != mNONE) {
      if (debugThisManyCalls > 0) {
        Serial.println(F("DEBUG RBG_processStateTable() - after RBG_waitForInput() call"));
        printAllMyState();Serial.print(F("DEBUG RBG_processStateTable() - tmpVinputRBG 0x")); Serial.print(tmpVinputRBG, HEX); Serial.print(F(" from row ")); Serial.print(myState.tableRow); Serial.print(F(" foundInputRow ")); Serial.print(foundInputRow);  Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
        debugThisManyCalls -= 1;
      }
      myState.tableRow = foundInputRow; // this should be the only place that this assignment is done
    } else if ((mNONE != thisRowPtr->SPECIAL) && (0 != (thisRowPtr->SPECIAL & (mSPCL_EFCT_CONTINUOUS | mSPCL_EFCT_CONFIGURE))) && (0 == (tmpVinputRBG&mVINP_SOUNDACTV))) {
      // restart a continuous sound
      if (debugThisManyCalls > 0) {
        printAllMyState(); Serial.print(F("DEBUG RBG_processStateTable() - tmpVinputRBG 0x")); Serial.print(tmpVinputRBG, HEX); Serial.print(F(" restart sound ")); Serial.print(thisRowPtr->efctSound); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
        debugThisManyCalls -= 1;
      }
      RBG_startEffectSound(thisRowPtr->efctSound, thisRowPtr->SPECIAL);
    } // end check restart continuous sound
  } // end check for inputs satisfied
} // end RBG_processStateTable()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_startRow(thisRowPtr) - start processing a row in myStateTable
//    basically we just start the effects and do a return
//
void RBG_startRow(RBGStateTable_t* thisRowPtr) {

  RBG_startEffectSound(thisRowPtr->efctSound, thisRowPtr->SPECIAL);
  RBG_startEffectLED(thisRowPtr->efctLED, thisRowPtr->SPECIAL);

} // end RBG_startRow()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_waitForInput(tmpVinputRBG) - wait until desired input happens
//   returns mNONE if did not happen, idx to row that matched if it did
// RBG_waitForInput   
//   for each row in block 
//     if special handler, process and goto WithoutInput
//     else if sound end and mSPCL_EFCT_ONETIME, goto WithoutInput
//     else if foundinput matches, goto OnInput
//
uint16_t RBG_waitForInput(uint16_t tmpVinputRBG) {
  static uint8_t debugThisManyCalls = DEBUG_STATE_MACHINE*200;
  uint16_t thisReturn = mNONE; // assume no input found
  RBGStateTable_t * thisRowPtr = &myStateTable[myState.tableRow];


  // we need to check until we hit the mBLOCKEND
  for (uint16_t idx = myState.tableRow; (idx < NUMOF(myStateTable)) && (mNONE == thisReturn); idx++) {
    // see if we match input condition for this row
    if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.print(idx); Serial.print(F(" thisRowPtr->inputRBG 0x")); Serial.print(thisRowPtr->inputRBG, HEX); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
    if (debugThisManyCalls > 0) { Serial.print(F("    thisRowPtr->SPECIAL&mSPCL_HANDLER 0x")); Serial.println(thisRowPtr->SPECIAL&mSPCL_HANDLER, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    thisRowPtr->SPECIAL&mSPCL_EFCT_ONETIME 0x")); Serial.print(thisRowPtr->SPECIAL&mSPCL_EFCT_ONETIME, HEX); Serial.print(F(" tmpVinputRBG&mVINP_SOUNDACTV 0x")); Serial.println(tmpVinputRBG&mVINP_SOUNDACTV, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    thisRowPtr->inputRBG&mINP_TRIG 0x")); Serial.print(thisRowPtr->inputRBG&mINP_TRIG, HEX); Serial.print(F(" tmpVinputRBG&mVINP_TRIG 0x")); Serial.println(tmpVinputRBG&mVINP_TRIG, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    thisRowPtr->inputRBG&mINP_OPEN 0x")); Serial.print(thisRowPtr->inputRBG&mINP_OPEN, HEX); Serial.print(F(" tmpVinputRBG&mVINP_OPEN 0x")); Serial.println(tmpVinputRBG&mVINP_OPEN, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    thisRowPtr->inputRBG&mINP_LOCK 0x")); Serial.print(thisRowPtr->inputRBG&mINP_LOCK, HEX); Serial.print(F(" tmpVinputRBG&mVINP_LOCK 0x")); Serial.println(tmpVinputRBG&mVINP_LOCK, HEX); }

    if ((mNONE != thisRowPtr->SPECIAL) && (0 != (thisRowPtr->SPECIAL & mSPCL_HANDLER))) { // special handler
      // no sounds no LEDs for mSPCL_HANDLER; it gets called exactly once
      RBG_specialProcessing(tmpVinputRBG, thisRowPtr->SPECIAL, thisRowPtr->storeVal, thisRowPtr->storeAddr);
      thisReturn = thisRowPtr->gotoWithoutInput; // this one uses WithoutInput not OnInput
      Serial.print(F(" RBG_waitForInput mSPCL_HANDLER thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
    } else if ((0 != (thisRowPtr->SPECIAL&mSPCL_EFCT_ONETIME)) && (0 == (tmpVinputRBG&mVINP_SOUNDACTV))) {
      thisReturn = thisRowPtr->gotoWithoutInput; // this one uses WithoutInput not OnInput
      Serial.print(F(" RBG_waitForInput mSPCL_EFCT_ONETIME thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
    } else if ((mNONE != (thisRowPtr->inputRBG)) && (0 != (thisRowPtr->inputRBG&mINP_TRIG)) && (0 != (tmpVinputRBG&mVINP_TRIG))) {
      // several cases for trigger
      if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.print(idx); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
      if (0 != (thisRowPtr->inputRBG&mINP_BANY)) {
        if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.print(idx); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
        thisReturn = thisRowPtr->gotoOnInput;
        Serial.print(F(" RBG_waitForInput mINP_TRIG mINP_BANY thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
        break;
      } else if ((mNONE != (thisRowPtr->inputRBG)) && (0 != (thisRowPtr->inputRBG&mINP_BNONE)) && (0 == (tmpVinputRBG & (mVINP_B01|mVINP_B02|mVINP_B04)))) {
        if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.print(idx); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
        thisReturn = thisRowPtr->gotoOnInput;
        Serial.print(F(" RBG_waitForInput mINP_TRIG mINP_BANY thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
        break;
      }
    } else if ((mNONE != (thisRowPtr->inputRBG)) && (0 != (thisRowPtr->inputRBG&mINP_OPEN)) && (0 != (tmpVinputRBG&mVINP_OPEN))) {
      thisReturn = thisRowPtr->gotoOnInput;
      Serial.print(F(" RBG_waitForInput mINP_OPEN thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
    } else if ((mNONE != (thisRowPtr->inputRBG)) && (0 != (thisRowPtr->inputRBG&mINP_LOCK)) && (0 != (tmpVinputRBG&mVINP_LOCK))) {
      thisReturn = thisRowPtr->gotoOnInput; // found an input we were waiting for
      Serial.print(F(" RBG_waitForInput mINP_LOCK thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
    }

    if (0 != (thisRowPtr->blkFlags&mBLOCKEND)) {
      // this is a normal way to end - found the mBLOCKEND but did not find input
      break;
    } else {
      // continue until we do reach mBLOCKEND
      thisRowPtr += 1;
    }
  } // end while searching for mBLOCKEND

  if (debugThisManyCalls >= 1) debugThisManyCalls -= 1;

  return(thisReturn);
} // end RBG_waitForInput()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcessing(tmpVinputRBG, tmpSPECIAL, tmpStoreVal, tmpStoreAddr)
//   do the SPECIAL processing - mostly the solenoid stuff
//
uint16_t RBG_specialProcessing(uint16_t tmpVinputRBG, uint16_t tmpSPECIAL, uint16_t tmpStoreVal, uint16_t tmpStoreAddr) {
  uint16_t myVinputRBG = tmpVinputRBG;
  uint16_t mySpec = tmpSPECIAL & (mSPCL_HANDLER-1);

  switch (mySpec) {
    case mSPCL_HANDLER_SHOOT:
      RBG_specialProcShoot();
      break;
    case mSPCL_HANDLER_SOLENOID:
      RBG_specialProcSolenoid();
      break;
    case mSPCL_HANDLER_CFGSTORE:
      RBG_specialProcConfigStore(tmpStoreVal, tmpStoreAddr);
      break;
    case mSPCL_HANDLER_CFGNEXT:
      RBG_specialProcConfigNext();
      break;
    case mSPCL_HANDLER_CFG2EEPROM:
      RBG_specialProcConfig2Eeprom();
      break;
    default:
      Serial.print(F(" RBG_specialProcessing ERROR ln ")); Serial.print((uint16_t) __LINE__);  Serial.print(F(" mySpec ")); Serial.print(mySpec);  Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
  } // end switch on type of special
  return(myVinputRBG);
} // end RBG_specialProcessing(uint16_t tmpVinputRBG)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcConfigStore(tmpStoreVal, tmpStoreAddr) - prepare for configuration list
//
// tmpStoreVal  - 8 MSbits: max num, 8 LSbits: mEFCT_ category
// tmpStoreAddr - code: mADDR_CFGSND, mADDR_CFGLED, or mADDR_CFGOTHER 
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//
void RBG_specialProcConfigStore(uint16_t tmpStoreVal, uint16_t tmpStoreAddr) {
  // initialize numbers for mSPCL_EFCT_CONFIGURE
  myState.cfg_curnum = 1; // current number for configuration list of choices
  myState.cfg_maxnum = (tmpStoreVal >> mSHIFT_EFCT_CFGMAXVAL) & 0xFF; // maximum number for configuration list of choices
  myState.cfg_category = tmpStoreVal & 0xFF; // example: mEFCT_LOCK_LOAD
  myState.cfg_type = tmpStoreAddr; // code: mADDR_CFGSND, mADDR_CFGLED, or mADDR_CFGOTHER
} // end RBG_specialProcConfigStore()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcConfigNext() - prepare for next item in configuration list
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//
void RBG_specialProcConfigNext() {
  // go to next choice in list of choices. Loop if needed.
  if (myState.cfg_curnum >= myState.cfg_maxnum) {
    myState.cfg_curnum = 1;
  } else {
    myState.cfg_curnum += 1;
  }
} // end RBG_specialProcConfigNext()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcConfig2Eeprom() - store choice in proper place in EEPROM
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//
void RBG_specialProcConfig2Eeprom() {
  // store choice in EEPROM
  switch (myState.cfg_type) {
    case mADDR_CFGSND:
      eeprom_store_with_chksum(eeSoundSave+EEPOFFSET(myState.cfg_category), myState.cfg_curnum);
      break;
    case mADDR_CFGLED:
      eeprom_store_with_chksum(eeLEDSave+EEPOFFSET(myState.cfg_category), myState.cfg_curnum);
      break;
    case mADDR_CFGOTHER:
      break;
    default:
      Serial.print(F(" RBG_specialProcConfig2Eeprom ERROR bad cfg_type ")); Serial.println((uint16_t) myState.cfg_type);
  } // end switch ()
  myState.cfg_curnum = myState.cfg_maxnum = myState.cfg_category = myState.cfg_type = mNONE;
} // end RBG_specialProcConfigStore()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcShoot() - do the solenoid for shooting
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//
void RBG_specialProcShoot() {
  uint16_t nextRow = myStateTable[myState.tableRow].gotoWithoutInput;
  digitalWrite(DPIN_SOLENOID, HIGH);
  myState.timerForceSolenoidLow = millis() + DLYSOLENOID;
} // end RBG_specialProcShoot()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcSolenoid() - release the solenoid after shooting
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//
void RBG_specialProcSolenoid() {
  uint16_t nextRow = myStateTable[myState.tableRow].gotoWithoutInput;
  digitalWrite(DPIN_SOLENOID, LOW);
  myState.timerForceSolenoidLow = 0;
  if (mNONE == nextRow) { nextRow = mROW_POWERON; Serial.print(F(" RBG_specialProcSolenoid ERROR ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" gotoWithoutInput is mNONE; going to mROW_POWERON")); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
} // end RBG_specialProcSolenoid()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_startEffectLED(tmpEfctLED, tmpSPECIAL) - starts a new LED pattern
//
// tmpEfctLED - 8 LSBits is pattern number - EEPROM configurable or uniq
//              8 MSBits reservered for parameter
// If the row says mSPCL_EFCT_CONFIGURE and efctSound is mNONE and mADDR_CFGLED then we use the configuration variables
//
void RBG_startEffectLED(uint16_t tmpEfctLED, uint16_t tmpSPECIAL) {
  uint16_t myEfctLED = tmpEfctLED & 0x00FF; // just the effect number; allows bits later

  if ((0 != (mSPCL_EFCT_CONFIGURE & tmpSPECIAL)) && (mADDR_CFGLED == myState.cfg_type) && (mNONE == tmpEfctLED)) { // handle configuration effects
    tmpEfctLED = myState.cfg_curnum + myState.cfg_category;
  } // end if special configuration effects

  if (mNONE != myEfctLED) {
    #if DEBUG_STATE_MACHINE
    Serial.print(F(" RBG_startEffectLED ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" EFCT num ")); Serial.print(tmpEfctLED); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
    #endif // DEBUG_STATE_MACHINE
    doPattern(tmpEfctLED); // doPattern figures out EEPROM configuration and if starting a new pattern and initializes
  }
} // end RBG_startEffectLED()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_startEffectSound(tmpEfctSound, tmpSPECIAL) - start tmpEfctSound if it is valid
//
// tmpEfctSound is two fields: 0x00vv00nn where nn is sound and vv is volume
//       FIXME - volume not implemented yet
// If the row says mSPCL_EFCT_CONFIGURE and efctSound is mNONE and mADDR_CFGSND then we use the configuration variables
//
// Had lots of trouble with reliable operation using playMp3Folder. Came to conclusion
//    that it is best to use the most primitive of YX5200 commands.
// Also saw strong correlation of using YX5200 ACK and having even more unreliable
//    operation, so turned that off in DFinit.
// There is code checking DPIN_AUDIO_BUSY that can probably be removed now that the
//    debugging for above is finished.
// There is code checking myDFPlayer.available() that can maybe also be removed now
//    that the dubugging for above is finished. Now that I am using myDFPlayer.play(),
//    it only seems to trigger when I interrupt a playing sound by starting another.
//    It is sort of interesting but not needed.
//
void  RBG_startEffectSound(uint16_t tmpEfctSound, uint16_t tmpSPECIAL) {
  uint16_t idx;
  bool prevHI;
  uint16_t mySound = tmpEfctSound & mMASK_EFCT_SND_NUM;
  // uint16_t myVolume = (tmpEfctSound >> mSHIFT_EFCT_SND_VOL) & mMASK_EFCT_SND_VOL; // USE BELOW to convince MS VS 2019 we don't lose data
  uint16_t myVolume = ((tmpEfctSound & (mMASK_EFCT_SND_VOL << mSHIFT_EFCT_SND_VOL)) >> mSHIFT_EFCT_SND_VOL) & mMASK_EFCT_SND_VOL;

  if ((0 != (mSPCL_EFCT_CONFIGURE & tmpSPECIAL)) && (mADDR_CFGSND == myState.cfg_type) && (mNONE == tmpEfctSound)) { // handle configuration effects
    tmpEfctSound = myState.cfg_curnum + myState.cfg_category;
    myVolume = 25;
  } // end if special configuration effects

  // wait up to one second for two "LOW" indications in a row
  prevHI = false;
  for (idx = 0; idx < 3; idx++) {
    delay(10);
    if (LOW != digitalRead(DPIN_AUDIO_BUSY)) {
      if (prevHI) break;
      prevHI = true;
    } else {
      prevHI = false;
    }
  }
  if (idx > 3) {
    Serial.print(F(" RBG_startEffectSound ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" wait msec ")); Serial.print(10*idx); printOneInput(DPIN_AUDIO_BUSY, " AUDIO_BUSY "); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
  } 

  // myVolume is [0-31]. 0 means default; else subtract one to make [0-30]
  if (0 == myVolume) {
    myVolume = mDEFAULT_EFCT_SND_VOL;
  } else {
    myVolume -= 1;
  }
  if (mNONE != mySound) {
    // configurable sounds are zero mod 10; we get config from EEPROM
    if (EFCT_IS_EEP(mySound)) {
      // configurable sound using EEPROM
      mySound += EEPROM.read(EEPOFFSET(mySound)+eeSoundSave);
    }
    #if DEBUG_STATE_MACHINE
    Serial.print(F(" RBG_startEffectSound ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" EFCT num ")); Serial.print(tmpEfctSound); Serial.print(F(" final num ")); Serial.print(mySound); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
    #endif // DEBUG_STATE_MACHINE
    /*** PROBABLY ADD THIS IN LATER FIXME
    if (false) { // (myState.currVolume != myVolume) { FIXME - add the volume after verifying it doesn't mess up communications
      myDFPlayer.volume(myVolume);  // Set volume value. From 0 to 30
      myState.currVolume = myVolume;
      if (myDFPlayer.available()) {
        Serial.print(F(" RBG_startEffectSound ln ")); Serial.print((uint16_t) __LINE__); Serial.println(F(" myDFPlayer problem after volume"));
        DFprintDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
      }
    } // end if volume different this time
    ***/
    myDFPlayer.play(mySound); //play specific mp3 in SD: root directory ###.mp3; number played is physical copy order; first one copied is 1
    // myDFPlayer.playMp3Folder(mySound); //play specific mp3 in SD:/MP3/####.mp3; File Name(0~9999) NOTE: this did not work reliably
    myState.timerForceSoundActv = millis() + mDELAY_SOUNDACTV; // handle YX5200 problem with interrupting play
  } // end if should start a sound

} // end RBG_startEffectSound

// ******************************** BUTTON AND TIMING UTILITIES ********************************

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// getButtonInput() - returns mVINP_ mask for buttons to process
// 
// All the buttons are 0 when pressed
// The lock/load input is 0 when connected and 1 when not lock/load
// The sound complete is 0 when sound is complete
//
// NOTE: DPIN_LOCK_LOAD handled in code
// NOTE: this is where we handle YX5200 active pin instability when interrupting previous play command
//
uint16_t getButtonInput() {
  static uint8_t debugThisManyCalls = DEBUG_INPUTS*10;
  uint16_t idx;
  uint16_t thePin;
  uint16_t theVal;
  uint16_t returnInpMask = 0;

  #if DEBUG_INPUTS
  Serial.print("getButtonInput() called: "); printAllMyInputs();
  #endif // DEBUG_INPUTS
  // do lock/load separately in code
  theVal = digitalRead(DPIN_LOCK_LOAD);
  if (LOW == theVal) { // we are locked and loaded; sensitive to trigger and other events
    if (debugThisManyCalls > 0) { Serial.print(F(" getButtonInput ln ")); Serial.println((uint16_t) __LINE__); }
    returnInpMask = mVINP_LOCK;
  } else { // we are not locked and loaded; abort everything else
    if (debugThisManyCalls > 0) { Serial.print(F(" getButtonInput ln ")); Serial.println((uint16_t) __LINE__); }
    returnInpMask = mVINP_OPEN;
  }

  // set/clear the input bits for the standard inputs
  for (idx = 0; idx < NUMOF(myPinsToVals); idx++) {
    if (LOW == digitalRead(myPinsToVals[idx].pin)) {
      returnInpMask |= ((uint16_t) myPinsToVals[idx].val); // less overkill but still solves if .val is not uintx_t
    } else {
      returnInpMask &= ~((uint16_t) myPinsToVals[idx].val); // overkill but can solve lots of issues
    }
  } // end for entries in myPinsToVals[]

  if (myState.timerNow < myState.timerForceSoundActv) {
    // takes a while for YX5200 active pin to go and stay low when interrupted previous play command
    returnInpMask |= mVINP_SOUNDACTV;
  }

  if (debugThisManyCalls > 0) { Serial.print(F(" checkButtons found inputs: 0x")); Serial.println((uint16_t) returnInpMask, HEX); }
  if (debugThisManyCalls > 0) { debugThisManyCalls -= 1; }

  return(returnInpMask);
} // end getButtonInput()

// ******************************** INITIALIZATION UTILITIES ********************************

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFsetup()
void DFsetup() {
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial, false, true)) {  // Use softwareSerial to communicate with mp3 player
    Serial.println(F("Unable to begin DFPlayer:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(1);
    }
  }
  myDFPlayer.EQ(DFPLAYER_EQ_BASS); // our speaker is quite small
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // device is SD card
  myDFPlayer.volume(mDEFAULT_EFCT_SND_VOL);  // Set volume value. From 0 to 30 - FIXME 25 is good
  myState.currVolume = mDEFAULT_EFCT_SND_VOL;
  Serial.println(F("DFPlayer Mini online."));
} // end DFsetup()

// ******************************** DEBUG UTILITIES ********************************

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkDataGuard()
void checkDataGuard() {
  static int8_t showOneTime = 1;
  if ((showOneTime >= 1) && ((0x55555555 != data_guard_before) || (0x55555555 != data_guard_after))) {
    Serial.print(F("checkDataGuard should be 0x55555555; before=0x"));
    Serial.print(data_guard_before, HEX);
    Serial.print(F(" after=0x"));
    Serial.println(data_guard_after, HEX);
    delay(2000); // for debugging & show
    showOneTime--;
  }
} // end checkDataGuard()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#if DFPRINTDETAIL
void DFprintDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      } // end switch (value)
      break;
    default:
      break;
  }  // end switch (type)
} // end DFprintDetail()
#endif // DFPRINTDETAIL

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_check_init() - check if EEPROM has our values; if not initialize it
//    we use a very crude checksum approach
void eeprom_check_init() {
  // start reading from the first byte (address 0) of the EEPROM
  int address;
  uint8_t invChksumValue;
  uint8_t byteValue;
  uint8_t byte2Value;

  // read RBG non-checksum bytes from EEPROM and calculate checksum; compare with stored checksum
  invChksumValue = eeprom_calc_inverted_checksum();
  byteValue = EEPROM.read(eeInvertedChksum);
  // byteValue = invChksumValue+1; // FIXME force a checksum error
  // Serial.print(F("INIT EEP: stored inverted chksum 0x"); Serial.print(eeInvertedChksum,HEX); Serial.print(F(" value 0x")); Serial.print(byteValue,HEX); Serial.print(F(", calculated inverted chksum 0x")); Serial.println(((uint8_t) ~chksumValue),HEX);
  if (byteValue != invChksumValue) {
    // checksum does not match; zero out our EEPROM area
    Serial.print(F("INIT: calc EEPROM inverted chksum 0x")); Serial.print(invChksumValue,HEX); Serial.print(F(" does not match 0x")); Serial.print(byteValue,HEX); Serial.println(F("; INITIALIZING"));
    byteValue = 1;
    for (address = 0; address < eeLastNonChksum; address++) { // one less than entire data area
      byte2Value = EEPROM.read(address);
      if (byte2Value != byteValue) { // avoid EEPROM writes when possible
        EEPROM.write(address, byteValue);
      }
    } // end zero out our EEPROM area except last value
    eeprom_store_with_chksum(eeLastNonChksum, byteValue); // store last value and checksum
  } // end if checksum does not match
} // end eeprom_check_init()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_store_with_chksum() - store byteValue at EEPROM address and update checksum
//    we use a very crude checksum approach
void eeprom_store_with_chksum(int address, uint8_t byteValue) {
  uint8_t byte2Value;
  uint8_t invChksumValue;

  byte2Value = EEPROM.read(address);
  if (byte2Value != byteValue) { // avoid EEPROM writes when possible
    EEPROM.write(address, byteValue);
  }
  invChksumValue = eeprom_calc_inverted_checksum();
  byte2Value = EEPROM.read(eeInvertedChksum);
  if (byte2Value != invChksumValue) { // avoid EEPROM writes when possible
    EEPROM.write(eeInvertedChksum, invChksumValue);
  }
} // end eeprom_store_with_chksum()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_calc_inverted_checksum() - calculate the inverted checksum
//    we use a very crude checksum approach
uint8_t eeprom_calc_inverted_checksum() {
  int address;
  uint8_t chksumValue; // non-inverted checksum
  uint8_t byteValue;

  // read RBG non-checksum bytes from EEPROM and calculate checksum
  for (address = chksumValue = 0; address <= eeLastNonChksum; address++) {
    byteValue = EEPROM.read(address);
    chksumValue += byteValue;
    // Serial.print(F("INIT EEP: address 0x")); Serial.print(address,HEX); Serial.print(F(" value 0x")); Serial.print(byteValue,HEX); Serial.print(F(" calc chksum 0x")); Serial.println(chksumValue,HEX);
  } // end caclulate checksum
  return((uint8_t) (~chksumValue));
} // end eeprom_calc_inverted_checksum()


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// printAllMyState() - print the important states
//
void printAllMyState() {
  Serial.println(F("DEBUG - myState:"));
  Serial.print(F("  - tableRow: "));
  Serial.println((uint16_t) myState.tableRow);
  Serial.print(F("  - VinputRBG: 0x"));
  Serial.println((uint16_t) myState.VinputRBG, HEX);
  printExplainBits(myState.VinputRBG, decodeBits_VinputRBG, NUMOF(decodeBits_VinputRBG));
} // end printAllMyState()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// printExplainBits(...) - print string explaining bits
void printExplainBits(uint16_t myBits, decodeBits_t theDecodeTable[], uint16_t numof_Table) {
#ifndef DONOTEXPLAINBITS // this coding takes too much space - needs re-write
  char printAsText[260]; // more than enough for now
  uint16_t idx;

  strcpy(printAsText, "    ");
  for (idx = 0; idx < numof_Table; idx++) {
    if (0 != (myBits & theDecodeTable[idx].theBit)) {
      strcat(printAsText, theDecodeTable[idx].theText);
    }
  } // end for
  if (strlen(printAsText) > 5) {
    Serial.println(printAsText);
  }
#endif // DONOTEXPLAINBITS // this coding takes too much space - needs re-write
} // end printExplainBits()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// printAllMyInputs() - interpret the input bits
void printAllMyInputs() {
  Serial.print(F("printAllMyInputs:"));
  printOneInput(DPIN_BTN_TRIGGER, " TRIGGER ");
  printOneInput(DPIN_BTN_YELLOW, " YELLOW ");
  printOneInput(DPIN_BTN_GREEN, " GREEN ");
  printOneInput(DPIN_BTN_BLACK, " BLACK ");
  printOneInput(DPIN_LOCK_LOAD, " LOAD ");
  printOneInput(DPIN_AUDIO_BUSY, " AUDIO_BUSY ");
  Serial.println(" ");
} // end printAllMyInputs()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// printOneInput(...) - interpret one input bit
//   dtext will line up the LOW and HIGH
void printOneInput(uint8_t dpin, const char * printAsText) {
  Serial.print(printAsText);
  if (LOW == digitalRead(dpin)) {
    Serial.print("LOW");
  } else {
    Serial.print("HIGH");
  }
} // end printOneInput()
