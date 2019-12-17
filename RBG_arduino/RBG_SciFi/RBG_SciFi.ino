// Author: Mark Olson 2019-11-03
//
// Rubber Band Gun - https://github.com/Mark-MDO47/RubberBandGun
// RBG - A high-tech imagining of the rubber band gun
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
// Here are the files I used, modified, and combined for the prototype sounds (other than GW170817-template.wav)
// | Tag        | File Name                                      | URL                             | Who |
// | ---        | ---                                            | ---                             | --- |
// | zero/1.0/  | 407052__sojan__power-charge.flac               | https://freesound.org/s/193610/ | crashoverride61088 |
// | zero/1.0/  |  397254__screamstudio__loading.wav             | https://freesound.org/s/397254/ | ScreamStudio |
// | zero/1.0/  | 145209__lensflare8642__shotgun-sounds.mp3      | https://freesound.org/s/145209/ | lensflare8642 |
// | by/3.0/    | 216096__richerlandtv__u-f-o.mp3                | https://freesound.org/s/216096/ | RICHERlandTV |
// | by/3.0/    | 88635__uair01__bicycle-picture-in-spectrum.wav | https://freesound.org/s/88635/  | uair01 |
// | by/3.0/    | 7967__cfork__boing-raw.aiff                    | https://freesound.org/s/7967/   | cfork |
// | by/3.0/    | 145209__lensflare8642__shotgun-sounds.mp3      | https://freesound.org/s/383205/ | SpiceProgram  |
// | by-nc/3.0/ | 179281__timbre__boingy-sweep.flac              | https://freesound.org/s/179281/ | Timbre |
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

#include "RBG_SciFi_LEDs.h"                  // LED structural and pattern definitions
#include "RBG_SciFi_StatesAndInputs.h"       // state tables and input definitions

#define SERIALDEBUG 1                        // serial debugging
#define REAL_BUTTONS 1                       // use actual buttons


SoftwareSerial mySoftwareSerial(DPIN_SWSRL_RX, DPIN_SWSRL_TX); // to talk to YX5200 audio player
DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player
void DFsetup();                                                // how to initialize myDFPlayer

// #define DFPRINTDETAIL (1&SERIALDEBUG)     // if need detailed status from myDFPlayer
#define DFPRINTDETAIL 0                      // will not print detailed status from myDFPlayer
#if DFPRINTDETAIL // routine to do detailed debugging
void DFprintDetail(uint8_t type, int value); // definition of call
#else  // no DFPRINTDETAIL
#define DFprintDetail(type, value) // nothing at all
#endif // #if DFPRINTDETAIL


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
  pinMode(DPIN_AUDIO_BUSY,  INPUT_PULLUP); // tells when audio stops
  pinMode(DPIN_LOCK_LOAD,   INPUT_PULLUP); // tells if barrel is locked and loaded
  // and the output pin
  pinMode(DPIN_SOLENOID,   OUTPUT);        // fires the rubber band

  // make sure solenoid is not drawing power
  digitalWrite(DPIN_SOLENOID, LOW);

  // initialize the DFPlayer audio player
  DFsetup();

  // initialize the FastLED library for our setup
  FastLED.addLeds<NEOPIXEL,DPIN_FASTLED>(led_display, NUM_LEDS_PER_DISK);
  FastLED.setBrightness(BRIGHTMAX); // we will do our own power management

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
  
  gHue += 3; // rotating "base color" used by Demo Reel 100 patterns

  myState.timerNow = millis();
  if (myState.VinputRBG&mVINP_LOCK) {
    //Serial.print(F(" RBG_startRow ln ")); Serial.println((uint16_t) __LINE__); Serial.print(F(" myState.VinputRBG 0x")); Serial.print(myState.VinputRBG, HEX);
    myState.VinputRBG |= mVINP_PREVLOCK; // set the bit
    //Serial.print(F(" AFTER myState.VinputRBG 0x")); Serial.println(myState.VinputRBG, HEX);
  } else {
    //Serial.print(F(" RBG_startRow ln ")); Serial.println((uint16_t) __LINE__); Serial.print(F(" myState.VinputRBG 0x")); Serial.print(myState.VinputRBG, HEX);
    myState.VinputRBG &= ((uint16_t) ~(mVINP_PREVLOCK)); // clear the bit
    //Serial.print(F(" AFTER myState.VinputRBG 0x")); Serial.println(myState.VinputRBG, HEX);
  }

  nowVinputRBG = getButtonInput();
  nowVinputRBG = processStateTable(nowVinputRBG);

  checkDataGuard();
  // doPattern(); // FIXME TBS WILL DO LEDs LATER
  checkDataGuard();
  FastLED.show();

  if (myState.pattern < MIN_FASTLED_PATTERN) { // Mark's patterns
    doDwell(myState.ptrn_delay, 1);
  } else { // FastLED patterns
    doDwell(myState.ptrn_delay_fastled, 1);
  }

  myState.VinputRBG = nowVinputRBG;
  myState.timerPrev = myState.timerNow;
}  // end loop()

