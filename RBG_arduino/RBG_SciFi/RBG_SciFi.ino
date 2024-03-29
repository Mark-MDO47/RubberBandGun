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
// Here are the files I used, modified, and combined (or plan to use) for the sounds
// | Tag        | File Name                                      | URL                             | Who |
// | ---        | ---                                            | ---                             | --- |
// | N/A | GW170817-template.wav | https://www.gw-openscience.org/audiogwtc1/ | LIGO detectors |
// | N/A | SKR-03-324.wav | http://www-pw.physics.uiowa.edu/space-audio/cassini/SKR1/ | NASA Cassini mission Radio and Plasma Wave Science |
// | zero/1.0/ | 145209__lensflare8642__shotgun-sounds.mp3 | https://freesound.org/s/145209/ | lensflare8642 |
// | zero/1.0/ | 162814__timgormly__spaceship-4.aiff | https://freesound.org/s/162814/ | timgormly |
// | by-nc/3.0/ | 165483__timbre__glitch-voice-ep-mp3.mp3 | https://freesound.org/s/165483/ | timbre |
// | by/3.0/ | 169292__lazr2012__haywirefusionator.ogg | https://freesound.org/s/169292/ | lazr2012 |
// | zero/1.0/ | 170136__lazr2012__machinery-bo.flac | https://freesound.org/s/170136/ | lazr2012 |
// | by-nc/3.0/ | 179281__timbre__boingy-sweep.flac | https://freesound.org/s/179281/ | Timbre |
// | by/3.0/ | 216096__richerlandtv__u-f-o.mp3 | https://freesound.org/s/216096/ | RICHERlandTV |
// | by/3.0/ | 221875__hero-of-the-winds__spring-boing.wav | https://freesound.org/s/221875/ | hero-of-the-winds |
// | by/3.0/ | 240297__jalastram__abstract-guitar-sfx-003.wav | https://freesound.org/s/240297/ | jalastram |
// | by/3.0/ | 272068__ichbinjager__shotgun-action.wav | https://freesound.org/s/272068/ | IchBinJager |
// | by/3.0/ | 275537__wjoojoo__contact-mic-on-satellite-dish04.wav | https://freesound.org/s/275537/ | wjoojoo |
// | zero/1.0/ | 352852__josepharaoh99__game-style-laser-beam.wav | https://freesound.org/s/352852/ | josepharaoh99 |
// | zero/1.0/ | 380886__morganpurkis__doom-shotgun-2017.wav | https://freesound.org/s/380886/ | morganpurkis |
// | by/3.0/ | 383205__spiceprogram__loading-sound.wav | https://freesound.org/s/383205/ | SpiceProgram |
// | zero/1.0/ | 383760__deleted-user-7146007__laboratory-mad-scientist-science-fiction-sci-fi.wav | https://freesound.org/s/383760/ | deleted-user-7146007 |
// | zero/1.0/ | 397254__screamstudio__loading.wav | https://freesound.org/s/397254/ | ScreamStudio |
// | zero/1.0/ | 404068__swordofkings128__backyard-gate-open.wav | https://freesound.org/s/404068/ | swordofkings128 |
// | zero/1.0/ | 407052__sojan__power-charge.flac | https://freesound.org/s/193610/ | crashoverride61088 |
// | by/3.0/ | 417131__cuddlenucks__science-fiction-noise-3.wav | https://freesound.org/s/417131/ | cuddlenucks |
// | by/3.0/ | 417363__xcreenplay__boing-massive-kick.wav | https://freesound.org/s/417363/ | xcreenplay |
// | by/3.0/ | 431117__inspectorj__door-front-opening-a.wav | https://freesound.org/s/431117/ | inspectorj |
// | zero/1.0/ | 500418__dj-somar__intro-reverso-craver-microbrute.wav | https://freesound.org/s/500418/ | DJ_SoMaR |
// | by/3.0/ | 7967__cfork__boing-raw.aiff | https://freesound.org/s/7967/ | cfork |
// | by/3.0/ | 88635__uair01__bicycle-picture-in-spectrum.wav | https://freesound.org/s/88635/ | uair01 |
// | by-nc/3.0/ | 91296__timbre__bwaang-2-reverb.mp3 | https://freesound.org/s/91296/ | timbre |
// | by/3.0/ | 96964__gabisaraceni__porta-abrindo-5.wav | https://freesound.org/s/96964/ | gabisaraceni |
// | zero/1.0/ | 388276__csnmedia__la-cucaracha-car-horn.wav | https://freesound.org/s/388276/ | csnmedia |
// | zero/1.0/ | 118807__lmbubec__17-1985-ford-mustang-horn.wav | https://freesound.org/s/118807/ | lmbubec |
//
// | Tag        | Name                                               | URL |
// | ---        | ---                                                | --- |
// | zero/1.0/  | Creative Commons 0 License                         | https://creativecommons.org/publicdomain/zero/1.0/ |
// | by/3.0/    | Creative Commons Attribution License               | https://creativecommons.org/licenses/by/3.0/ |
// | by-nc/3.0/ | Creative Commons Attribution Noncommercial License | https://creativecommons.org/licenses/by-nc/3.0/ |
//
// The robotic voice sounds were generated using the eSpeak text to speech program found on eSpeak.SourceForge.net.
//
// Note: I am not making any claims that this software is well written or a good example for anyone.
//       I am just having fun with it.
//       Mark


#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port
#include <EEPROM.h>                          // to store configuration info

#define USE_PROGMEM true                     // set true to keep big const items in FLASH (PROGMEM keyword)

#include "FastLED.h"                         // to manipulate WS2812b (NeoPixel) 5050 RGB LED Rings
#include "DFRobotDFPlayerMini.h"             // to communicate with the YX5200 audio player

#include "RBG_SciFi_StatesAndInputs.h"       // state tables and input definitions
#include "RBG_SciFi_LEDs.h"                  // LED structural and pattern definitions

#define SERIALDEBUG 1                        // serial debugging
#define REAL_BUTTONS 1                       // use actual buttons

#define DEBUG_SHOW_MSEC 1                    // use globalLoopCount for millis() display not loopcount
#define DONOTEXPLAINBITS 1                   // don't explain the bits - existing routine uses too much RAM

#define DEBUGALL_GLOBAL 0                    // sets many of the following
#define DEBUG_STATE_MACHINE (0 | DEBUGALL_GLOBAL) // 1 to show state machine internals for transitions
#define DEBUG_INPUTS (1 | DEBUGALL_GLOBAL)        // 1 to show all inputs MDO_DEBUG_TURNOFFLATER
#define DEBUG_CONFIG (0 | DEBUGALL_GLOBAL)        // 1 to show all CONFIGURATION special activity
#define DEBUG_TRIGSTATE (1 | DEBUGALL_GLOBAL)     // 1 to show all new trigger state activity

static uint32_t globalLoopCount = 0;  // based on DEBUG_SHOW_MSEC: this is either the milliseconds since startup or a count of times through loop()

SoftwareSerial mySoftwareSerial(DPIN_SWSRL_RX, DPIN_SWSRL_TX); // to talk to YX5200 audio player
DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player
void DFsetup();                                                // how to initialize myDFPlayer

// sure glad we are done with debugging the YX5200 and its code!!!
//
#define DFPRINTDETAIL (1&SERIALDEBUG)     // if need detailed status from myDFPlayer
// #define DFPRINTDETAIL 0                      // will not print detailed status from myDFPlayer
#if DFPRINTDETAIL // routine to do detailed debugging
  void DFprintDetail(uint8_t type, int value); // definition of call
#else  // no DFPRINTDETAIL
  #define DFprintDetail(type, value) // nothing at all
#endif // #if DFPRINTDETAIL


static uint8_t gHue = 0; // rotating "base color" used by Demo Reel 100
CRGBPalette16 gPal; // palette for Fire2012WithPalette()
static uint16_t gSeed = ((uint16_t) 42); // my favorite is 47 but the whole world loves 42 and HHG2TG
// we are not using the fire pattern
#if FASTLED_FIRE_PATTERN // only used for Fire pattern
CRGB dark_color_palette[1]  = { CRGB::DarkGreen, CRGB::Red,    CRGB::Blue, CRGB::DarkOrange };
CRGB light_color_palette[1] = { CRGB::LimeGreen, CRGB::Yellow, CRGB::Aqua, CRGB::Gold };
#endif // FASTLED_FIRE_PATTERN

static uint16_t nowVinputRBG; // latest button inputs, to compare with previous in myState

