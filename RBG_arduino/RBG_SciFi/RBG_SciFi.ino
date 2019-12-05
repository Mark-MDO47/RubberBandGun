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

#include "RBG_SciFi_LEDs.h"                  // LED structural and pattern definitions
#include "RBG_SciFi_StatesAndInputs.h"       // state tables and input definitions

#define NUMOF(x) (sizeof(x) / sizeof(*x))

#define SERIALDEBUG 1                        // serial debugging

#define DPIN_FASTLED      3  // serial out - talk to LED rings
#define DPIN_BTN_TRIGGER  4  // digital input - the trigger
#define DPIN_BTN_YELLOW   5  // digital input - yellow configuration button
#define DPIN_BTN_GREEN    6  // digital input - green configuration button
#define DPIN_BTN_BLACK    7  // digital input - black configuration button
#define DPIN_LOCK_LOAD    8  // digital input - grounded when in lock and load position
#define DPIN_SWSRL_RX    10  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_TX    11  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY  12  // digital input - signals when audio finishes
#define DPIN_SOLENOID    13  // often has internal LED and resistor soldered to board, can make INPUT not work


// EEPROM addresses
// EEPROM[eeSoundSave+idx] idx: 1 WindUp, 2 Shoot, 4 Open, 7 Load
#define eeSoundSave 0x00 // EEPROM starting address for sound configuration
#define eeLEDSave   0x10 // EEPROM starting address for LED pattern configuration

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


uint8_t gHue = 0; // rotating "base color" used by Demo Reel 100
CRGBPalette16 gPal; // palette for Fire2012WithPalette()
uint16_t gSeed = ((uint16_t) 42); // my favorite is 47 but the whole world loves 42 and HHG2TG
#if FASTLED_FIRE_PATTERN // only used for Fire pattern
CRGB dark_color_palette[NUM_ARDUINOS]  = { CRGB::DarkGreen, CRGB::Red,    CRGB::Blue, CRGB::DarkOrange };
CRGB light_color_palette[NUM_ARDUINOS] = { CRGB::LimeGreen, CRGB::Yellow, CRGB::Aqua, CRGB::Gold };
#endif // FASTLED_FIRE_PATTERN

#define mINPROCFLG_WAITFORSOUND ((uint8_t) 0x80)  // wait for sound to finish
#define mINPROCFLG_WAITFORINPUT ((uint8_t) 0x40)  // wait for user input (trigger with perhaps others)

// ******************************** SETUP ********************************
// setup()
//   initializes hardware serial port for general debug
//   initializes SoftwareSerial for DFPlayer audio player YX5200 control
//   initializes push button pins
//   initializes FastLED library
void setup() {
  // put your setup code here, to run once:

#if SERIALDEBUG
  Serial.begin(115200);         // this is for general debug
#endif // SERIALDEBUG
  mySoftwareSerial.begin(9600); // this is control to DFPlayer audio player

  Serial.println();
  Serial.println(F("FOOF SciFi RBG init..."));

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

  Serial.println(F("FOOF SciFi RBG init COMPLETE"));
} // end setup()

// ******************************** LOOP ********************************
//  loop()
//     Get the inputs - buttons, barrel, sound ended
//     Use our state table and state and inputs to calculate next state
//     Determine if we need to change LED pattern and/or sound
//     If needed, release the rubber band and set timer to stop the solenoid current later
//
void loop() {
  // put your main code here, to run repeatedly:
  
  gHue += 3; // rotating "base color" used by Demo Reel 100 patterns

  myState.nowTimer = millis();
  myState.VinputRBG = RBG_debounceInputs();
  
  if (0 == myState.tableRowInProcFlags) {
    myState.tableRowInProcFlags = RBG_startRow(); // just do what the row says
  } else if (mINPROCFLG_WAITFORSOUND == myState.tableRowInProcFlags) {
    myState.tableRowInProcFlags = RBG_waitForSound(); // wait for sound to complete
  } else if (mINPROCFLG_WAITFORINPUT == myState.tableRowInProcFlags) {
    myState.tableRowInProcFlags = RBG_waitForInput(); // wait for user input, trigger and maybe other buttons
  } else {
    Serial.print(F("ERROR - unknown input "));
    Serial.println((uint16_t) myState.tableRowInProcFlags);
    myState.tableRowInProcFlags = 0;
  } // end process state table

  if ((NO_BUTTON_CHANGE != myState.nextPattern) && (myState.nextPattern != myState.pattern)) {
    myState.pattern = myState.nextPattern;
  }
  myState.nextPattern = NO_BUTTON_CHANGE;
  if (myState.oldPattern != myState.pattern) {
    Serial.print(F("switch to pattern ")); Serial.println((int16_t) myState.pattern);
  }
  checkDataGuard();
  doPattern();
  checkDataGuard();
  FastLED.show();
  myState.oldPattern = myState.pattern;

  if (myState.pattern < MIN_FASTLED_PATTERN) { // Mark's patterns
    doDwell(myState.ptrn_delay, 1);
  } else { // FastLED patterns
    doDwell(myState.ptrn_delay_fastled, 1);
  }

  myState.prevTimer = myState.nowTimer;
}  // end loop()

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
  myDFPlayer.volume(25);  // Set volume value. From 0 to 30
  Serial.println(F("DFPlayer Mini online."));
} // end DFsetup()