// ******************************** STATE TABLE UTILITIES ********************************

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// processStateTable(...) - called from main loop to do state table processing
//     Use our state table and state and inputs to calculate next state
//     Determine if we need to change LED pattern and/or sound
//     If needed, release the rubber band and set timer to stop the solenoid current later
//
uint16_t processStateTable(uint16_t tmpVinputRBG) {
  static uint8_t countBadStatePrint = 6;
  static uint8_t countGoodStatePrint = 6;
  static uint8_t countGoodInputPrint = 6;
  uint16_t myGoTo = 0;
  uint16_t foundInput = 0; // return from RBG_waitForInput


  if (0 == myState.tableRowInProcFlags) {
    myState.tableRowInProcFlags = RBG_startRow(); // just do what the row says
    if (countGoodStatePrint > 0) {
      Serial.println(F("DEBUG - after RBG_startRow() call"));
      printAllMyState(); Serial.print(F("DEBUG processStateTable() - tmpVinputRBG 0x")); Serial.println(tmpVinputRBG, HEX);
      countGoodStatePrint -= 1;
    }
  } else if (mINPROCFLG_WAITFORSOUND == myState.tableRowInProcFlags) {
    if ((0 == (tmpVinputRBG&mVINP_SOUNDACTV)) &&
        (myStateTable[myState.tableRow].gotoWithoutInput != mNONE)) {
      // sound completed and we have a place to go
      myState.tableRowInProcFlags = 0; // can only have one WAITFOR or the other
      myGoTo = myStateTable[myState.tableRow].gotoWithoutInput;
      if ((0 == (mSPCL_EFCT_CONTINUOUS & myStateTable[myState.tableRow].SPECIAL)) && (mNONE != myGoTo)) {
        myState.tableRow = myGoTo; // gotoWithoutInput
        if (countGoodStatePrint > 0) {
          Serial.print(F("DEBUG processStateTable() - after mINPROCFLG_WAITFORSOUND - gotoWithoutInput row "));
          Serial.println(myGoTo);
        }
      } else {
        if (countGoodStatePrint > 0) {
          myStateTable[myState.tableRow].SPECIAL |= RBG_startEffectSound(myStateTable[myState.tableRow].efctSound);
          Serial.print(F("DEBUG processStateTable() - after mINPROCFLG_WAITFORSOUND - restart sound "));
          Serial.println(myGoTo);
        }
      }
      if (countGoodStatePrint > 0) {
        Serial.println(F("DEBUG processStateTable() - after mINPROCFLG_WAITFORSOUND"));
        printAllMyState(); Serial.print(F("DEBUG processStateTable() - tmpVinputRBG 0x")); Serial.println(tmpVinputRBG, HEX);
        countGoodStatePrint -= 1;
      }
    } // else we the sound did not end with a place to go
  } else if (mINPROCFLG_WAITFORINPUT == myState.tableRowInProcFlags) {
    // we need to check until we hit the mBLOCKEND
    foundInput = RBG_waitForInput(tmpVinputRBG); // wait for user input, trigger and maybe other buttons
    if (mNONE != foundInput) {
      myState.tableRowInProcFlags = 0; // can only have one WAITFOR or the other
      myState.tableRow = foundInput;
      if (countGoodInputPrint > 0) {
        Serial.println(F("DEBUG processStateTable() - after RBG_waitForInput() call"));
        printAllMyState(); Serial.print(F("DEBUG - tmpVinputRBG 0x")); Serial.print(tmpVinputRBG, HEX); Serial.print(F(" foundInput 0x")); Serial.println(foundInput, HEX);
        countGoodInputPrint -= 1;
      }
    } // end if found input
  } else if (mINPROCFLG_SPCL_IN_PROC == myState.tableRowInProcFlags) {
    // special processing happening now; just call that until this flag clears
    tmpVinputRBG = RBG_specialProcessing(tmpVinputRBG, mINPROCFLG_SPCL_IN_PROC);
  } else {
    if (countBadStatePrint > 0) {
      Serial.println(F("ERROR processStateTable() - unknown tableRowInProcFlags value"));
      printAllMyState(); Serial.print(F("DEBUG - tmpVinputRBG 0x")); Serial.println(tmpVinputRBG, HEX);
      myState.tableRowInProcFlags = 0;
      countBadStatePrint -= 1;
    } else {
      myState.tableRowInProcFlags = 0;
    }
  }
  return(tmpVinputRBG);
} // end processStateTable()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_startRow() - start processing a row in myStateTable
//    myState.tableRowInProcFlags should be zero to call this
// returns a tableRowInProcFlags bitmask
uint16_t RBG_startRow() {
  static uint8_t debugThisManyCalls = 10;
  RBGStateTable * thisRowPtr = &myStateTable[myState.tableRow];
  uint16_t thisSound = 0;
  uint16_t thisLED = 0;
  uint16_t thisReturn = 0;
  static uint16_t prev_row = 0;
  static uint16_t prev_tableRowInProcFlags = 0;

  if ((prev_row != myState.tableRow) || (prev_tableRowInProcFlags != myState.tableRowInProcFlags)) {
    debugThisManyCalls = 10;
    if (debugThisManyCalls > 0) { Serial.print(F(" RBG_startRow ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" from row ")); Serial.print((uint16_t) prev_row); Serial.print(F(" to row ")); Serial.println((uint16_t) myState.tableRow); }
    prev_row = myState.tableRow;
    prev_tableRowInProcFlags = myState.tableRowInProcFlags;
  } // end if more debugging is useful
  if (mNONE == thisRowPtr->gotoOnInput) {
    // not waiting for input
    if (debugThisManyCalls > 0) { Serial.print(F(" RBG_startRow ln ")); Serial.println((uint16_t) __LINE__); }
    thisSound = thisRowPtr->efctSound;
    if ((mNONE == thisRowPtr->SPECIAL) || (0 != (thisRowPtr->SPECIAL & mSPCL_EFCT_CONTINUOUS))) { // not a SPECIAL function row or CONTINOUS sound
      if (debugThisManyCalls > 0) { Serial.print(F(" RBG_startRow ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" play sound ")); Serial.println((uint16_t) thisSound); }
      thisReturn |= RBG_startEffectSound((uint16_t) (thisSound));
      thisLED = thisRowPtr->efctLED;
      if (mNONE != thisLED) {
        if (debugThisManyCalls > 0) { Serial.print(F(" RBG_startRow ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" LED ptrn ")); Serial.println((uint16_t) thisLED); }
        if (debugThisManyCalls > 0) { Serial.println(F(" RBG_startRow FIXME LEDS to efctLED")); }
        myState.timerLed = millis() + deltaMsLED;
      }  // end if should switch to other LED pattern
      // FIXME MAYBE NEED MORE CODE FOR SPECIALS - maybe don't need it
    }
    if (debugThisManyCalls > 0) { Serial.print(F(" RBG_startRow ln ")); Serial.println((uint16_t) __LINE__); }
    if (mNONE == thisReturn) { // if we still don't have anything to do, just jump
      if (debugThisManyCalls > 0) { Serial.print(F(" RBG_startRow ln ")); Serial.println((uint16_t) __LINE__); }
      myState.tableRow = thisRowPtr->gotoWithoutInput; // we will go next time.
      // thisReturn is already mNONE
    } // end if do the jump next time
  } else { // there is input to wait for, perhaps a block
    if (debugThisManyCalls > 0) { Serial.print(F(" RBG_startRow ln ")); Serial.println((uint16_t) __LINE__); }
    thisReturn = mINPROCFLG_WAITFORINPUT; // start the new state, RBG_waitForInput() will handle it
  } // end if there is input to wait for
  if (debugThisManyCalls > 0) { Serial.print(F(" RBG_startRow ln ")); Serial.println((uint16_t) __LINE__); }
  if (debugThisManyCalls > 0) { debugThisManyCalls -= 1; }
  return thisReturn;
} // end RBG_startRow()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_waitForInput(tmpVinputRBG) - wait until desired input happens
//   returns mNONE if did not happen, idx to row that matched if it did
uint16_t RBG_waitForInput(uint16_t tmpVinputRBG) {
  static uint8_t debugThisManyCalls = 8;
  uint16_t thisReturn = mNONE; // assume no input found
  RBGStateTable * thisRowPtr = &myStateTable[myState.tableRow];

  // restart the debug prints when something interesting happens
  if (tmpVinputRBG != (myState.VinputRBG & ((uint16_t) (~mVINP_PREVLOCK)))) { debugThisManyCalls = 8; }

  // this is what a debug print looks like
  if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput entry ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" tmpVinputRBG 0x")); Serial.println(tmpVinputRBG, HEX); }

  // we need to check until we hit the mBLOCKEND
  for (uint16_t idx = myState.tableRow; (idx < NUMOF(myStateTable)) && (mNONE == thisReturn); idx++) {
    // see if we match input condition for this row
    if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.print(idx); Serial.print(F(" thisRowPtr->inputRBG 0x")); Serial.println(thisRowPtr->inputRBG, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    thisRowPtr->inputRBG&mINP_TRIG 0x")); Serial.print(thisRowPtr->inputRBG&mINP_TRIG, HEX); Serial.print(F(" tmpVinputRBG&mVINP_TRIG 0x")); Serial.println(tmpVinputRBG&mVINP_TRIG, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    myState.VinputRBG&mVINP_PREVLOCK 0x")); Serial.println(myState.VinputRBG&mVINP_PREVLOCK, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    thisRowPtr->inputRBG&mINP_OPEN 0x")); Serial.print(thisRowPtr->inputRBG&mINP_OPEN, HEX); Serial.print(F(" tmpVinputRBG&mVINP_OPEN 0x")); Serial.println(tmpVinputRBG&mVINP_OPEN, HEX); }
    if (debugThisManyCalls > 0) { Serial.print(F("    thisRowPtr->inputRBG&mINP_LOCK 0x")); Serial.print(thisRowPtr->inputRBG&mINP_LOCK, HEX); Serial.print(F(" tmpVinputRBG&mVINP_LOCK 0x")); Serial.println(tmpVinputRBG&mVINP_LOCK, HEX); }
    // if (debugThisManyCalls > 0) { Serial.print(F("    0 != (thisRowPtr->inputRBG&mINP_LOCK) 0x")); Serial.print(0 != (thisRowPtr->inputRBG&mINP_LOCK), HEX); Serial.print(F(" 0 != (tmpVinputRBG&mVINP_LOCK) 0x")); Serial.println(0 != (tmpVinputRBG&mVINP_LOCK), HEX); }
    // if (debugThisManyCalls > 0) { Serial.print(F("    (0 != (thisRowPtr->inputRBG&mINP_LOCK)) && (0 != (tmpVinputRBG&mVINP_LOCK)) 0x")); Serial.println((0 != (thisRowPtr->inputRBG&mINP_LOCK)) && (0 != (tmpVinputRBG&mVINP_LOCK)), HEX); }
    if ((0 != (thisRowPtr->inputRBG&mINP_TRIG)) && (0 != (tmpVinputRBG&mVINP_TRIG))) {
      // several cases for trigger
      if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.println(idx); }
      if (0 != (thisRowPtr->inputRBG&mINP_BANY)) {
        if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.println(idx); }
        thisReturn = thisRowPtr->gotoOnInput;
      } else if ((0 != (thisRowPtr->inputRBG&mINP_BNONE)) &&
                 (0 == (tmpVinputRBG & (mVINP_B01|mVINP_B02|mVINP_B04)))) {
        if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.println(idx); }
        thisReturn = thisRowPtr->gotoOnInput;
      }
    } else if ((0 != (thisRowPtr->inputRBG&mINP_OPEN)) && (0 != (tmpVinputRBG&mVINP_OPEN)) && (0 != (myState.VinputRBG&mVINP_PREVLOCK))) {
      /* if (debugThisManyCalls > 0) */ { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.println(idx); }
      thisReturn = thisRowPtr->gotoOnInput;
      break;
    } else if ((0 != (thisRowPtr->inputRBG&mINP_LOCK)) && (0 != (tmpVinputRBG&mVINP_LOCK)) && (0 == (myState.VinputRBG&mVINP_PREVLOCK))) {
      /* if (debugThisManyCalls > 0) */ { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" idx ")); Serial.println(idx); }
      thisReturn = thisRowPtr->gotoOnInput; // found an input we were waiting for
      break;
    }

    if (0 != (thisRowPtr->inputRBG&mBLOCKEND)) {
      // this is a normal way to end - found the mBLOCKEND but did not find input
      if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.println((uint16_t) __LINE__); }
      // now we just check if we are doing a special effect like mSPCL_EFCT_CONTINUOUS
      thisRowPtr = &myStateTable[myState.tableRow]; // set this back to start of block
      if ((0 != (mSPCL_EFCT_CONTINUOUS & thisRowPtr->SPECIAL)) && (0 == (mVINP_SOUNDACTV & tmpVinputRBG))) {
        // want continuous sound and sound is not active so restart it
        Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" play sound ")); Serial.println((uint16_t) thisRowPtr->efctSound);
        RBG_startEffectSound((uint16_t) (thisRowPtr->efctSound));
      }
      break;
    }
    thisRowPtr += 1;
  } // end while searching for mBLOCKEND
    
  if (debugThisManyCalls > 0) { Serial.print(F(" RBG_waitForInput ln ")); Serial.print((uint16_t) __LINE__); Serial.print(F(" thisReturn ")); Serial.println(thisReturn); }
  if (/* FIXME debugThisManyCalls */ 0 > 0) { debugThisManyCalls -= 1; }
  return thisReturn; // input did not happen
} // end RBG_waitForInput()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcessing(int16_t tmpVinputRBG, uint16_t tmpFlags)
//   do the SPECIAL processing - mostly the solenoid stuff
//
uint16_t RBG_specialProcessing(uint16_t tmpVinputRBG, uint16_t tmpFlags) {
  uint16_t myVinputRBG = tmpVinputRBG;
  RBGStateTable * thisRowPtr = &myStateTable[myState.tableRow];

  if (0 == tmpFlags) { // first time on this row
    switch ((thisRowPtr->SPECIAL & (mSPCL_HANDLER-1))) {
      case mSPCL_HANDLER_SHOOT:
        RBG_specialProcShoot();
        break;
      case mSPCL_HANDLER_SOLENOID:
        RBG_specialProcSolenoid();
        break;
      default:
        Serial.print(F(" RBG_specialProcessing ln ")); Serial.print((uint16_t) __LINE__);
        break;
    } // end switch on type of special
  } else { // read tmpFlags and state to see what is going on
  }
  return(myVinputRBG);
} // end RBG_specialProcessing(uint16_t tmpVinputRBG, uint16_t tmpFlags)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcShoot() - do the solenoid for shooting
//
void RBG_specialProcShoot() {
  uint16_t nextRow = myStateTable[myState.tableRow].gotoWithoutInput;
  digitalWrite(DPIN_SOLENOID, HIGH);
  delay(200); // let's try it the easy way
  if (mNONE == nextRow) { nextRow = mROW_POWERON; digitalWrite(DPIN_SOLENOID, LOW); Serial.print(F(" RBG_specialProcShoot ln ")); Serial.print((uint16_t) __LINE__); Serial.println(F(" gotoWithoutInput is mNONE; going to mROW_POWERON")); }
  myState.tableRow = nextRow;
} // end RBG_specialProcShoot()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_specialProcSolenoid() - release the solenoid after shooting
//
void RBG_specialProcSolenoid() {
  uint16_t nextRow = myStateTable[myState.tableRow].gotoWithoutInput;
  digitalWrite(DPIN_SOLENOID, LOW);
  if (mNONE == nextRow) { nextRow = mROW_POWERON; Serial.print(F(" RBG_specialProcSolenoid ln ")); Serial.print((uint16_t) __LINE__); Serial.println(F(" gotoWithoutInput is mNONE; going to mROW_POWERON")); }
  myState.tableRow = nextRow;
} // end RBG_specialProcSolenoid()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RBG_startEffectSound(tmpEfctSound) - start tmpEfctSound if it is valid
// returns a tableRowInProcFlags bitmask - zero or mINPROCFLG_WAITFORSOUND
//   caller will determine if this flag should go into tableRowInProcFlags
uint16_t  RBG_startEffectSound(uint16_t tmpEfctSound) {
  uint16_t thisReturn = 0;

  if (mNONE != tmpEfctSound) {
    Serial.print(F(" RBG_startEffectSound ln ")); Serial.print((uint16_t) __LINE__);  Serial.print(F(" EFCT num ")); Serial.println(tmpEfctSound); 
    if (EFCT_IS_EEP(tmpEfctSound)) {
      // configurable sound using EEPROM
      myDFPlayer.playMp3Folder(tmpEfctSound + EEPROM.read(EEPOFFSET(tmpEfctSound))); //play specific mp3 in SD:/MP3/####.mp3; File Name(0~9999)
      // myDFPlayer.enableLoop(); this does not actually make the playMp3Folder call loop
    } else { // unique sound - includes any mEFCT_ stuff
      myDFPlayer.playMp3Folder(tmpEfctSound); //play specific mp3 in SD:/MP3/####.mp3; File Name(0~9999)
    }
    thisReturn |= mINPROCFLG_WAITFORSOUND;
  } // end if should start a sound

  return(thisReturn); // this is a flag that could go into tableRowInProcFlags, depending on context of caller
} // end RBG_startEffectSound

