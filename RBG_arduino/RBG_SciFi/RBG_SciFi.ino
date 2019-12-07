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

#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port
#include <EEPROM.h>                          // to store configuration info

#include "FastLED.h"                         // to manipulate WS2812b 5050 RGB LED Rings
#include "DFRobotDFPlayerMini.h"             // to communicate with the YX5200 audio player

#define NUMOF(x) (sizeof(x) / sizeof(*x))

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
CRGB dark_color_palette[NUM_ARDUINOS]  = { CRGB::DarkGreen, CRGB::Red,    CRGB::Blue, CRGB::DarkOrange };
CRGB light_color_palette[NUM_ARDUINOS] = { CRGB::LimeGreen, CRGB::Yellow, CRGB::Aqua, CRGB::Gold };
#endif // FASTLED_FIRE_PATTERN
static uint16_t nowVinputRBG; // latest button inputs, to compare with previous in myState


// ******************************** SETUP ********************************
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

// ******************************** LOOP ********************************
//  loop()
//     Get the inputs - buttons, barrel, sound ended
//     Use our state table and state and inputs to calculate next state
//     Determine if we need to change LED pattern and/or sound
//     If needed, release the rubber band and set timer to stop the solenoid current later
//
void loop() {
  static uint8_t countBadStatePrint = 6;
  static uint8_t countGoodStatePrint = 6;
  uint16_t foundInput = 0; // return from RBG_waitForInput

  // put your main code here, to run repeatedly:
  
  gHue += 3; // rotating "base color" used by Demo Reel 100 patterns

  myState.timerNow = millis();
  nowVinputRBG = getButtonInput();
  
  if (0 == myState.tableRowInProcFlags) {
    myState.tableRowInProcFlags = RBG_startRow(); // just do what the row says
    if (countGoodStatePrint > 0) {
      Serial.println(F("DEBUG - after RBG_startRow() call"));
      printAllMyState(); Serial.print(F("DEBUG - nowVinputRBG 0x")); Serial.println(nowVinputRBG, HEX);
      countGoodStatePrint -= 1;
    }
  } else if (mINPROCFLG_WAITFORSOUND == myState.tableRowInProcFlags) {
    if ((0 == (nowVinputRBG&mVINP_SOUNDACTV)) &&
        (myStateTable[myState.tableRow].gotoWithoutInput != mNONE)) {
      // sound completed and we have a place to go
      myState.tableRowInProcFlags = 0; // can only have one WAITFOR or the other
      myState.tableRow = myStateTable[myState.tableRow].gotoWithoutInput;
      if (countGoodStatePrint > 0) {
        Serial.println(F("DEBUG - after mINPROCFLG_WAITFORSOUND"));
        printAllMyState(); Serial.print(F("DEBUG - nowVinputRBG 0x")); Serial.println(nowVinputRBG, HEX);
        countGoodStatePrint -= 1;
      }
    } // else we the sound did not end with a place to go
  } else if (mINPROCFLG_WAITFORINPUT == myState.tableRowInProcFlags) {
    // we need to check until we hit the mBLOCKEND
    foundInput = RBG_waitForInput(nowVinputRBG); // wait for user input, trigger and maybe other buttons
    if (countGoodStatePrint > 0) {
      Serial.println(F("DEBUG - after RBG_waitForInput() call"));
      printAllMyState(); Serial.print(F("DEBUG - nowVinputRBG 0x")); Serial.println(nowVinputRBG, HEX);
      countGoodStatePrint -= 1;
    }
  } else {
    if (countBadStatePrint > 0) {
      Serial.println(F("ERROR - unknown tableRowInProcFlags value"));
      printAllMyState(); Serial.print(F("DEBUG - nowVinputRBG 0x")); Serial.println(nowVinputRBG, HEX);
      myState.tableRowInProcFlags = 0;
      countBadStatePrint -= 1;
    } else {
      myState.tableRowInProcFlags = 0;
    }
  } // end process state table

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

// RBG_startRow() - start processing a row in myStateTable
//    myState.tableRowInProcFlags should be zero to call this
uint8_t RBG_startRow() {
  static uint8_t debugThisManyCalls = 10;
  RBGStateTable * thisRowPtr = &myStateTable[myState.tableRow];
  uint8_t thisSound = 0;
  uint8_t thisLED = 0;
  uint8_t thisReturn = 0;
  if (mNONE == thisRowPtr->gotoOnInput) {
    // not waiting for input
    if (debugThisManyCalls > 0) { Serial.print(" RBG_startRow "); Serial.println((uint16_t) __LINE__); }
    thisSound = thisRowPtr->efctSound;
    if (mNONE != thisSound) {
      if (debugThisManyCalls > 0) { Serial.print(" RBG_startRow "); Serial.println((uint16_t) __LINE__); }
      if (0 != myState.tableRow) {
         myDFPlayer.playMp3Folder(thisSound+mEFCT_CONFIGURE); //play specific mp3 in SD:/MP3/####.mp3; File Name(0~9999)
      } else {
         myDFPlayer.playMp3Folder(thisSound+mEFCT_INIT_PWR_UP); //play specific mp3 in SD:/MP3/####.mp3; File Name(0~9999)
      }
      thisReturn |= mINPROCFLG_WAITFORSOUND;
    } // end if should start a sound and wait for it
    thisLED = thisRowPtr->efctLED;
    if (debugThisManyCalls > 0) { Serial.print(" RBG_startRow "); Serial.println((uint16_t) __LINE__); }
    if (mNONE != thisLED) {
      if (debugThisManyCalls > 0) { Serial.print(" RBG_startRow "); Serial.println((uint16_t) __LINE__); }
      // FIXME LEDS to efctLED
      myState.timerLed = millis() + deltaMsLED;
    }  // end if should switch to other LED pattern
    if (debugThisManyCalls > 0) { Serial.print(" RBG_startRow "); Serial.println((uint16_t) __LINE__); }
    if (mNONE == thisReturn) { // if we still don't have anything to do, just jump
      if (debugThisManyCalls > 0) { Serial.print(" RBG_startRow "); Serial.println((uint16_t) __LINE__); }
      myState.tableRow = thisRowPtr->gotoWithoutInput; // we will go next time.
      // thisReturn is already mNONE
    } // end if do the jump next time
  } else { // there is input to wait for, perhaps a block
    if (debugThisManyCalls > 0) { Serial.print(" RBG_startRow "); Serial.println((uint16_t) __LINE__); }
    thisReturn = mINPROCFLG_WAITFORINPUT; // start the new state, RBG_waitForInput() will handle it
  } // end if there is input to wait for
  if (debugThisManyCalls > 0) { Serial.print(" RBG_startRow "); Serial.println((uint16_t) __LINE__); }
  if (debugThisManyCalls > 0) { debugThisManyCalls -= 1; }
  return thisReturn;
} // end RBG_startRow()

// RBG_waitForInput(nowVinputRBG) - wait until desired input happens
//   returns mNONE if did not happen, idx to row that matched if it did
uint8_t RBG_waitForInput(uint16_t nowVinputRBG) {
  uint8_t thisReturn = mNONE; // assume no input found
  static uint8_t debugThisManyCalls = 3;
  RBGStateTable * thisRowPtr = &myStateTable[myState.tableRow];

  // we need to check until we hit the mBLOCKEND
  for (uint16_t idx = myState.tableRow; (idx < NUMOF(myStateTable)) && (mNONE == thisReturn); idx++) {
    // see if we match input condition for this row
    if ((0 != thisRowPtr->inputRBG&mINP_TRIG) && (0 != nowVinputRBG&mVINP_TRIG)) {
      // several cases for trigger
      if (0 != thisRowPtr->inputRBG&mINP_BANY) {
      } else if ((0 != thisRowPtr->inputRBG&mINP_BNONE) &&
                 (0 == (nowVinputRBG & (mVINP_B01|mVINP_B02|mVINP_B04)))) {
      }
    } else if ((0 != thisRowPtr->inputRBG&mINP_OPEN) && (0 != nowVinputRBG&mVINP_OPEN)) {
      thisReturn = idx;
      break;
    } else if ((0 != thisRowPtr->inputRBG&mINP_LOCK) && (0 != nowVinputRBG&mVINP_LOCK)) {
      thisReturn = idx;
      break;
    }

    if (0 != (thisRowPtr->inputRBG&mBLOCKEND)) {
      // this is a normal way to end - found the mBLOCKEND but did not find input
      break;
    }
    thisRowPtr += 1;
  } // end while searching for mBLOCKEND
    
  return thisReturn; // input did not happen
} // end RBG_waitForInput()

// ******************************** BUTTON AND TIMING UTILITIES ********************************


uint16_t RBGMatchInput (uint16_t inpMask) {
  return 0; // no match
} // end RBGMatchInput(...)

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

// getButtonInput() - get next button or other input, true inputs or debugging
//
// All the buttons are 0 when pressed and active when turning zero
// The lock/load input is 0 when connected and 1 when not lock/load
// The sound complete is 0 when sound is complete (FIXME TBR)
//
// NOTE: DPIN_LOCK_LOAD handled in code
// lock/load has priority - if not lock/load then no button or sound input matters
// when lock/load:
//    trigger means collect the state of the buttons
//    sound input is always sensed. If sound is playing and it finishes then we set input.
//
uint16_t getButtonInput() {
#if REAL_BUTTONS
  return(checkButtons());
#else // end if REAL_BUTTONS; now NOT REAL_BUTTONS
  return(checkKeyboard());
#endif // not REAL_BUTTONS
} // end getButtonInput()

// #define CAPTURE_BUTTONS_THISTIME button_count = button_count_thistime; button_mask = button_mask_thistime; button_timestamp = button_time;  // FIXME TBD MAYBE DO NOT NEED - LEFT IT OUT
// checkButtons() - returns mVINP_ mask for buttons to process
// 
uint16_t checkButtons() {
  static uint8_t debugThisManyCalls = 10;
  uint8_t idx;
  uint16_t thePin;
  uint16_t theVal;
  uint16_t returnInpMask = 0;

  if (debugThisManyCalls > 0) { Serial.println("checkButtons() called:"); printAllMyInputs(); }
  // do lock/load separately in code
  theVal = digitalRead(DPIN_LOCK_LOAD);
  if (LOW == theVal) { // we are locked and loaded; sensitive to trigger and other events
    if (debugThisManyCalls > 0) { Serial.print(" checkButtons "); Serial.println((uint16_t) __LINE__); }
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
    if (debugThisManyCalls > 0) { Serial.print(" checkButtons "); Serial.println((uint16_t) __LINE__); }
    returnInpMask = mVINP_OPEN;
  }

  if (debugThisManyCalls > 0) { Serial.print(" checkButtons found inputs: 0x"); Serial.println((uint16_t) returnInpMask, HEX); }
  if (debugThisManyCalls > 0) { debugThisManyCalls -= 1; }

  return(returnInpMask);
} // end checkButtons()

// ******************************** INITIALIZATION UTILITIES ********************************

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
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // device is SD card
  myDFPlayer.volume(25);  // Set volume value. From 0 to 30 - FIXME 25 is good
  Serial.println(F("DFPlayer Mini online."));
} // end DFsetup()