static RBGStateTable_t loopRow; // for use in setup() and loop() - since USE_PROGMEM, must copy to RAM 

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// setup()
//   initializes hardware serial port for general debug
//   initializes SoftwareSerial for DFPlayer audio player YX5200 control
//   initializes push button pins
//   initializes FastLED library
void setup() {
  // put your setup code here, to run once:

  // take care of the solenoid output pin ASAP
  pinMode(DPIN_SOLENOID,   OUTPUT);        // fires the rubber band
  // make sure solenoid or motor is not drawing power
  RBG_specialProcStopShoot(0); // serial port not initialized yet don't do debug printing

#if USE_PROGMEM   
  memcpy_P(&loopRow, &myStateTable[myState.tableRow], sizeof(myStateTable[0]));
#else // not USE_PROGMEM
  memcpy(&loopRow, &myStateTable[myState.tableRow], sizeof(myStateTable[0]));
#endif // use, not USE_PROGMEM

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
  pinMode(DPIN_BTN_RED,     INPUT_PULLUP); // configuration button
  pinMode(DPIN_AUDIO_BUSY,  INPUT_PULLUP); // tells when audio stops
  pinMode(DPIN_LOCK_LOAD,   INPUT_PULLUP); // tells if barrel is locked and loaded
  // and the other output pin
  pinMode(DPIN_UNUSED,      INPUT_PULLUP); // matches with BlueToothTesting.ino

  // initialize the DFPlayer audio player
  DFsetup();

  // initialize the FastLED library for our setup
  // according to Amazon comments: Library configuration used was WS2812B GRB (not RGB). Library call: FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);. Everything worked as expected.
  //    this was for the graduation cap: FastLED.addLeds<NEOPIXEL,DPIN_FASTLED>(led_display, NUM_LEDS_PER_DISK);
  FastLED.addLeds<WS2812B,DPIN_FASTLED,GRB>(led_display, NUM_LEDS_PER_DISK);
  FastLED.addLeds<WS2812B,DPIN_FASTLED_SNGL,GRB>(&led_sngl, 1);
  FastLED.setBrightness(BRIGHTMAX); // we will do our own power management
  // initialize led_display
  RBG_diskInitBrightSpots(windup1BrightSpots, &led_BLACK, 3, 196); // FIXME need initialize for this pattern

  // initialize FASTLED_SNGL to do the single LED inside the handle
  fill_rainbow( led_sngl_array, FASTLED_SNGLPTRNLEN, gHue, 21); // this just fills up the colors to send later
  led_sngl = led_sngl_array[0]; // load first color
  
  // if needed, initialize EEPROM variables
  eeprom_check_init(EEPROM_PROCESS_ALL_CONFIG);
  copy_eeprom_to_ram_running_config(EEPROM_CONFIG_RUNNING);
  // eeprom_factory_init(EEPROM_PROCESS_ALL_CONFIG);

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

#if USE_PROGMEM   
  memcpy_P(&loopRow, &myStateTable[myState.tableRow], sizeof(myStateTable[0]));
#else // not USE_PROGMEM
  memcpy(&loopRow, &myStateTable[myState.tableRow], sizeof(myStateTable[0]));
#endif // use, not USE_PROGMEM

  // put your main code here, to run repeatedly:

  static uint16_t preVinputRBG = 65535;

  myState.timerNow = millis();
  #if DEBUG_SHOW_MSEC
  globalLoopCount = myState.timerNow;
  #endif // DEBUG_SHOW_MSEC


  // handle (most of) solenoid OFF or motor OFF processing
  // Four factors: SOLENOID_IF_NONZERO, DLYSOLENOID_MIN and _MAX, releasing the trigger
  //   SOLENOID/CLOTHESPIN approach - ignore the trigger, just use the edge signal to start
  //                         hold the solenoid for at least DLYSOLENOID_MIN milliseconds
  //                         after that, when shooting sound finishes, then release the solenoid
  //                         release the solenoid after DLYSOLENOID_MAX milliseconds no matter what
  //   MOTOR/SIDEWINDER approach - we also take into account how long the trigger is held in
  //                         run the motor for at least DLYSOLENOID_MIN milliseconds
  //                         after that, when the trigger is released, stop the motor
  //                         stop the motor after DLYSOLENOID_MAX milliseconds no matter what
  // NOTE: this part does not depend on getButtonInput() and should happen immediately if conditions are met
  if ((myState.timerMaxForceSolenoidLow > 0) && (myState.timerNow > myState.timerMinForceSolenoidLow)) { // shooting and passed minimum
    if (myState.timerNow > myState.timerMaxForceSolenoidLow) {
      if (DEBUG_TRIGSTATE) { Serial.print(F("DEBUG TRIGSTATE 01 RBG_specialProcStopShoot() - nowVinputRBG 0x"));Serial.println(nowVinputRBG, HEX);  printAllMyState(); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
      RBG_specialProcStopShoot(SERIALDEBUG); // always turn off after maximum delay
    }
  }

  // see if time to run the state machine and process inputs
  if ((myState.timerNow-myState.timerPrevState) >= 40) { // || (myState.VinputRBG != nowVinputRBG)) { THIS MAKES RELEASING TRIGGER TOO FAST AFFECT SOUND START
    nowVinputRBG = getButtonInput();
    if (myState.timerMaxForceSolenoidLow > 0) { // shooting
      if ((SOLENOID_IF_NONZERO || (0 == (mVINP_TRIG_STATE & nowVinputRBG))) && (myState.timerNow > myState.timerMinForceSolenoidLow)) {
        if (DEBUG_TRIGSTATE) { Serial.print(F("DEBUG TRIGSTATE 02 RBG_specialProcStopShoot() - nowVinputRBG 0x")); Serial.println(nowVinputRBG, HEX);  printAllMyState(); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
        RBG_specialProcStopShoot(SERIALDEBUG); // (SOLENOID || trigger released), sound finished, beyond minimum time
      }
    }
    if (preVinputRBG != nowVinputRBG) {
      Serial.print(F("DEBUG loop() - nowVinputRBG 0x")); Serial.print(nowVinputRBG, HEX); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
    }
    preVinputRBG = nowVinputRBG;
    nowVinputRBG = RBG_processStateTable(nowVinputRBG);
    myState.timerPrevState = myState.timerNow;
    myState.VinputRBG = nowVinputRBG;
  } // end wait for next State activity

  // see if time to run the LED patterns
  dwell_led_sngl -= 1; // process the single LED in the handle
  if (dwell_led_sngl < 0) {
    dwell_led_sngl = FASTLED_SNGLDWELL;
    led_sngl = led_sngl_array[which_led_sngl];
    which_led_sngl += 1;
    if (which_led_sngl >= FASTLED_SNGLPTRNLEN) { which_led_sngl = 0; }
  }
  if ((myState.timerNow-myState.timerPrevLEDstep) >= myState.ptrnDelayLEDstep) {
    gHue += 3; // rotating "base color" used by Demo Reel 100 patterns
    checkDataGuard();
    doPattern(loopRow.efctLED, loopRow.SPECIAL, 0); // start
    checkDataGuard();
    FastLED.show();
    myState.timerPrevLEDstep = myState.timerNow;
    globalLoopCount += 1;
  } // end wait for next LED activity

}  // end loop()

// ******************************** LED UTILITIES ****************************************

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// doPattern(tmpEfctLED, tmpSpecial, tmpInit) - start or step the pattern
//
// If tmpInit is nonzero, do initialization of pattern
// If tmpSpecial says mSPCL_EFCT_CONFIGURE and efctSound == mNONE and cfg_curnum != mNONE then we use the configuration variables
// If tmpEfctLED is an EEPROM configurable pattern (divisible by 10) then configure it
//
#define DEBUG_DPtrn 0
//
void doPattern(uint16_t tmpEfctLED, uint16_t tmpSpecial, uint8_t tmpInit) {
//  static uint16_t prevEfctLED = mNONE;
  static uint16_t numSteps = 0;
  uint16_t nowEfctLED = tmpEfctLED & 0x00FF; // just the effect number

  #if DEBUG_DPtrn
  Serial.print(F(" DEBUG doPattern BEFORE tmpEfctLED ")); Serial.print(tmpEfctLED); Serial.print(F(" tmpInit ")); Serial.print(tmpInit); Serial.print(F(" final nowEfctLED ")); Serial.print(nowEfctLED); Serial.println(F(" that is all"));
  #endif // DEBUG_DPtrn

  if ((mNONE == nowEfctLED) && (0 != (mSPCL_EFCT_CONFIGURE & tmpSpecial)) && (mNONE != myState.cfg_curnum)) {
    // handle configuration choice effects
    nowEfctLED = myState.cfg_curnum + myState.cfg_type2save;
  } else if ((mNONE != nowEfctLED) && (EFCT_IS_EEP(nowEfctLED)) && (nowEfctLED <= mEFCT_LAST_EEP_CONFIG)) {
    // configurable LED patterns are zero mod 10; we get config from EEPROM
    // nowEfctLED += EEPROM.read(EEPOFFSET(nowEfctLED)+EEPROM_START_LED_CONFIGS); old way; now using EEPROM_RAMcopy
    nowEfctLED += EEPROM_RAMcopy[EEPOFFSET(nowEfctLED)+EEPROM_START_LED_CONFIGS];
  } // end if configurable LED pattern

  // now convert "configuration" effect number to pattern effect number
  #if DEBUG_DPtrn
  Serial.print(F(" DEBUG doPattern BEFORE lookupLEDpattern tmpEfctLED ")); Serial.print(tmpEfctLED); Serial.print(F(" tmpInit ")); Serial.print(tmpInit); Serial.print(F(" final nowEfctLED ")); Serial.print(nowEfctLED);
  Serial.print(F(" lookup(-1) ")); Serial.print(lookupLEDpattern(nowEfctLED-1)); Serial.print(F(" lookupLEDpattern lookup(+0) ")); Serial.print(lookupLEDpattern(nowEfctLED)); Serial.print(F(" lookupLEDpattern lookup(+1) ")); Serial.println(lookupLEDpattern(nowEfctLED+1)); 
  #endif // DEBUG_DPtrn
  nowEfctLED = lookupLEDpattern(nowEfctLED);
  tmpEfctLED = (0xFF00 & tmpEfctLED) | nowEfctLED;

  #if DEBUG_DPtrn
  Serial.print(F(" DEBUG doPattern AFTER  lookupLEDpattern tmpEfctLED ")); Serial.print(tmpEfctLED); Serial.print(F(" tmpInit ")); Serial.print(tmpInit); Serial.print(F(" final nowEfctLED ")); Serial.println(nowEfctLED);
  #endif // DEBUG_DPtrn

  switch (nowEfctLED) {

    case mEFCT_PTRNLED_OFF: // 254 = OFF
    default:
      if (0 != tmpInit) { // initialize
        for (uint8_t idx = 0; idx < NUM_RINGS_PER_DISK; idx++) {
          led_display[idx] = CRGB::Black;
        }
      } // there is no "step"; just leave the LEDs off
      break;

    case 1:
      juggle();
      break;

    case 2:
      rainbowWithGlitter();
      break;

    case 3:
      RBG_bpm_rings();
      break;

    case 4: // RBG_diskDownTheDrainOrRotate(-1) disk, clockwise, rotate through
      if (0 != tmpInit) { // initialize
        RBG_ringRotateAndFade(mNONE, 0, windup1BrightSpots); // FIXME - initialization from other effect
        RBG_diskDownTheDrainOrRotate(0);
      } else { // step
        RBG_diskDownTheDrainOrRotate(-1);
      }
      break;

    case 5: // RBG_diskDownTheDrainOrRotate(2) disk, counterclockwise, drain, repeat
      if ((0 != tmpInit) || (numSteps > (10+NUM_LEDS_PER_DISK))) { // initialize
        RBG_ringRotateAndFade(mNONE, 0, windup1BrightSpots); // FIXME - initialization from other effect
        numSteps = 0;
      } else { // step
        RBG_diskDownTheDrainOrRotate(2);
        numSteps += 1;
      }
      break;

    case 6: // RBG_juggle_numdot_ring(-4) rings, 4 dots
      RBG_juggle_numdot_ring(-4);
      break;

    case 7: // RBG_juggle_numdot_ring(5); RBG_confetti_fadeby(128); disk, 5 dots, sparkle confetti
      RBG_juggle_numdot_ring(5);
      RBG_confetti_fadeby(128);
      break;

    case 8:
      RBG_RailGunEffect(tmpInit, &led_BLUE);
      break;

    case 9:
      RBG_RailGunEffect(tmpInit, &led_RED);
      break;

    case 10:
      RBG_RailGunEffect(tmpInit, &led_GREEN);
      break;

    case 11:
      RBG_confetti_fadeby(128);
      break;

    case 12:
      bpm();
      break;

    case 13:
      confetti();
      break;
  } // end switch
} // end doPattern()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// lookupLEDpattern(nowEfctLED)
//
// nowEfctLED - "configured" LED pattern number. This already has EEPROM or CFG applied. Is not divisible by 10.
//
// The table used for this purpose is in PROGMEM
//
// returns: actual LED pattern number
//
uint16_t lookupLEDpattern(uint16_t nowEfctLED) {
  TYPEOF_lookupLEDpatternTbl myRetVal;

  nowEfctLED &= 0xFF; // must be 8 bits for actual pattern
  if (nowEfctLED == mEFCT_PTRNLED_OFF) {
    myRetVal = mEFCT_PTRNLED_OFF;
  } else if ((nowEfctLED >= mEFCT_UNIQ) || (0 == nowEfctLED)) {
    if (mNONE != nowEfctLED) {
      Serial.print(F("ERROR - lookupLEDpattern() out of range - ")); Serial.println(nowEfctLED);
    }
    myRetVal = mEFCT_PTRNLED_OFF;
  } else {
#if USE_PROGMEM
    if (sizeof(myRetVal) - sizeof(lookupLEDpatternTbl[0])) { // cannot use sizeof in #if statement
      Serial.print(F("ERROR FIXME SIZE MISMATCH TYPEOF_lookupLEDpatternTbl ")); Serial.print(sizeof(myRetVal)); Serial.println(sizeof(lookupLEDpatternTbl[0]));
      myRetVal = mEFCT_PTRNLED_OFF;
    } else {
      memcpy_P(&myRetVal, &lookupLEDpatternTbl[nowEfctLED-1], sizeof(myRetVal));
    }
#else // not USE_PROGMEM
    myRetVal = lookupLEDpatternTbl[nowEfctLED-1];
#endif // USE_PROGMEM
  }
  return(myRetVal);
} // end lookupLEDpattern(nowEfctLED)

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
// RBG_ringRotateAndFade(whichRing, rotateLcm, brightSpots) - rotate a single ring, fade to black, add in new bright spots
//
// whichRing - which ring to rotate, 0 through (NUM_RINGS_PER_DISK-1) {2 for RBG}
//                value = mNONE (255) means initialize entire disk (actually, anything > 2)
// rotateLcm - fraction of LCM_LEDS_PER_RING to rotate, +/-. With these rings, + is counter-clockwise and - is clockwise
// brightSpots - list of positions within ring and color for bright spots
// 
// writes over led_tmpRing and led_display
//
// #define DEBUG_RRandF 1
void RBG_ringRotateAndFade(uint8_t whichRing, int8_t rotateLcm, brightSpots_t* brightSpots) {
  int8_t idx;
  static int16_t startLocPerRing[NUM_RINGS_PER_DISK]; // (95 + 95 = 190) > 127 so int8_t will not work

  if (whichRing > (NUM_RINGS_PER_DISK-1)) {
    // initialize
    #ifdef DEBUG_RRandF
    Serial.print(F(" DEBUG_RRandF initialize whichRing=")); Serial.println(whichRing);
    #endif // DEBUG_RRandF
    myState.ptrnDelayLEDstep = DLYLED_ringRotateAndFade;
    RBG_diskInitBrightSpots(brightSpots, &led_BLACK, -3, 196);
    for (idx=0; idx < NUM_RINGS_PER_DISK; idx++) {
      startLocPerRing[idx] = 0;
    }
    // end initialize
  } else if ((whichRing >= 0) && (whichRing <= (NUM_RINGS_PER_DISK-1)) && (0 != rotateLcm)) {
    // process individual ring
    int8_t numLcmPerLED = LCM_LEDS_PER_RING / leds_per_ring[whichRing];
    int16_t numHere = startLocPerRing[whichRing] / numLcmPerLED;
    int16_t numEnd = (startLocPerRing[whichRing] + rotateLcm) / numLcmPerLED;
    int8_t moveBy;
    
    if (rotateLcm < 0) {
      moveBy = -1;
    } else {
      moveBy = 1;
    }
    startLocPerRing[whichRing] = (startLocPerRing[whichRing] + rotateLcm) % LCM_LEDS_PER_RING;
    #ifdef DEBUG_RRandF
    Serial.print(F(" DEBUG_RRandF ERROR CALL whichRing=")); Serial.println(whichRing);
    #endif // DEBUG_RRandF
    // end process individual ring
  } // end check on whichRing
} // end RBG_ringRotateAndFade()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_ringIdxIncrDecr(idx, idxRing, direction)
//
// idx - index of LED within ring. must be (start_per_ring[idxRing]) <= idx < (start_per_ring[idxRing]+leds_per_ring[idxRing])
// idxRing - which ring we are on, 0 <= idxRing < NUM_RINGS_PER_DISK
// direction - either -1, 0, or 1
// returns value modulus value of idx+direction where (start_per_ring[idxRing]) <= return < (start_per_ring[idxRing]+leds_per_ring[idxRing])
//
uint8_t RBG_ringIdxIncrDecr(uint8_t idx, uint8_t idxRing, int8_t direction) {
  int16_t rtn = idx + direction;

  if (rtn >= start_per_ring[idxRing]+leds_per_ring[idxRing]) {
    rtn = start_per_ring[idxRing];
  } else if (rtn < start_per_ring[idxRing]) {
    rtn = start_per_ring[idxRing]+leds_per_ring[idxRing];
  } // end if special case
  return((uint8_t) rtn);
} // end RBG_ringIdxIncrDecr(...)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_diskInitBrightSpots(brightSpots, color, direction, fade) - 
//
// brightSpots - list of positions within ring and color for bright spots
// pColor      - pointer to color to use as fill (typically &CRGB::Black)
// direction   - if zero, ignore direction and fade
//               if non-zero, take that many steps in that direction, fading to fade/256 value each step
// fade        - ignored if direction is zero, else fade/256 each step
//
void RBG_diskInitBrightSpots(brightSpots_t* brightSpots, CRGB* pColor, int8_t direction, uint16_t fade) {
  int16_t idxBrtspt, idxRing, idxFade, idx;
  CRGB myHue;

  for (idx=0; idx < NUM_LEDS_PER_DISK; idx++) {
    led_display[idx] = *pColor;
  } // end set all to pColor
  for (idxRing=0; idxRing<NUM_RINGS_PER_DISK; idxRing++) {
    for (idxBrtspt=0; (brightSpots[idxBrtspt].posn < leds_per_ring[idxRing]) && (idxBrtspt < leds_per_ring[idxRing]); idxBrtspt++) {
      myHue = brightSpots[idxBrtspt].hue;
      led_display[brightSpots[idxBrtspt].posn+start_per_ring[idxRing]] = myHue;
      // note: sgn(direction) is -1, 0, 1 for (direction < 0), (direction == 0), (direction > 0) respectively
      idxFade = brightSpots[idxBrtspt].posn+start_per_ring[idxRing];
      for (idxFade = RBG_ringIdxIncrDecr(idxFade, idxRing, direction); 0 != sgn(direction); idxFade = RBG_ringIdxIncrDecr(idxFade, idxRing, direction)) {
        myHue.fadeToBlackBy(fade);
        led_display[idxFade] = myHue;
        direction -= sgn(direction); // decrement the count
      } // end do fade if requested
    } // end for all bright spots this ring
  } // end for all rings
} // end RBG_diskInitBrightSpots(...)

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
} // end RBG_diskRotateOrDrain()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_ringRotateOrDrain(direction, pColor, whichRing) - 
//
// direction - +/- 1 = rotate through, +/- 2 = down drain. With these rings, + is counter-clockwise and - is clockwise
// pColor    - pointer to color to use as fill (typically &CRGB::Black)
// whichRing - which ring to rotate, 0 through (NUM_RINGS_PER_DISK-1) {2 for RBG}
// 
void RBG_ringRotateOrDrain(int8_t direction, CRGB* pColor, uint8_t whichRing) {
  // do rotate/drain
  int16_t idx;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_RailGunEffect(myInit, pColor)
//
// myInit - nonzero for initialization
//
// do 27 cycles; be long enough for any of the SHOOT sounds
//
#define DEBUG_RBG_RailGunEffect 0
void RBG_RailGunEffect(uint8_t myInit, CRGB* pColor) {
  static uint16_t myStep = 0;
  static int8_t lastState = 99;
  uint8_t idx;

#if DEBUG_RBG_RailGunEffect
  Serial.print(F("DEBUG rail BEFORE myInit=")); Serial.print(myInit); Serial.print(F(" myStep=")); Serial.print(myStep); Serial.print(F(" ptrnDelayLEDstep=")); Serial.print(myState.ptrnDelayLEDstep); Serial.print(F(" millis()=")); Serial.print(millis()); Serial.print(F(" timerNow=")); Serial.print(myState.timerNow); Serial.print(F(" timerPrevLEDstep=")); Serial.print(myState.timerPrevLEDstep); Serial.print(F(" lastState=")); Serial.println(lastState);
#endif // DEBUG_RBG_RailGunEffect
  if (0 != myInit) {
    myStep = 0;
    myState.ptrnDelayLEDstep = 25;
    lastState = -1; // DEBUG
    for (idx = 0; idx < NUM_LEDS_PER_DISK; idx++) { led_display[idx] = led_BLACK; }
  } else {
    if (myStep < 8*4*27) { // 27 cycles
      switch ((myStep / 8) % 4) {
        case 0: // after some black, set ring[2] to the color
          for (idx = start_per_ring[2]; idx < start_per_ring[2]+leds_per_ring[2]; idx++) {
            led_display[idx] = *pColor;
          } // end for smallest ring
          lastState = 0; // DEBUG
          break;
        case 1: // set ring[2] black and set ring[1] to the color
          for (idx = start_per_ring[2]; idx < start_per_ring[2]+leds_per_ring[2]; idx++) {
            led_display[idx] = led_BLACK;
          }
          for (idx = start_per_ring[1]; idx < start_per_ring[1]+leds_per_ring[1]; idx++) {
            led_display[idx] = *pColor;
          } // end for middle ring
          lastState = 1; // DEBUG
          break;
        case 2: // set ring[1] black and set ring[0] to the color
          for (idx = start_per_ring[1]; idx < start_per_ring[1]+leds_per_ring[1]; idx++) {
            led_display[idx] = led_BLACK;
          } // end for smallest ring
          for (idx = start_per_ring[0]; idx < start_per_ring[0]+leds_per_ring[0]; idx++) {
            led_display[idx] = *pColor;
          } // end for largest ring
          lastState = 2; // DEBUG
          break;
        case 3: // do speed-up and set ring[0] black for next cycle
          if (myStep < 8*4*1) {
            myState.ptrnDelayLEDstep = 16; // speed it up
          } else if (myStep < 8*4*2) {
            myState.ptrnDelayLEDstep = 7; // speed it up
          }
          for (idx = start_per_ring[0]; idx < start_per_ring[0]+leds_per_ring[0]; idx++) {
            led_display[idx] = led_BLACK;
          } // all black
          lastState = 3; // DEBUG
          break;
      } // end switch every eight intervals
      myStep += 1;
      // end for 27 cycles
    } else {
      // then just effect
      RBG_confetti_fadeby(128);
      lastState = 4; // DEBUG
      // confetti();
    } // end if lots of steps
  } // end if not initialization
#if DEBUG_RBG_RailGunEffect
  Serial.print(F("DEBUG rail AFTER  myInit=")); Serial.print(myInit); Serial.print(F(" myStep=")); Serial.print(myStep); Serial.print(F(" ptrnDelayLEDstep=")); Serial.print(myState.ptrnDelayLEDstep); Serial.print(F(" millis()=")); Serial.print(millis()); Serial.print(F(" timerNow=")); Serial.print(myState.timerNow); Serial.print(F(" timerPrevLEDstep=")); Serial.print(myState.timerPrevLEDstep); Serial.print(F(" lastState=")); Serial.println(lastState);
#endif // DEBUG_RBG_RailGunEffect
} // end RBG_RailGunEffect()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_bpm_rings() - a variant of one of Mark Kriegsman's classic DemoReel100.ino patterns
//
void RBG_bpm_rings() { // my mod of pattern from Demo Reel 100
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
} // end RBG_bpm_rings()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_confetti_fadeby(fadeVal) - a variant of one of Mark Kriegsman's classic DemoReel100.ino patterns
//
// fadeVal -  // 8 bit, 1 = slow, 255 = fast
//
void RBG_confetti_fadeby(uint8_t fadeVal) { // pattern from Demo Reel 100
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(led_display, NUM_LEDS_PER_DISK, fadeVal);
  int pos = random16(NUM_LEDS_PER_DISK);
  led_display[pos] += CHSV( gHue + random8(64), 200, 255);
} // end confetti()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_juggle_numdot_ring(numDots) - a variant of one of Mark Kriegsman's classic DemoReel100.ino patterns
//
// numDots: >0 - number of dots, travel entire disk
//          <0 - number of dots, travel within rings
//          =0 - same as 8
//
void RBG_juggle_numdot_ring(int8_t numDots) { // pattern from Demo Reel 100
  // colored dots, weaving in and out of sync with each other
  byte dothue = 0;

  fadeToBlackBy( led_display, NUM_LEDS_PER_DISK, 20);
  if (0 == numDots) { numDots = 8; }
  if (0 < numDots) {
    for( int i = 0; i < numDots; i++) {
      led_display[beatsin16(i+7,0,NUM_LEDS_PER_DISK-1)] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
  } else { // <0 means travel within rings
    uint16_t tmp;
    numDots = -numDots; // make it >0
    if (numDots > MIN_LEDS_PER_RING) { numDots = MIN_LEDS_PER_RING; }
    for ( uint8_t ring = 0; ring < NUM_RINGS_PER_DISK; ring++ ) {
      for( int i = 0; i < numDots; i++) {
        tmp = beatsin16(i+7,start_per_ring[ring],start_per_ring[ring]+leds_per_ring[ring]-1);
        led_display[tmp] |= CHSV(dothue, 200, 255);
        dothue += 32;
      } // end for dots
    } // end for rings
  } // end if rings or whole disk
} // end RBG_juggle_numdot_ring()


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// a few of Mark Kriegsman's classic DemoReel100.ino patterns
//
 
void rainbow() { // pattern from Demo Reel 100
  // FastLED's built-in rainbow generator
  fill_rainbow( led_display, NUM_LEDS_PER_DISK, gHue, 7);
} // end rainbow()

void rainbowWithGlitter() { // pattern from Demo Reel 100
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(100);
} // end rainbowWithGlitter()

void addGlitter( fract8 chanceOfGlitter) { // helper routine from Demo Reel 100
  if( random8() < chanceOfGlitter) {
    led_display[ random16(NUM_LEDS_PER_DISK) ] += CRGB::White;
  }
} // end addGlitter()

void confetti() { // pattern from Demo Reel 100
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( led_display, NUM_LEDS_PER_DISK, 10);
  int pos = random16(NUM_LEDS_PER_DISK);
  led_display[pos] += CHSV( gHue + random8(64), 200, 255);
} // end confetti()

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
  static RBGStateTable_t procRow;

#if USE_PROGMEM
  memcpy_P(&procRow, &myStateTable[myState.tableRow], sizeof(myStateTable[0]));
#else // not USE_PROGMEM
  memcpy(&procRow, &myStateTable[myState.tableRow], sizeof(myStateTable[0]));
#endif // use, not USE_PROGMEM

  // see if need to start a new row
  if (prevRow != myState.tableRow) { // start a new row
    debugThisManyCalls = DEBUG_STATE_MACHINE*10; // will be interesting for a bit
    RBG_startRow(&procRow); // just do what the row says
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
    } else if ((mNONE != procRow.SPECIAL) && (0 != (procRow.SPECIAL & (mSPCL_EFCT_CONTINUOUS | mSPCL_EFCT_CONFIGURE))) && (0 == (tmpVinputRBG&mVINP_SOUNDACTV))) {
      // restart a continuous sound
      if (debugThisManyCalls > 0) {
        printAllMyState(); Serial.print(F("DEBUG RBG_processStateTable() - tmpVinputRBG 0x")); Serial.print(tmpVinputRBG, HEX); Serial.print(F(" restart sound ")); Serial.print(procRow.efctSound); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
        debugThisManyCalls -= 1;
      }
      RBG_startEffectSound(procRow.efctSound, procRow.SPECIAL);
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
  static RBGStateTable_t waitRow;
  uint16_t waitRowIdx = myState.tableRow;

#if USE_PROGMEM
  memcpy_P(&waitRow, &myStateTable[waitRowIdx], sizeof(myStateTable[0]));
#else // not USE_PROGMEM
  memcpy(&waitRow, &myStateTable[waitRowIdx], sizeof(myStateTable[0]));
#endif // use, not USE_PROGMEM


  // we need to check until we hit the mBLOCKEND
  for (uint16_t idx = myState.tableRow; (idx < NUMOF(myStateTable)) && (mNONE == thisReturn); idx++) {
    // see if we match input condition for this row
    if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.print(idx); Serial.print(F(" waitRow.inputRBG 0x")); Serial.print(waitRow.inputRBG, HEX); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
    if (debugThisManyCalls > 0) { Serial.print(F("    waitRow.SPECIAL&mSPCL_HANDLER 0x")); Serial.println(waitRow.SPECIAL&mSPCL_HANDLER, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    waitRow.SPECIAL&mSPCL_EFCT_ONETIME 0x")); Serial.print(waitRow.SPECIAL&mSPCL_EFCT_ONETIME, HEX); Serial.print(F(" tmpVinputRBG&mVINP_SOUNDACTV 0x")); Serial.println(tmpVinputRBG&mVINP_SOUNDACTV, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    waitRow.inputRBG&mINP_TRIG 0x")); Serial.print(waitRow.inputRBG&mINP_TRIG, HEX); Serial.print(F(" tmpVinputRBG&mVINP_TRIG_EDGE 0x")); Serial.println(tmpVinputRBG&mVINP_TRIG_EDGE, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    waitRow.inputRBG&mINP_OPEN 0x")); Serial.print(waitRow.inputRBG&mINP_OPEN, HEX); Serial.print(F(" tmpVinputRBG&mVINP_OPEN 0x")); Serial.println(tmpVinputRBG&mVINP_OPEN, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    waitRow.inputRBG&mINP_LOCK 0x")); Serial.print(waitRow.inputRBG&mINP_LOCK, HEX); Serial.print(F(" tmpVinputRBG&mVINP_LOCK 0x")); Serial.println(tmpVinputRBG&mVINP_LOCK, HEX); }

    if ((mNONE != waitRow.SPECIAL) && (0 != (waitRow.SPECIAL & mSPCL_HANDLER))) { // special handler
      // no sounds no LEDs for mSPCL_HANDLER; it gets called exactly once
      thisReturn = RBG_specialProcessing(tmpVinputRBG, waitRow.SPECIAL, waitRow.storeVal, waitRow.storeAddr);
      if (mNONE == thisReturn) {
        thisReturn = waitRow.gotoWithoutInput; // this one uses WithoutInput not OnInput
      }
      Serial.print(F(" RBG_waitForInput mSPCL_HANDLER thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
    } else if ((0 != (waitRow.SPECIAL&mSPCL_EFCT_ONETIME)) && (0 == (tmpVinputRBG&mVINP_SOUNDACTV))) {
      thisReturn = waitRow.gotoWithoutInput; // this one uses WithoutInput not OnInput
      Serial.print(F(" RBG_waitForInput mSPCL_EFCT_ONETIME thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
    } else if ((mNONE != (waitRow.inputRBG)) && (0 != (waitRow.inputRBG&mINP_TRIG)) && (0 != (tmpVinputRBG&mVINP_TRIG_EDGE))) {
      // two cases for trigger: trigger + any of the listed buttons (but at least one of them) OR trigger + exact match with buttons listed (even if no button listed)
      if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.print(idx); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
      if ((0 != (waitRow.inputRBG&mINP_BANY)) && (0 != (waitRow.inputRBG&mINP_B07&tmpVinputRBG))) {
        // mINP_BANY means any of the listed buttons but at least one
        if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.print(idx); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
        thisReturn = waitRow.gotoOnInput;
        Serial.print(F(" RBG_waitForInput mINP_TRIG mINP_BANY thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
        break;
      } else if ((mNONE != (waitRow.inputRBG)) && ((tmpVinputRBG&mINP_B07) == (waitRow.inputRBG&mINP_B07))) {
        // else we must match buttons listed exactly, even if there are no buttons listed
        if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.print(idx); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
        thisReturn = waitRow.gotoOnInput;
        Serial.print(F(" RBG_waitForInput mINP_TRIG mINP_BANY thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
        break;
      }
    } else if ((mNONE != (waitRow.inputRBG)) && (0 != (waitRow.inputRBG&mINP_OPEN)) && (0 != (tmpVinputRBG&mVINP_OPEN))) {
      thisReturn = waitRow.gotoOnInput;
      Serial.print(F(" RBG_waitForInput mINP_OPEN thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
    } else if ((mNONE != (waitRow.inputRBG)) && (0 != (waitRow.inputRBG&mINP_LOCK)) && (0 != (tmpVinputRBG&mVINP_LOCK))) {
      thisReturn = waitRow.gotoOnInput; // found an input we were waiting for
      Serial.print(F(" RBG_waitForInput mINP_LOCK thisReturn ")); Serial.print(thisReturn); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
    }

    if (0 != (waitRow.blkFlags&mBLOCKEND)) {
      // this is a normal way to end - found the mBLOCKEND but did not find input
      break;
    } else {
      // continue until we do reach mBLOCKEND
      waitRowIdx += 1;
#if USE_PROGMEM
      memcpy_P(&waitRow, &myStateTable[waitRowIdx], sizeof(myStateTable[0]));
#else // not USE_PROGMEM
      memcpy(&waitRow, &myStateTable[waitRowIdx], sizeof(myStateTable[0]));
#endif // use, not USE_PROGMEM
    }
  } // end while searching for mBLOCKEND

  if (debugThisManyCalls >= 1) debugThisManyCalls -= 1;

  return(thisReturn);
} // end RBG_waitForInput()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcessing(tmpVinputRBG, tmpSpecial, tmpStoreVal, tmpStoreAddr)
//   do the SPECIAL processing - mostly the solenoid stuff (AKA motor if SIDEWINDER implementation)
//
// This is a belt-and-suspenders approach from the state table to have an alternate way of releasing the solenoid/motor.
// Circumstances can happen where this routine would not release the solenoid; however, code in the main loop will
//    keep monitoring all the factors below and catch that case.
//
// Four factors: SOLENOID_IF_NONZERO, DLYSOLENOID_MIN and _MAX, releasing the trigger
//   SOLENOID/CLOTHESPIN approach - ignore the trigger, just use the edge signal to start
//                         hold the solenoid for at least DLYSOLENOID_MIN milliseconds
//                         after that, when shooting sound finishes, then release the solenoid
//                         release the solenoid after DLYSOLENOID_MAX milliseconds no matter what
//   MOTOR/SIDEWINDER approach - we also take into account how long the trigger is held in
//                         run the motor for at least DLYSOLENOID_MIN milliseconds
//                         after that, when the trigger is released, stop the motor
//                         stop the motor after DLYSOLENOID_MAX milliseconds no matter what
//
// return mNONE to have next level up decide where to jump
// otherwise return an mROW value
//
uint16_t RBG_specialProcessing(uint16_t tmpVinputRBG, uint16_t tmpSpecial, uint16_t tmpStoreVal, uint16_t tmpStoreAddr) {
  uint16_t myVinputRBG = tmpVinputRBG;
  uint16_t mySpec = tmpSpecial & (mSPCL_HANDLER-1);
  uint16_t myRet = mNONE;

  switch (mySpec) {
    case mSPCL_HANDLER_SHOOT: // SHOOT
      RBG_specialProcShoot();
      break;
    case mSPCL_HANDLER_SOLENOID: // SOLENOID HANDLING
      if (myState.dynamicMode != mNONE) { // only update dynamicMode if end of shooting effects
        myState.dynamicMode = (myState.dynamicMode+1) % NUM_EEPROM_CONFIGURATIONS;
        copy_eeprom_to_ram_running_config(myState.dynamicMode);
      }
      // this is a special function in the state table to make sure solenoid gets turned off. Shooting sound is finished.
      if (millis() > myState.timerMinForceSolenoidLow) { // we always wait at least the minimum
        if ((SOLENOID_IF_NONZERO) || (1 == ( nowVinputRBG & mVINP_TRIG_STATE))) { // if MOTOR/SIDEWINDER, do not stop shooting here unless trigger is released
          if (DEBUG_TRIGSTATE) { Serial.print(F("DEBUG TRIGSTATE 03 RBG_specialProcStopShoot() - nowVinputRBG 0x"));Serial.println(nowVinputRBG, HEX);  printAllMyState(); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount); }
          RBG_specialProcStopShoot(SERIALDEBUG);
        }
      } // end if time is past the minimum solenoid/motor activation time
      break;
    case mSPCL_HANDLER_CFGSTART: // START CONFIGURATION CHOICES AT FIRST CHOICE
      RBG_specialProcConfigStart(tmpStoreAddr, tmpStoreVal);
      break;
    case mSPCL_HANDLER_CFGNEXT: // GO TO NEXT CONFIGURATION CHOICE
      RBG_specialProcConfigNext();
      break;
    case mSPCL_HANDLER_CFG2STORAGE: // COPY A CONFIGURATION CHOICE TO EEPROM
      RBG_specialProcConfig2Storage();
      break;
    case mSPCL_HANDLER_CFG2STORAGESKIP:
      myRet = RBG_specialProcConfig2Storage(); // RETURN THE SKIP FOR USER CHOICE
      break;
    case mSPCL_HANDLER_CFG2CPYRST: // RETURN THE SKIP FOR FACTORY RESET OR CONFIGURATION COPY
    case mSPCL_HANDLER_CFG2ADVNCD: // RETURN THE SKIP FOR ADVANCE SETTINGS
      myRet = RBG_specialProcCfgCpyRst_skip(tmpStoreVal);
      break;
    case mSPCL_HANDLER_FACT2RUN: // FACTORY RESET RUNNING CONFIG ONLY
      eeprom_factory_init(EEPROM_CONFIG_RUNNING);
      break;
    case mSPCL_HANDLER_FACT2ALL: // FACTORY RESET ALL CONFIGS
      eeprom_factory_init(EEPROM_PROCESS_ALL_CONFIG);
      break;
    case mSPCL_HANDLER_RUN2ONE: // COPY RUNNING CONFIG -> ONE
      copy_eeprom_to_eeprom(EEPROM_CONFIG_RUNNING, EEPROM_SAVED_ONE);
      break;
    case mSPCL_HANDLER_RUN2TWO: // COPY RUNNING CONFIG -> TWO
      copy_eeprom_to_eeprom(EEPROM_CONFIG_RUNNING, EEPROM_SAVED_TWO);
      break;
    case mSPCL_HANDLER_RUN2THREE: // COPY RUNNING CONFIG -> THREE
      copy_eeprom_to_eeprom(EEPROM_CONFIG_RUNNING, EEPROM_SAVED_THREE);
      break;
    case mSPCL_HANDLER_ONE2RUN: // COPY CONFIG ONE -> RUNNING
      copy_eeprom_to_eeprom(EEPROM_SAVED_ONE, EEPROM_CONFIG_RUNNING);
      break;
    case mSPCL_HANDLER_TWO2RUN: // COPY CONFIG TWO -> RUNNING
      copy_eeprom_to_eeprom(EEPROM_SAVED_TWO, EEPROM_CONFIG_RUNNING);
      break;
    case mSPCL_HANDLER_THREE2RUN: // COPY CONFIG THREE -> RUNNING
      copy_eeprom_to_eeprom(EEPROM_SAVED_THREE, EEPROM_CONFIG_RUNNING);
      break;
    case mSPCL_HANDLER_STATICMODE: // SET STATIC MODE - Don't Cycle Through Configurations
      myState.dynamicMode = mNONE; // dynamicMode == mNONE just do running effects from EEPROM_CONFIG_RUNNING
      copy_eeprom_to_ram_running_config(myState.dynamicMode);
      break;
    case mSPCL_HANDLER_ADVFEATURES: // ENABLE TIME TRAVEL AND TELEPORTATION CAPABILITIES (REQUIRES PASSWORD)
      // nothing needed
      break;
    default:
      Serial.print(F(" RBG_specialProcessing ERROR ln ")); Serial.print((uint16_t) __LINE__);  Serial.print(F(" mySpec ")); Serial.print(mySpec);  Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
      break;
  } // end switch on type of special
  return(myRet);
} // end RBG_specialProcessing(uint16_t tmpVinputRBG)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcConfigStart(tmpStoreAddr, tmpStoreVal) - prepare for configuration list
//
// tmpStoreAddr - code: mADDR_CFG_CATEGORY, mADDR_CFG_TYPE, mADDR_CFG_EFFECT, etc.
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//
void RBG_specialProcConfigStart(uint16_t tmpStoreAddr, uint16_t tmpStoreVal) {
  // initialize numbers for mSPCL_EFCT_CONFIGURE
  myState.cfg_curnum = 1; // current number for configuration list of choices
  if (mADDR_CFG_CATEGORY == tmpStoreAddr) {
    myState.cfg_maxnum = mCFG_CATEGORY_MAXNUM; // sound or LED pattern or ...
    myState.cfg_category = mCFG_CATEGORY_SOUND; // so we can speak choices
    myState.cfg_category2save = mNONE;
    myState.cfg_type = EEPOFFSET(mEFCT_UNIQ_CFG_SOUNDS_DESCRIP)*10; // sounds for descriptions of types
    myState.cfg_type2save = mNONE;
  } else if (mADDR_CFG_TYPE == tmpStoreAddr) {
    if (mADDR_CFG_CATEGORY != myState.cfg_addr) {
      Serial.print(F("ERROR RBG_specialProcConfigStart mADDR_CFG_TYPE and prev addr not mADDR_CFG_CATEGORY but ")); Serial.print(myState.cfg_addr); Serial.print(F(" on row ")); Serial.println(myState.tableRow);
    }
    myState.cfg_maxnum = EEPOFFSET(mEFCT_UNIQ);
    myState.cfg_category = mCFG_CATEGORY_SOUND; // so we can speak choices
    myState.cfg_type = EEPOFFSET(mEFCT_UNIQ_CFG_WINDUP_DESCRIP)*10; // sounds for descriptions of types
    myState.cfg_type2save = mNONE;
  }
  else if (mADDR_CFG_EFFECT == tmpStoreAddr) {
    if (mADDR_CFG_TYPE != myState.cfg_addr) {
      Serial.print(F("ERROR RBG_specialProcConfigStart mADDR_CFG_EFFECT and prev addr not mADDR_CFG_TYPE but ")); Serial.print(myState.cfg_addr); Serial.print(F(" on row ")); Serial.println(myState.tableRow);
    }
    myState.cfg_category = myState.cfg_category2save; // so we can show either sound or LED pattern
    if (1 == myState.cfg_category2save) {
      myState.cfg_maxnum = cfgMaxSoundForType[myState.cfg_category2save, EEPOFFSET(myState.cfg_type2save)];
    } else {
      myState.cfg_maxnum = cfgMaxLEDForType[myState.cfg_category2save, EEPOFFSET(myState.cfg_type2save)];
    }
  } else if (mADDR_CFG_CPY_RST == tmpStoreAddr) {
    myState.cfg_maxnum = tmpStoreVal; // EFCT_TYPE_OFFSET(mEFCT_UNIQ_CFG_MGMT_08);
    myState.cfg_category = mCFG_CATEGORY_SOUND; // so we can speak choices
    myState.cfg_category2save = mNONE;
    myState.cfg_type = mEFCT_UNIQ_CFG_MGMT_01 - EFCT_TYPE_OFFSET(mEFCT_UNIQ_CFG_MGMT_01);
    myState.cfg_type2save = mNONE;
  } else if (mADDR_CFG_ADVANCED == tmpStoreAddr) {
    myState.cfg_maxnum = tmpStoreVal;
    myState.cfg_category = mCFG_CATEGORY_SOUND; // so we can speak choices
    myState.cfg_category2save = mNONE;
    myState.cfg_type = mEFCT_UNIQ_CFG_ADVANCED_01 - EFCT_TYPE_OFFSET(mEFCT_UNIQ_CFG_ADVANCED_01);
    myState.cfg_type2save = mNONE;
  } else {
    Serial.print(F("ERROR RBG_specialProcConfigStart tmpStoreAddr is ")); Serial.print(tmpStoreAddr); Serial.print(F(" on row ")); Serial.println(myState.tableRow);
  }
  myState.cfg_addr = tmpStoreAddr; // code: mADDR_CFG_CATEGORY, mADDR_CFG_TYPE, or mADDR_CFG_EFFECT
  #if DEBUG_CONFIG
  Serial.print(F(" RBG_specialProcConfigStart cfg_curnum ")); Serial.print((uint16_t) myState.cfg_curnum); Serial.print(F(" cfg_maxnum ")); Serial.print((uint16_t) myState.cfg_maxnum); Serial.print(F(" cfg_category2save ")); Serial.print((uint16_t) myState.cfg_category2save); Serial.print(F(" cfg_type2save ")); Serial.println((uint16_t) myState.cfg_type2save);
  #endif // DEBUG_CONFIG
} // end RBG_specialProcConfigStart()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcConfigNext() - prepare for next item in configuration list
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//
void RBG_specialProcConfigNext() {
  // go to next choice in list of choices. Loop if needed.
  #if DEBUG_CONFIG
  Serial.print(F(" RBG_specialProcConfigNext B4 cfg_curnum ")); Serial.print((uint16_t) myState.cfg_curnum); Serial.print(F(" cfg_maxnum ")); Serial.print((uint16_t) myState.cfg_maxnum);
  #endif // DEBUG_CONFIG
  if (myState.cfg_curnum >= myState.cfg_maxnum) {
    myState.cfg_curnum = 1;
  } else {
    myState.cfg_curnum += 1;
  }
  #if DEBUG_CONFIG
  Serial.print(F(" so set cfg_curnum to ")); Serial.println((uint16_t) myState.cfg_curnum);
  #endif // DEBUG_CONFIG
} // end RBG_specialProcConfigNext()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcConfig2Storage() - store choice in proper place in EEPROM
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//      UNLESS caller decides to use the return myRet as an mROW to jump to
//
uint16_t RBG_specialProcConfig2Storage() {
  // store choice in either EEPROM or myState
  uint16_t myRet = mNONE; // flag not to use the return category

  switch (myState.cfg_addr) { //  mADDR_CFG_CATEGORY, mADDR_CFG_TYPE, mADDR_CFG_EFFECT
    case mADDR_CFG_CATEGORY:
      myState.cfg_category = mCFG_CATEGORY_SOUND; // so we can speak choices
      myState.cfg_category2save = myState.cfg_curnum;
      myRet = myState.tableRow + myState.cfg_curnum; // we could skip by the choice number
      break;
    case mADDR_CFG_TYPE:
      myState.cfg_type = myState.cfg_type2save = (myState.cfg_curnum-1) * 10; // reconstruct type
      myState.cfg_category = myState.cfg_category2save; // so we can show LED patterns or make sounds
      break;
    case mADDR_CFG_EFFECT:
      // store the selection in EEPROM
      uint8_t eepromBase;
      switch (myState.cfg_category2save) {
        case mCFG_CATEGORY_SOUND:
          eepromBase = EEPROM_START_SOUND_CONFIGS;
          break;
        case mCFG_CATEGORY_LEDPTRN:
          eepromBase = EEPROM_START_LED_CONFIGS;
          break;
        default:
          Serial.print(F(" RBG_specialProcConfig2Storage ERROR bad myState.cfg_category ")); Serial.print((uint16_t) myState.cfg_category);
          break;
      } // end switch on myState.cfg_category2save
      #if DEBUG_CONFIG
      Serial.print(F(" RBG_specialProcConfig2Storage mADDR_CFG_EFFECT cfg_curnum ")); Serial.print((uint16_t) myState.cfg_curnum); Serial.print(F(" cfg_category2save ")); Serial.print((uint16_t) myState.cfg_category2save); Serial.print(F(" EEPOFFSET(cfg_type2save) ")); Serial.print((uint16_t) EEPOFFSET(myState.cfg_type2save)); Serial.print(F(" eepromBase ")); Serial.println((uint16_t) eepromBase);
      #endif // DEBUG_CONFIG
      eeprom_store_with_chksum(eepromBase+EEPOFFSET(myState.cfg_type2save), myState.cfg_curnum);
      myState.cfg_maxnum =  myState.cfg_category = myState.cfg_category2save = myState.cfg_type = myState.cfg_type2save = mNONE;
      break;
    case mADDR_CFG_CPY_RST:
      myState.cfg_category = mCFG_CATEGORY_SOUND; // so we can speak choices
      myState.cfg_type = myState.cfg_type2save = mEFCT_UNIQ_CFG_MGMT_01 - EFCT_TYPE_OFFSET(mEFCT_UNIQ_CFG_MGMT_01); // do the config copies and factory reset choices
      myRet = myState.tableRow + myState.cfg_curnum; // we could skip by the choice number
      break;
    default:
      Serial.print(F(" RBG_specialProcConfig2Eeprom ERROR bad myState.cfg_addr ")); Serial.print((uint16_t) myState.cfg_addr);
      break;
  } // end switch on myState.cfg_addr
  return(myRet);
} // end RBG_specialProcConfig2Storage()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcCfgCpyRst_skip(maxSkip) - skip based on the choice
//    implements the skip based on the choice of factory resets or configuration copies
//    then cleans up from being in configuration
// maxSkip - from the row data .storeVal - this is the maximum number of rows we should skip
//           minimum we should skip is 1 row
// returns next row to go to
//
uint16_t RBG_specialProcCfgCpyRst_skip(uint8_t maxSkip) {
  uint16_t myRet = myState.tableRow + min(max(1, myState.cfg_curnum), maxSkip); // don't let it get crazy
  myState.cfg_maxnum =  myState.cfg_category = myState.cfg_category2save = myState.cfg_type = myState.cfg_type2save = myState.cfg_addr = mNONE;
  return(myRet);
} // end RBG_specialProcCfgCpyRst_skip()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcShoot() - do the solenoid for shooting
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//
//   SIDEWINDER initial approach - let the motor turn for DLYSOLENOID_MAX milliseconds or until firing sound finishes, whichever is first.
//   CLOTHESPIN approach - hold the solenoid for at least DLYSOLENOID_MIN milliseconds
//                         release the solenoid after DLYSOLENOID_MAX milliseconds or after firing sound finishes, whichever is first.
//
void RBG_specialProcShoot() {
  digitalWrite(DPIN_SOLENOID, HIGH);
  myState.timerMinForceSolenoidLow = millis() + DLYSOLENOID_MIN;
  myState.timerMaxForceSolenoidLow = myState.timerMinForceSolenoidLow + DLYSOLENOID_MAX - DLYSOLENOID_MIN;
  Serial.print(F(" RBG_specialProcShoot HIGH timerMaxForceSolenoidLow ")); Serial.print(myState.timerMaxForceSolenoidLow); Serial.print(F(" timerNow ")); Serial.print(myState.timerNow); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
} // end RBG_specialProcShoot()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcStopShoot(doDebugPrint) - release the solenoid or stop the motor after shooting
//
// doDebugPrint - non-zero to do the debug printing on USB serial port
//
//   All RBG_specialProcXxx routines get called exactly one time then move to .gotoWithoutInput
//
//   SIDEWINDER and CLOTHESPIN approach the same, based on DLYSOLENOID_MAX, DLYSOLENOID_MIN
//       run the motor/solenoid for a minimum of DLYSOLENOID_MIN milliseconds, then stop when either
//            DLYSOLENOID_MAX time expires
//            trigger is released
//
void RBG_specialProcStopShoot(uint16_t doDebugPrint) {
  digitalWrite(DPIN_SOLENOID, LOW);
  if ((doDebugPrint && SERIALDEBUG) || DEBUG_TRIGSTATE) {
    Serial.print(F(" RBG_specialProcStopShoot DPIN_SOLENOID=LOW timerMaxForceSolenoidLow ")); Serial.print(myState.timerMaxForceSolenoidLow); Serial.print(F(" timerMinForceSolenoidLow ")); Serial.print(myState.timerMinForceSolenoidLow); Serial.print(F(" timerNow ")); Serial.print(myState.timerNow); Serial.print(F(" dynamicMode ")); Serial.print(myState.dynamicMode); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
  }
  myState.timerMaxForceSolenoidLow = 0;
  myState.timerMinForceSolenoidLow = 0;
} // end RBG_specialProcStopShoot()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_startEffectLED(tmpEfctLED, tmpSpecial) - starts a new LED pattern
//
// tmpEfctLED - 8 LSBits is pattern number - EEPROM configurable or uniq
//              8 MSBits reservered for parameter
// both EEPROM configuration of pattern and configuration choice effects are handled in doPattern
//
void RBG_startEffectLED(uint16_t tmpEfctLED, uint16_t tmpSpecial) {
  uint16_t myEfctLED = tmpEfctLED & 0x00FF; // just the effect number; allows bits later

  if ((mNONE != myEfctLED) ||
      ((0 != (mSPCL_EFCT_CONFIGURE & tmpSpecial)) && (mNONE != myState.cfg_category) && (mNONE == myEfctLED))) {
    #if DEBUG_STATE_MACHINE
    Serial.print(F(" RBG_startEffectLED ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" EFCT num ")); Serial.print(tmpEfctLED); Serial.print(F(" loopCount ")); Serial.println(globalLoopCount);
    if ((0 != (mSPCL_EFCT_CONFIGURE & tmpSpecial)) && (mCFG_CATEGORY_LEDPTRN == myState.cfg_category) && (mNONE == myEfctLED)) {
      Serial.print(F(" RBG_startEffectLED mSPCL_EFCT_CONFIGURE cfg_curnum ")); Serial.print((uint16_t) myState.cfg_curnum); Serial.print(F(" cfg_type2save ")); Serial.print((uint16_t) myState.cfg_type2save); Serial.print(F(" myEfctLED ")); Serial.println((uint16_t) myEfctLED);
    }
    #endif // DEBUG_STATE_MACHINE
    doPattern(tmpEfctLED, tmpSpecial, 1); // doPattern figures out EEPROM configuration and configuration choice effects
  }
} // end RBG_startEffectLED()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_startEffectSound(tmpEfctSound, tmpSpecial) - start tmpEfctSound if it is valid
//
// tmpEfctSound is two fields: 0x00vv00nn where nn is sound and vv is volume
//       FIXME - volume not implemented yet
// If the row says mSPCL_EFCT_CONFIGURE and efctSound is mNONE and cfg_category is mCFG_CATEGORY_SOUND then we use the cfg_current to pick sound
// If the row says mSPCL_EFCT_CONFIGURE and efctSound is mNONE and cfg_category is not mCFG_CATEGORY_SOUND, then we use cfg_type to pick sound
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
void  RBG_startEffectSound(uint16_t tmpEfctSound, uint16_t tmpSpecial) {
  uint16_t idx;
  bool prevHI;
  uint16_t mySound = tmpEfctSound & mMASK_EFCT_SND_NUM;
  // uint16_t myVolume = (tmpEfctSound >> mSHIFT_EFCT_SND_VOL) & mMASK_EFCT_SND_VOL; // USE BELOW to convince MS VS 2019 we don't lose data
  uint16_t myVolume = ((tmpEfctSound & (mMASK_EFCT_SND_VOL << mSHIFT_EFCT_SND_VOL)) >> mSHIFT_EFCT_SND_VOL) & mMASK_EFCT_SND_VOL;

  if ((0 != (mSPCL_EFCT_CONFIGURE & tmpSpecial)) && (mCFG_CATEGORY_SOUND == myState.cfg_category) && (mNONE == tmpEfctSound)) { // handle configuration effects
    mySound = myState.cfg_curnum + myState.cfg_type;
    tmpEfctSound = (0xFF00 & tmpEfctSound) + mySound;
    myVolume = 25;
    Serial.print(F(" RBG_startEffectSound mSPCL_EFCT_CONFIGURE cfg_curnum ")); Serial.print((uint16_t) myState.cfg_curnum); Serial.print(F(" cfg_type2save ")); Serial.print((uint16_t) myState.cfg_type2save); Serial.print(F(" mySound ")); Serial.println((uint16_t) mySound);
  } else if ((0 != (mSPCL_EFCT_CONFIGURE & tmpSpecial)) && (mCFG_CATEGORY_SOUND != myState.cfg_category) && (mNONE == tmpEfctSound)) {
    if (mCFG_CATEGORY_LEDPTRN == myState.cfg_category2save) {
      mySound = mEFCT_UNIQ_CFG_LED2CHOOSE;
      tmpEfctSound = (0xFF00 & tmpEfctSound) + mySound;
      myVolume = 25;
    } else {
      mySound = mEFCT_UNIQ_NOT_IMPL;
      tmpEfctSound = (0xFF00 & tmpEfctSound) + mySound;
      myVolume = 25;
      Serial.print(F(" RBG_startEffectSound mSPCL_EFCT_CONFIGURE ERROR - unprogrammed cfg_category2save ")); Serial.println((uint16_t) myState.cfg_category2save); 
    }
  } // end if special configuration effects

  // myVolume is [0-31]. 0 means default; else subtract one to make [0-30]
  if (0 == myVolume) {
    myVolume = mDEFAULT_EFCT_SND_VOL;
  } else {
    myVolume -= 1;
  }
  if (mNONE != mySound) {
    // configurable sounds are zero mod 10; we get config from EEPROM
    if ((EFCT_IS_EEP(mySound)) && (mySound <= mEFCT_LAST_EEP_CONFIG)) {
      // configurable sound using EEPROM
      // mySound += EEPROM.read(EEPOFFSET(mySound)+EEPROM_START_SOUND_CONFIGS); old way; now using EEPROM_RAMcopy
      mySound += EEPROM_RAMcopy[EEPOFFSET(mySound)+EEPROM_START_SOUND_CONFIGS];
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
// NOTE: DPIN_BTN_TRIGGER handled in code in this routine: edge trigger, only goes 1 once on trigger press
// NOTE: DPIN_LOCK_LOAD handled in code in this routine
// NOTE: this is where we handle YX5200 active pin instability when interrupting previous play command
// NOTE: and... this is where we look for sound inactive before minimum motor/solenoid pulse time
//
uint16_t getButtonInput() {
  static uint8_t debugThisManyCalls = DEBUG_INPUTS*10;
  static uint8_t prevTrigstate = 0; // 0=trigger on LOW, 1=wait for HIGH
  uint16_t idx;
  uint16_t thePin;
  uint16_t theVal;
  uint16_t returnInpMask = 0;

  #if DEBUG_INPUTS
  Serial.print("getButtonInput() called: "); printAllMyInputs(); Serial.println(F(" that is all"));
  #endif // DEBUG_INPUTS
  // do lock/load separately in code
  theVal = digitalRead(DPIN_LOCK_LOAD);
  if (LOW == theVal) { // we are locked and loaded; sensitive to trigger and other events
    if (debugThisManyCalls > 0) { Serial.print(F(" getButtonInput ln ")); Serial.println((uint16_t) __LINE__); }
    returnInpMask |= mVINP_LOCK;
  } else { // we are not locked and loaded; abort everything else
    if (debugThisManyCalls > 0) { Serial.print(F(" getButtonInput ln ")); Serial.println((uint16_t) __LINE__); }
    returnInpMask |= mVINP_OPEN;
  }

  // do trigger edge separately in code
  theVal = digitalRead(DPIN_BTN_TRIGGER);
  if ((0 == prevTrigstate) && (LOW == theVal)) { // this is our edge
    if (debugThisManyCalls > 0) { Serial.print(F(" getButtonInput ln ")); Serial.println((uint16_t) __LINE__); }
    prevTrigstate = 1; // 0=trigger on LOW, 1=wait for HIGH
    returnInpMask |= mVINP_TRIG_EDGE;
  } else if (HIGH == theVal) {
    if (debugThisManyCalls > 0) { Serial.print(F(" getButtonInput ln ")); Serial.println((uint16_t) __LINE__); }
    prevTrigstate = 0; // 0=trigger on LOW, 1=wait for HIGH
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

  #if DEBUG_INPUTS
  Serial.print(F("    getButtonInput inputs: 0x")); Serial.print((uint16_t) returnInpMask, HEX); Serial.println(F(" that is all"));
  #endif // DEBUG_INPUTS
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
// eeprom_check_init(configToProc) - check if EEPROM has valid values; if not factory reset it
//    we use a very crude checksum approach
// configToProc - can be EEPROM_PROCESS_ALL_CONFIG or just one of the configs 0 <= config < NUM_EEPROM_CONFIGURATIONS
//
void eeprom_check_init(uint8_t configToProc) {
  // start reading from the first byte (address 0) of the EEPROM
  int address;
  uint8_t invChksumValue;
  uint8_t nowValue;
  uint8_t min_config, max_config;
  uint16_t thisConfigStart;

  // check validity, set up which configs we will process
  if ((EEPROM_PROCESS_ALL_CONFIG != configToProc) && (configToProc >= NUM_EEPROM_CONFIGURATIONS)) {
    // recall that configToProc is uint so there is no less than zero
    Serial.print(F("eeprom_check_init: ERROR bad configToProc ")); Serial.print(configToProc); Serial.print(F(": checking all EEPROM configs"));
    configToProc = EEPROM_PROCESS_ALL_CONFIG;
  }
  if (EEPROM_PROCESS_ALL_CONFIG != configToProc) {
    min_config = EEPROM_CONFIG_RUNNING;
    max_config = EEPROM_SAVED_LAST;
  } else {
    min_config = max_config = configToProc;
  }

  for (thisConfigStart = min_config*EEPROM_BYTES_PER_CONFIG; thisConfigStart <= max_config*EEPROM_BYTES_PER_CONFIG; thisConfigStart += EEPROM_BYTES_PER_CONFIG) {
    // read RBG non-checksum bytes from EEPROM and calculate checksum; compare with stored checksum
    invChksumValue = eeprom_calc_inverted_checksum(thisConfigStart/EEPROM_BYTES_PER_CONFIG);
    nowValue = EEPROM.read(EEPROM_INVERTED_CHKSM+thisConfigStart);
    // nowValue = invChksumValue+1; // FIXME force a checksum error
    // Serial.print(F("eeprom_check_init: stored inverted chksum 0x"); Serial.print(EEPROM_INVERTED_CHKSM,HEX); Serial.print(F(" value 0x")); Serial.print(nowValue,HEX); Serial.print(F(", calculated inverted chksum 0x")); Serial.println(((uint8_t) ~chksumValue),HEX);
    if (nowValue != invChksumValue) {
      // checksum does not match; factory reset our EEPROM configuration area
      Serial.print(F("eeprom_check_init: mismatch config num")); Serial.print(thisConfigStart/EEPROM_BYTES_PER_CONFIG);  Serial.print(F(" inverted chksum 0x")); Serial.print(invChksumValue,HEX); Serial.print(F(" does not match 0x")); Serial.print(nowValue,HEX); Serial.println(F("; INITIALIZING"));
      eeprom_factory_init(thisConfigStart/EEPROM_BYTES_PER_CONFIG);
    } // end if checksum does not match
  } // end for all configurations to process
} // end eeprom_check_init()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_calc_inverted_checksum(configToProc) - calculate the inverted checksum
//    we use a very crude checksum approach
// configToProc - must be just one of the configs 0 <= config < NUM_EEPROM_CONFIGURATIONS
//
uint8_t eeprom_calc_inverted_checksum(uint8_t configToProc) {
  int address;
  uint8_t chksumValue; // non-inverted checksum
  uint8_t byteValue;
  uint16_t thisConfigStart;

  // check validity, set up which configs we will process
  if ((EEPROM_PROCESS_ALL_CONFIG != configToProc) && (configToProc >= NUM_EEPROM_CONFIGURATIONS)) {
    // recall that configToProc is uint so there is no less than zero
    Serial.print(F("eeprom_check_init: ERROR bad configToProc ")); Serial.print(configToProc); Serial.print(F(": checking all EEPROM configs"));
    configToProc = NUM_EEPROM_CONFIGURATIONS-1;
  }
  thisConfigStart = configToProc*EEPROM_BYTES_PER_CONFIG;
  // read RBG non-checksum bytes from EEPROM and calculate checksum
  for (address = chksumValue = 0; address <= EEPROM_LAST_NON_CHKSM; address++) {
    byteValue = EEPROM.read(address+thisConfigStart);
    chksumValue += byteValue;
    // Serial.print(F("INIT EEP: address 0x")); Serial.print(address,HEX); Serial.print(F(" value 0x")); Serial.print(byteValue,HEX); Serial.print(F(" calc chksum 0x")); Serial.println(chksumValue,HEX);
  } // end caclulate checksum
  return((uint8_t) (~chksumValue));
} // end eeprom_calc_inverted_checksum()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_store_with_chksum(address, byteValue) - store byteValue at EEPROM address and update checksum
//    we use a very crude checksum approach
// address - where to store the byte, could be in any one of the configurations
// byteValue - byte value to store at address
//
void eeprom_store_with_chksum(int address, uint8_t byteValue) {
  uint8_t nowValue;
  uint8_t invChksumValue;
  uint8_t thisConfig = address/EEPROM_BYTES_PER_CONFIG;
  uint16_t thisConfigStart = thisConfig*EEPROM_BYTES_PER_CONFIG;

  nowValue = EEPROM.read(address);
  if (nowValue != byteValue) { // avoid EEPROM writes when possible
    EEPROM.write(address, byteValue);
  }
  invChksumValue = eeprom_calc_inverted_checksum(thisConfigStart/EEPROM_BYTES_PER_CONFIG);
  nowValue = EEPROM.read(EEPROM_INVERTED_CHKSM + thisConfigStart);
  if (nowValue != invChksumValue) { // avoid EEPROM writes when possible
    EEPROM.write(EEPROM_INVERTED_CHKSM + thisConfigStart, invChksumValue);
  }

  if (mNONE == myState.dynamicMode) {
    if (EEPROM_CONFIG_RUNNING == thisConfig) {
      copy_eeprom_to_ram_running_config(EEPROM_CONFIG_RUNNING);
    }
  } // end if not static mode; just wait till we cycle around to that EEPROM if static mode
} // end eeprom_store_with_chksum()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_factory_init(configToProc)
//   set requested EEPROM configurations to factory reset state
// configToProc - can be EEPROM_PROCESS_ALL_CONFIG or just one of the configs 0 <= config < NUM_EEPROM_CONFIGURATIONS
//
void eeprom_factory_init(uint8_t configToProc) {
  static uint8_t effectConfigs[EEPROM_BYTES_PER_CONFIG]; // don't want mysterious stack/heap collisions
  uint8_t min_config, max_config;
  uint16_t thisConfigStart;

  // check validity, set up which configs we will process
  if (EEPROM_PROCESS_ALL_CONFIG == configToProc) {
    min_config = EEPROM_CONFIG_RUNNING;
    max_config = EEPROM_SAVED_LAST;
  } else if (configToProc < NUM_EEPROM_CONFIGURATIONS) {
    min_config = max_config = configToProc;
  } else { 
    // recall that configToProc is uint so there is no less than zero
    Serial.print(F("eeprom_factory_init: ERROR bad configToProc ")); Serial.print(configToProc); Serial.print(F(": factory reset to all EEPROM configs"));
    configToProc = EEPROM_PROCESS_ALL_CONFIG;
    min_config = EEPROM_CONFIG_RUNNING;
    max_config = EEPROM_SAVED_LAST;
  }

  Serial.print(F("eeprom_factory_init: configToProc ")); Serial.print(configToProc); Serial.print(F(" min_config ")); Serial.print(min_config); Serial.print(F(" max_config ")); Serial.println(max_config);

  for (thisConfigStart = min_config; thisConfigStart <= max_config; thisConfigStart += 1) {
#if USE_PROGMEM
    memcpy_P(&effectConfigs, &factory_effect_configs[thisConfigStart*EEPROM_BYTES_PER_CONFIG], NUMOF(effectConfigs));
#else // not USE_PROGMEM
    memcpy(&effectConfigs, &factory_effect_configs[thisConfigStart*EEPROM_BYTES_PER_CONFIG], NUMOF(effectConfigs));
#endif // use, not USE_PROGMEM
    Serial.print(F("eeprom_factory_init: thisConfigStart ")); Serial.print(thisConfigStart); Serial.print(F(" effectConfigs[0] ")); Serial.print(effectConfigs[0]); Serial.print(F(" effectConfigs[1] ")); Serial.println(effectConfigs[1]);
    copy_ram_to_eeprom(effectConfigs, thisConfigStart);
  } // end for all configurations we should factory initialize
}; // end eeprom_factory_init(configToProc)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// copy_eeprom_to_ram(configToProc, ramArray)
//
// configToProc - just one of the configs 0 <= config < NUM_EEPROM_CONFIGURATIONS
//
void copy_eeprom_to_ram(uint8_t configToProc, uint8_t* ramArray) {
  uint16_t address;
  uint16_t thisConfigStart = configToProc*EEPROM_BYTES_PER_CONFIG;

  for (address = 0; address < EEPROM_BYTES_PER_CONFIG; address += 1) {
    ramArray[address] = EEPROM.read(address+thisConfigStart);
  } // end for all addresses in a single configuration
} // end copy_eeprom_to_ram(configToProc)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// copy_eeprom_to_ram_running_config(configToProc)
//
// configToProc - just one of the configs 0 <= config < NUM_EEPROM_CONFIGURATIONS
//
void copy_eeprom_to_ram_running_config(uint8_t configToProc) {
  copy_eeprom_to_ram(configToProc, EEPROM_RAMcopy);
} // end copy_eeprom_to_ram_running_config()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// copy_ram_to_eeprom(ramAddr, configToProc) -  copy from ramAddr to the configuration in configToProc
//
// ramAddr - address of uint8_t array of length EEPROM_BYTES_PER_CONFIG
// configToProc - must be just one of the configs 0 <= config < NUM_EEPROM_CONFIGURATIONS
// 
void copy_ram_to_eeprom(uint8_t *ramAddr, uint8_t configToProc) {
  uint8_t desiredValue, nowValue;
  uint16_t address;

  for (address = 0; address < EEPROM_LAST_NON_CHKSM; address++) { // one less than entire data area minus checksum
    nowValue = EEPROM.read(address+configToProc*EEPROM_BYTES_PER_CONFIG);
    desiredValue = ramAddr[address];
    Serial.print(F("copy_ram_to_eeprom: address+ ")); Serial.print(address+configToProc*EEPROM_BYTES_PER_CONFIG); Serial.print(F(" nowValue ")); Serial.print(nowValue); Serial.print(F(" desiredValue ")); Serial.println(desiredValue);
    // avoid EEPROM writes when possible
    if (desiredValue != nowValue) {
      EEPROM.write(address+configToProc*EEPROM_BYTES_PER_CONFIG, desiredValue);
    }
  } // end zero out our EEPROM area except last value
  nowValue = EEPROM.read(EEPROM_LAST_NON_CHKSM+configToProc*EEPROM_BYTES_PER_CONFIG);
  desiredValue = ramAddr[EEPROM_LAST_NON_CHKSM];
  Serial.print(F("copy_ram_to_eeprom: last address ")); Serial.print(EEPROM_LAST_NON_CHKSM+configToProc*EEPROM_BYTES_PER_CONFIG); Serial.print(F(" nowValue ")); Serial.print(nowValue); Serial.print(F(" desiredValue ")); Serial.println(desiredValue);
  eeprom_store_with_chksum(EEPROM_LAST_NON_CHKSM+configToProc*EEPROM_BYTES_PER_CONFIG, ramAddr[EEPROM_LAST_NON_CHKSM]); // store last value and checksum
} // end copy_ram_to_eeprom(ramAddr, configToProc)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// copy_eeprom_to_eeprom(fromConfigToProc, toConfigToProc) -  copy from one EEPROM config to another
//
// fromConfigToProc - must be just one of the configs 0 <= config < NUM_EEPROM_CONFIGURATIONS
// toConfigToProc   - must be just one of the configs 0 <= config < NUM_EEPROM_CONFIGURATIONS
// 
void copy_eeprom_to_eeprom(uint8_t fromConfigToProc, uint8_t toConfigToProc) {
  uint8_t desiredValue, nowValue;
  uint16_t address;

  for (address = 0; address < EEPROM_LAST_NON_CHKSM; address++) { // one less than entire data area minus checksum
    nowValue =      EEPROM.read(address + toConfigToProc*EEPROM_BYTES_PER_CONFIG);
    desiredValue  = EEPROM.read(address + fromConfigToProc*EEPROM_BYTES_PER_CONFIG);
    Serial.print(F("copy_eeprom_to_eeprom: fromConfigToProc ")); Serial.print(fromConfigToProc); Serial.print(F(" toConfigToProc ")); Serial.print(toConfigToProc); Serial.print(F(" address ")); Serial.print(address); Serial.print(F(" nowValue ")); Serial.print(nowValue); Serial.print(F(" desiredValue ")); Serial.println(desiredValue);
    // avoid EEPROM writes when possible
    if (desiredValue != nowValue) {
      EEPROM.write(address + toConfigToProc*EEPROM_BYTES_PER_CONFIG, desiredValue);
    }
  } // end zero out our EEPROM area except last value
  nowValue =      EEPROM.read(EEPROM_LAST_NON_CHKSM + toConfigToProc*EEPROM_BYTES_PER_CONFIG);
  desiredValue  = EEPROM.read(EEPROM_LAST_NON_CHKSM + fromConfigToProc*EEPROM_BYTES_PER_CONFIG);
  Serial.print(F("copy_eeprom_to_eeprom: last address ")); Serial.print(EEPROM_LAST_NON_CHKSM); Serial.print(F(" nowValue ")); Serial.print(nowValue); Serial.print(F(" desiredValue ")); Serial.println(desiredValue);
  eeprom_store_with_chksum(EEPROM_LAST_NON_CHKSM + toConfigToProc*EEPROM_BYTES_PER_CONFIG, desiredValue); // store last value and checksum

  if (mNONE == myState.dynamicMode) {
    if (EEPROM_CONFIG_RUNNING == toConfigToProc) {
      copy_eeprom_to_ram_running_config(EEPROM_CONFIG_RUNNING);
    } // end if need to copy to RAM Running Config
  } // end if not static mode; just wait till we cycle around to that EEPROM if static mode
} // end copy_eeprom_to_eeprom(ramAddr, configToProc)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// printAllMyState() - print (almost) ALL states
//
void printAllMyState() {
  Serial.println(F("DEBUG - myState:"));
  Serial.print(F("  - tableRow: ")); Serial.println((uint16_t) myState.tableRow);
  Serial.print(F("  - VinputRBG: 0x")); Serial.println((uint16_t) myState.VinputRBG, HEX);
  printExplainBits(myState.VinputRBG, decodeBits_VinputRBG, NUMOF(decodeBits_VinputRBG));
  Serial.print(F("  - timerNow: ")); Serial.println(myState.timerNow);
  Serial.print(F("  - timerPrevState: ")); Serial.println(myState.timerPrevState);
  Serial.print(F("  - timerPrevLEDstep: ")); Serial.println(myState.timerPrevLEDstep);
  Serial.print(F("  - timerForceSoundActv: ")); Serial.println(myState.timerForceSoundActv);
  Serial.print(F("  - timerMinForceSolenoidLow: ")); Serial.println(myState.timerMinForceSolenoidLow);
  Serial.print(F("  - timerMaxForceSolenoidLow: ")); Serial.println(myState.timerMaxForceSolenoidLow);
  Serial.print(F("  - ptrnDelayLEDstep: ")); Serial.println(myState.ptrnDelayLEDstep);
  Serial.print(F("  - cfg_curnum: ")); Serial.println(myState.cfg_curnum);
  Serial.print(F("  - cfg_maxnum: ")); Serial.println(myState.cfg_maxnum);
  Serial.print(F("  - cfg_category: ")); Serial.println(myState.cfg_category);
  Serial.print(F("  - cfg_category2save: ")); Serial.println(myState.cfg_category2save);
  Serial.print(F("  - cfg_type: ")); Serial.println(myState.cfg_type);
  Serial.print(F("  - cfg_type2save: ")); Serial.println(myState.cfg_type2save);
  Serial.print(F("  - cfg_addr: ")); Serial.println(myState.cfg_addr);
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
  printOneInput(DPIN_BTN_TRIGGER, " TRIGGER ");
  printOneInput(DPIN_BTN_YELLOW, " YELLOW ");
  printOneInput(DPIN_BTN_GREEN, " GREEN ");
  printOneInput(DPIN_BTN_RED, " RED ");
  printOneInput(DPIN_LOCK_LOAD, " LOAD ");
  printOneInput(DPIN_AUDIO_BUSY, " AUDIO_BUSY ");
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