// ******************************** BUTTON AND TIMING UTILITIES ********************************


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// doDwell(int16_t dwell, uint8_t must_be_diff_pattern) - dwell or break out if button press
//   returns TRUE if got a change in inputs
//   else returns false
//
// FIXME TBD MAYBE DO NOT NEED - LEFT IT OUT keeps track of button_time
//
// FIXME - needs adaptation for Rubber Band Gun - handle LED pattern, sound and solenoid
//
#define SMALL_DWELL 20
int16_t doDwell(int16_t dwell, uint8_t must_be_diff_pattern) {
  int16_t numloops = dwell / SMALL_DWELL;
  int16_t i;
  static uint8_t firstTime = 1;

  if (firstTime) {
    Serial.println(F("FIXME doDwell(...) - may need improvement for Rubber Band Gun for solenoid timer"));
    firstTime = 0;
  }

  for (i = 0; i < numloops; i++) {
    nowVinputRBG = getButtonInput();
    if ((0 != must_be_diff_pattern) && (nowVinputRBG == myState.pattern)) {
      delay(SMALL_DWELL);
    } else {
      return(nowVinputRBG);
    }
    // button_time += SMALL_DWELL; // FIXME TBD MAYBE DO NOT NEED - LEFT IT OUT
  } // end for most of the delay
  if ((dwell % SMALL_DWELL) != 0) {
    nowVinputRBG = getButtonInput();
    if ((0 != must_be_diff_pattern) && (nowVinputRBG == myState.pattern)) {
      delay(dwell % SMALL_DWELL);
    } else {
      return(nowVinputRBG);
    }
    // button_time += (dwell % SMALL_DWELL); // FIXME TBD MAYBE DO NOT NEED - LEFT IT OUT
  } // end handle the remainder
  return(0); // never saw input change
} // end doDwell()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// getButtonInput() - get next button or other input, true inputs or debugging
//
// checkButtons() - returns mVINP_ mask for buttons to process
// 
// All the buttons are 0 when pressed
// The lock/load input is 0 when connected and 1 when not lock/load
// The sound complete is 0 when sound is complete
//
// NOTE: DPIN_LOCK_LOAD handled in code
// lock/load has priority - if not lock/load then no button or sound input matters
// when lock/load:
//    trigger means collect the state of the buttons
//    sound input is always sensed. If sound is playing and it finishes then we set input.
//
uint16_t getButtonInput() {
  static uint8_t debugThisManyCalls = 10;
  uint16_t idx;
  uint16_t thePin;
  uint16_t theVal;
  uint16_t returnInpMask = 0;

  if (debugThisManyCalls > 0) { Serial.println("checkButtons() called:"); printAllMyInputs(); }
  // do lock/load separately in code
  theVal = digitalRead(DPIN_LOCK_LOAD);
  if (LOW == theVal) { // we are locked and loaded; sensitive to trigger and other events
    if (debugThisManyCalls > 0) { Serial.print(F(" checkButtons ln ")); Serial.println((uint16_t) __LINE__); }
    returnInpMask = mVINP_LOCK;
    // set/clear the input bits for the standard inputs
    for (idx = 0; idx < NUMOF(myPinsToVals); idx++) {
      if (LOW == digitalRead(myPinsToVals[idx].pin)) {
        returnInpMask |= ((uint16_t) myPinsToVals[idx].val); // less overkill but still solves if .val is not uintx_t
      } else {
        returnInpMask &= ~((uint16_t) myPinsToVals[idx].val); // overkill but can solve lots of issues
      }
    } // end for entries in myPinsToVals[]
  } else { // we are not locked and loaded; abort everything else
    if (debugThisManyCalls > 0) { Serial.print(F(" checkButtons ln ")); Serial.println((uint16_t) __LINE__); }
    returnInpMask = mVINP_OPEN;
  }

  if (debugThisManyCalls > 0) { Serial.print(F(" checkButtons found inputs: 0x")); Serial.println((uint16_t) returnInpMask, HEX); }
  if (debugThisManyCalls > 0) { debugThisManyCalls -= 1; }

  return(returnInpMask);
} // end checkButtons()