// ******************************** BUTTON AND TIMING UTILITIES ********************************

uint8_t RBG_debounceInputs() {
  return 0; // RBG_debounceInputs
} // end RBG_debounceInputs()

uint16_t RBGMatchInput (uint16_t inpMask) {
  return 0; // no match
} // end RBGMatchInput(...)

uint8_t RBG_waitForSound() {
  return 0; // RBG_waitForSound to end
} // end RBG_waitForSound()

uint8_t RBG_waitForInput() {
  return 0; // RBG_waitForInput
} // end RBG_waitForInput()

// doDwell(int16_t dwell, uint8_t must_be_diff_pattern) - dwell or break out if button press
//   returns TRUE if should switch to different pattern
//   else returns false
//
// keeps track of button_time
//
// FIXME - needs adaptation for Rubber Band Gun - handle LED pattern, sound and solenoid
//
#define SMALL_DWELL 20
int16_t doDwell(int16_t dwell, uint8_t must_be_diff_pattern) {
  int16_t numloops = dwell / SMALL_DWELL;
  int16_t i;

  Serial.println(F("FIXME doDwell(...) - needs adaptation for Rubber Band Gun - handle LED pattern, sound and solenoid"));

  for (i = 0; i < numloops; i++) {
    nextInputFromButtons();
    if ((0 != must_be_diff_pattern) && (myState.nextPattern == myState.pattern)) myState.nextPattern = NO_BUTTON_CHANGE;
    if (myState.nextPattern != NO_BUTTON_CHANGE) return(myState.nextPattern != NO_BUTTON_CHANGE);
    delay(SMALL_DWELL);
    button_time += SMALL_DWELL;
  }
  if ((dwell % SMALL_DWELL) != 0) {
    nextInputFromButtons();
    if ((0 != must_be_diff_pattern) && (myState.nextPattern == myState.pattern)) myState.nextPattern = NO_BUTTON_CHANGE;
    if (myState.nextPattern != NO_BUTTON_CHANGE) return(myState.nextPattern != NO_BUTTON_CHANGE);
    delay(dwell % SMALL_DWELL);
    button_time += (dwell % SMALL_DWELL);
  }
  return(myState.nextPattern != NO_BUTTON_CHANGE);
} // end doDwell()

// nextInputFromButtons() - store nextPattern if button pressed
//     nextPattern will get used when we get back to the main loop
int16_t nextInputFromButtons() {
  int16_t myButton = getButtonPress();
  if (myButton != NO_BUTTON_PRESS) {
    nextPattern = myButton;
  }
  return (nextPattern);
} // end nextInputFromButtons()

// getButtonPress() - get next button press, true button or debugging
int16_t getButtonPress() {
#if REAL_BUTTONS
  return(checkButtons());
#else // end if REAL_BUTTONS; now NOT REAL_BUTTONS
  return(checkKeyboard());
#endif // not REAL_BUTTONS
} // end getButtonPress()

#if REAL_BUTTONS

  #define CAPTURE_BUTTONS_THISTIME button_count = button_count_thistime; button_mask = button_mask_thistime; button_timestamp = button_time;
  // checkButtons() - returns number of button pressed (1 through 6) or NO_BUTTON_PRESS
  //    news flash - not enough time to do all 6 buttons; just did 3
  // 
  // with REAL_BUTTONS, holding button down gives pattern 1 which is OFF
  // pressing button 1 gives pattern 2, etc.
  // 
  // use button_time to determine when to do things
  //
  int16_t checkButtons() {
    uint8_t  val;
    int16_t thePin;
    static uint32_t button_timestamp = 0;
    static uint8_t button_mask = 0; // 1=btn1, 2=btn2, 4=btn3
    static uint8_t button_count = 0;
    uint8_t button_mask_thistime, button_count_thistime;
    int16_t returnPtrn = 1; // 1 is display nothing
//    static int16_t prevReturn = NO_BUTTON_PRESS; // for debugging only

    button_mask_thistime = button_count_thistime = 0;
    for (thePin = PSHBTN1; thePin <= PSHBTN6; thePin ++) {
      val = digitalRead(thePin);
      if (LOW == val) {
        button_mask_thistime += (1 << (thePin - PSHBTN1));
        button_count_thistime += 1;
      }
    } // end for all pushbuttons
    if (0 != button_mask_thistime) {
      if (0 != button_mask) {
        returnPtrn = NO_BUTTON_PRESS; // already said we have button down
      } else {
        returnPtrn = 1; // always return 1 whenever a button is being pushed
      }
      if (button_count_thistime >= button_count) {
        CAPTURE_BUTTONS_THISTIME
      } else {
        // they may be letting up on the buttons; they get 1000 millisec or we reset to current buttons
        if ((button_time - button_timestamp) > 1000) {
          // reset to thistime buttons
          CAPTURE_BUTTONS_THISTIME
        }
      } // button count decreased but not zero
    } else { // button count is zero
      returnPtrn = ButtonsToPatternNumber[button_mask];
      button_timestamp = button_mask = button_count = 0;
    }
//    if (prevReturn != returnPtrn) { // DEBUG
//      Serial.print("prevReturn="); Serial.print(prevReturn); Serial.print("returnPtrn="); Serial.println(returnPtrn); 
//    }
//    prevReturn = returnPtrn;
    return(returnPtrn);
  } // end checkButtons()