// ******************************** DEBUG UTILITIES ********************************

// checkDataGuard()
void checkDataGuard() {
  if ((0x55555555 != data_guard_before) || (0x55555555 != data_guard_after)) {
    Serial.print(F("checkDataGuard should be 1431655765; before="));
    Serial.print(data_guard_before);
    Serial.print(F(" after="));
    Serial.println(data_guard_after);
    delay(2000); // for debugging & show
  }
} // end checkDataGuard()

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
    // Serial.print("INIT EEP: stored inverted chksum 0x"); Serial.print(eeInvertedChksum,HEX); Serial.print(" value 0x"); Serial.print(byteValue,HEX); Serial.print(", calculated inverted chksum 0x"); Serial.println(((uint8_t) ~chksumValue),HEX);
  if (byteValue != invChksumValue) {
    // checksum does not match; zero out our EEPROM area
    Serial.print("INIT: calc EEPROM inverted chksum 0x"); Serial.print(invChksumValue,HEX); Serial.print(" does not match 0x"); Serial.print(byteValue,HEX); Serial.println("; INITIALIZING");
    byteValue = 0;
    for (address = 0; address < eeLastNonChksum; address++) { // one less than entire data area
      byte2Value = EEPROM.read(address);
      if (byte2Value != byteValue) { // avoid EEPROM writes when possible
        EEPROM.write(address, byteValue);
      }
    } // end zero out our EEPROM area except last value
    eeprom_store_with_chksum(eeLastNonChksum, byteValue); // store last value and checksum
  } // end if checksum does not match
} // end eeprom_check_init()

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
    // Serial.print("INIT EEP: address 0x"); Serial.print(address,HEX); Serial.print(" value 0x"); Serial.print(byteValue,HEX); Serial.print(" calc chksum 0x"); Serial.println(chksumValue,HEX);
  } // end caclulate checksum
  return((uint8_t) (~chksumValue));
} // end eeprom_calc_inverted_checksum()