// ******************************** INITIALIZATION UTILITIES ********************************

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void DFsetup() {
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  // Use softwareSerial to communicate with mp3 player
    Serial.println(F("Unable to begin DFPlayer:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(1);
    }
  }
  myDFPlayer.EQ(DFPLAYER_EQ_BASS); // our speaker is quite small
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // device is SD card
  myDFPlayer.volume(25);  // Set volume value. From 0 to 30 - FIXME 25 is good
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
void printAllMyState() {
  Serial.println(F("DEBUG - myState:"));
  Serial.print(F("  - tableRow: "));
  Serial.println((uint16_t) myState.tableRow);
  Serial.print(F("  - tableRowInProcFlags: 0x"));
  Serial.println((uint16_t) myState.tableRowInProcFlags, HEX);
  Serial.print(F("  - VinputRBG: 0x"));
  Serial.println((uint16_t) myState.VinputRBG, HEX);
} // end printAllMyState()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// printAllMyInputs() - interpret the input bits
void printAllMyInputs() {
  Serial.println(F("DEBUG - printAllMyInputs:"));
  printOneInput(DPIN_BTN_TRIGGER, "DPIN_BTN_TRIGGER ");
  printOneInput(DPIN_BTN_YELLOW, "DPIN_BTN_YELLOW   ");
  printOneInput(DPIN_BTN_GREEN, "DPIN_BTN_GREEN    ");
  printOneInput(DPIN_BTN_GREEN, "DPIN_BTN_GREEN    ");
  printOneInput(DPIN_BTN_BLACK, "DPIN_BTN_BLACK    ");
  printOneInput(DPIN_LOCK_LOAD, "DPIN_LOCK_LOAD    ");
  printOneInput(DPIN_AUDIO_BUSY, "DPIN_AUDIO_BUSY  ");
} // end printAllMyInputs()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// printOneInput() - interpret one input bit
//   dtext will line up the LOW and HIGH
void printOneInput(uint8_t dpin, const char * dtext) {
  Serial.print(dtext);
  if (LOW == digitalRead(dpin)) {
    Serial.println("LOW");
  } else {
    Serial.println("HIGH");
  }
} // end printOneInput()