#else // end if REAL_BUTTONS; now NOT REAL_BUTTONS
  // checkKeyboard() - for debugging - serial port buttons
  int16_t checkKeyboard() { // not REAL_BUTTONS
    int8_t received_serial_input;
    int16_t myButton = NO_BUTTON_PRESS;
    if (Serial.available() > 0) {
      received_serial_input = Serial.read();
      switch ((int16_t) received_serial_input) {
        case (int16_t) '1': myButton = 1; break;
        case (int16_t) '2': myButton = 2; break;
        case (int16_t) '3': myButton = 3; break;
        case (int16_t) '4': myButton = 4; break;
        case (int16_t) '5': myButton = 5; break;
        case (int16_t) '6': myButton = 6; break;
        default: myButton = NO_BUTTON_PRESS; break;
      } // end switch on received serial "button"
    } // end if there was serial input ready to read
    return(myButton);
  } // end checkKeyboard()
#endif // not REAL_BUTTONS

// patternFromButtons() - get pattern to use (called from main loop)
// could have button pressed now - do that ignore any earlier press
// could have seen button pressed earlier and just now handling it - do that
// otherwise keep same pattern - no change
int16_t patternFromButtons() {
  int16_t myButton = getButtonPress(); // no change unless we see a change
  if (myButton == NO_BUTTON_PRESS) {
    if (NO_BUTTON_CHANGE != nextPattern) {
      myButton = nextPattern;
    } else {
      myButton = pattern;
    }
  } // end if no button pressed now so process earlier button press
  nextPattern = NO_BUTTON_CHANGE;
  return(myButton);
} // end patternFromButtons()


// ******************************** STATE TABLE UTILITIES ********************************

// RBG_startRow() - start processing a row in myStateTable
//    myState.tableRowInProcFlags should be zero to call this
uint8_t RBG_startRow() {
  RBGStateTable * thisRowPtr = &myStateTable[myState.tableRow];
  uint8_t thisSound = 0;
  uint8_t thisLED = 0;
  uint8_t thisReturn = mNONE;
  if (mNONE == thisRowPtr->gotoOnInput) {
    // not waiting for input
    thisSound = thisRowPtr->efctSound;
    if (mNONE != thisSound) {
      myDFPlayer.playMp3Folder(thisSound+mEFCT_CONFIGURE); //play specific mp3 in SD:/MP3/####.mp3; File Name(0~9999)
      thisReturn |= mINPROCFLG_WAITFORSOUND;
    } // end if should start a sound and wait for it
    thisLED = thisRowPtr->efctLED;
    if (mNONE != thisLED) {
       // FIXME LEDS to efctLED
       myState.ledTimer = millis() + deltaMsLED;
    }  // end if should switch to other LED pattern
    if (mNONE == thisReturn) { // if we still don't have anything to do, just jump
      myState.tableRow = thisRowPtr->gotoWithoutInput; // we will go next time.
      // thisReturn is already mNONE
    } // end if do the jump next time
  } else { // there is input to wait for, perhaps a block
    for (int idx = myState.tableRow; idx < NUMOF(myStateTable); idx++) {
      if (RBGMatchInput(mINP_TRIG&myStateTable[idx].inputRBG)){ // match the inputs!
        myState.tableRow = myStateTable[idx].gotoOnInput;
        thisReturn = mNONE; // start the new state
        break;
      } else if (mBLOCKEND&myStateTable[idx].blkFlags) { // no more in this block to check
        thisReturn = mNONE; // start this block again next time
        break; // end of block; break the loop
      } // end of checking for this idx
    } // end for idx, potentially for a block
  } // end if there is input to wait for
  return thisReturn;
} // end RBG_startRow()

// ******************************** DEBUG UTILITIES ********************************

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