/* need to re-think this one
void stateTable_store(RBGStateTable * theRow, uint8_t * theStates) {
  uint8_t  val  = 0;
  uint32_t addr = 0;
  if (VYBG == theRow->storeVal) {
    val = theStates->VYBG;
  } else {
    val = theStates->storeVal;
  }
  addr = (stateTable_ROW->storeAddr & mADDRLOW) + ((stateTable_ROW->storeAddr & mADDRHI) >> mADDRHIrshift)
  if (stateTable_ROW->storeAddr & mIDX) {
    addr += theStates->ramVals[(stateTable_ROW->storeAddr & mIDX) >> mIDXrshift]
  }
  EEPROM[stateTable_ROW->storeAddr] = addr
  EEPROM[stateTable_ROW->storeVal] = val
} // end stateTable_store()
*/

void printAllMyState() {
  Serial.println(F("DEBUG - myState:"));
  Serial.print(F("  - tableRow: "));
  Serial.println((uint16_t) myState.tableRow);
  Serial.print(F("  - tableRowInProcFlags: 0x"));
  Serial.println((uint16_t) myState.tableRowInProcFlags, HEX);
  Serial.print(F("  - VinputRBG: 0x"));
  Serial.println((uint16_t) myState.VinputRBG, HEX);
} // end printAllMyState()

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

void printOneInput(uint8_t dpin, char * dtext) {
  Serial.print(dtext);
  if (LOW == digitalRead(dpin)) {
    Serial.println("LOW");
  } else {
    Serial.println("HIGH");
  }
}
