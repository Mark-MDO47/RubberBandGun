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
#include "RBG_SciFi_LEDs.h"                  // 
#include "DFRobotDFPlayerMini.h"             // to communicate with the YX5200 audio player

#define SERIALDEBUG 1                        // serial debugging

// #define DFPRINTDETAIL (1&SERIALDEBUG)     // if need detailed status from myDFPlayer
#define DFPRINTDETAIL 0                      // will not print detailed status from myDFPlayer
void DFprintDetail(uint8_t type, int value); // definition of call doesn't hurt
void DFsetup();                              // initialize myDFPlayer

#define DPIN_FASTLED      3  // talk to FASTLED library
#define DPIN_BTN_TRIGGER  4
#define DPIN_BTN_YELLOW   5
#define DPIN_BTN_GREEN    6
#define DPIN_BTN_BLACK    7
#define DPIN_SWSRL_RX    10
#define DPIN_SWSRL_TX    11
#define DPIN_AUDIO_BUSY  12
#define DPIN_SOLENOID    13  // often has internal LED and resistor soldered to board, can make INPUT not work

// masks for inputs: button, trigger and barrel states and state changes
#define mINP_B01   0x01  // mask for DPIN_BTN_YELLOW only
#define mINP_B02   0x02  // mask for DPIN_BTN_GREEN  only
#define mINP_B03   0x03  // mask for DPIN_BTN_YELLOW and DPIN_BTN_GREEN
#define mINP_B04   0x04  // mask for DPIN_BTN_BLACK  only
#define mINP_B05   0x05  // mask for DPIN_BTN_YELLOW and DPIN_BTN_BLACK
#define mINP_B06   0x06  // mask for DPIN_BTN_GREEN  and DPIN_BTN_BLACK
#define mINP_B07   0x07  // mask for DPIN_BTN_YELLOW and DPIN_BTN_GREEN and DPIN_BTN_BLACK
#define mINP_BANY  0x08  // mask for any DPIN_BTN_ combination but at least one of them
#define mINP_BNONE 0x10  // mask for no DPIN_BTN_ depressed
#define mINP_TRIG  0x20  // mask for just depressed the trigger
#define mINP_LOCK  0x40  // mask for just connected the barrel
#define mINP_OPEN  0x80  // mask for just disconnected the barrel


// values that can be stored
#define VYBG 0x10    // whatever is in DPIN_BTN_YELLOW and DPIN_BTN_GREEN and DPIN_BTN_BLACK (0 thru 7)
#define V00  0x00    // the value 0
#define V01  0x01    // the value 1
#define V02  0x02    // the value 2
#define V03  0x03    // the value 3
#define V04  0x04    // the value 4
#define V05  0x05    // the value 5
#define V06  0x06    // the value 6
#define V07  0x07    // the value 7

// EEPROM addresses
// EEPROM[eeSoundSave+idx] idx: 1 WindUp, 2 Shoot, 4 Open, 7 Load
#define eeSoundSave 0x00 // EEPROM starting address for sound configuration
#define eeLEDSave   0x10 // EEPROM starting address for LED pattern configuration

// STATE TABLE
//  EEPROM[stateTable_ROW->storeAddr] = addr
//  EEPROM[stateTable_ROW->storeVal] = val
typedef struct _RBGStateTable {
    uint8_t blkFlags;         // mBLOCKSTART, mBLOCKEND or mNONE
    uint8_t SPECIAL;          // special row-handling flags: mSPCL_*
    uint8_t soundAfterInput;  // index for sound to make after input match
    uint8_t lights;           // index for light pattern while waiting
    uint8_t inputRBG;         // mask for input expected
    uint8_t storeVal;         // value to store, 8 bit uint
    uint8_t storeAddr;        // address to store; includes mask for mFUNC, mVAL,
                              //   eeSoundSave|mFUNC: idx= 3 WindUp, 2 Shoot, 4 Open, 7 Load
    uint8_t gotoOnInput;      // index within table to go with matching input
    uint8_t gotoWithoutInput; // index within table to go without waiting for input
    uint8_t index;            // input column unused in this table
} RBGStateTable;

SoftwareSerial mySoftwareSerial(DPIN_SWSRL_RX, DPIN_SWSRL_TX); // to talk to YX5200 audio player
DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player

#define mUNDEFINED -2
#define mNONE -1
#define mMENU 1

// define the effect number ranges
#define mEFCT_WIND_UP 0
#define mEFCT_SHOOT 10
#define mEFCT_OPEN_BARREL 20
#define mEFCT_LOCK_LOAD 30
#define mEFCT_INIT_PWR_UP 40
#define mEFCT_CONFIGURE 80


RBGSTATETABLE myState[4] = {
    { // row 0
        uint8_t mBLOCKSTART|mBLOCKEND; // blkFlags
        uint8_t mNONE; // SPECIAL
        uint8_t mFOOF; // soundAfterInput
        uint8_t mSPARKLE; // lights
        uint8_t mNONE; // inputRBG
        uint8_t mNONE; // storeVal
        uint8_t mNONE; // storeAddr
        uint8_t mNONE; // gotoOnInput
        uint8_t mMENU; // gotoWithoutInput
        uint8_t mPOWERON; // index
    },
    { // row 1
        uint8_t mBLOCKSTART; // blkFlags
        uint8_t mSPCL_ONETIME | mSPCL_SHOOT; // SPECIAL
        uint8_t mEFCT_SPCL|mEFCT_SHOOT; // soundAfterInput
        uint8_t mEFCT_SPCL|mEFCT_SHOOT; // lights
        uint8_t mINP_TRIG|mINP_BNONE; // inputRBG
        uint8_t mNONE; // storeVal
        uint8_t mNONE; // storeAddr
        uint8_t mMENU; // gotoOnInput
        uint8_t mNONE; // gotoWithoutInput
        uint8_t mMENU; // index
    },
    { // row 2
        uint8_t mNONE; // blkFlags
        uint8_t mSPCL_ONETIME; // SPECIAL
        uint8_t mEFCT_SPCL|mEFCT_OPEN_BARREL; // soundAfterInput
        uint8_t mEFCT_SPCL|mEFCT_OPEN_BARREL; // lights
        uint8_t mINP_OPEN; // inputRBG
        uint8_t mNONE; // storeVal
        uint8_t mNONE; // storeAddr
        uint8_t mMENU; // gotoOnInput
        uint8_t mNONE; // gotoWithoutInput
        uint8_t mMENU; // index
    },
    { // row 3
        uint8_t mBLOCKEND; // blkFlags
        uint8_t mSPCL_ONETIME; // SPECIAL
        uint8_t mEFCT_SPCL|mEFCT_LOCK_LOAD; // soundAfterInput
        uint8_t mEFCT_SPCL|mEFCT_LOCK_LOAD; // lights
        uint8_t mINP_LOCK; // inputRBG
        uint8_t mNONE; // storeVal
        uint8_t mNONE; // storeAddr
        uint8_t mMENU; // gotoOnInput
        uint8_t mNONE; // gotoWithoutInput
        uint8_t mMENU; // index
    }
}

void setup() {
  // put your setup code here, to run once:

#if SERIALDEBUG
  Serial.begin(115200);         // this is for general debug
#endif // SERIALDEBUG
  mySoftwareSerial.begin(9600); // this is control to DFPlayer audio player

  Serial.println();
  Serial.println(F("FOOF SciFi RBG init..."));

  pinMode(DPIN_BTN_TRIGGER, INPUT);
  pinMode(DPIN_BTN_YELLOW,  INPUT);
  pinMode(DPIN_BTN_GREEN,   INPUT);
  pinMode(DPIN_BTN_BLACK,   INPUT);
  pinMode(DPIN_AUDIO_BUSY,  INPUT);
  pinMode(DPIN_SOLENOID,   OUTPUT);

  DFsetup();

  FastLED.addLeds<NEOPIXEL,DPIN_FASTLED>(led_display, NUM_LEDS_PER_DISK);
  FastLED.setBrightness(BRIGHTMAX); // we will do our own power management

} // end setup()

void loop() {
  // put your main code here, to run repeatedly:

  static unsigned long timer = millis();

}  // end loop()

void DFsetup() {
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  // Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin DFPlayer:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
} // end DFsetup()

void stateTable_store(stateTable_ROW * theRow, stateTable_STATE * theStates) {
  uint_8  val  = 0;
  uint_32 addr = 0;
  if (VYBG == theRow->storeVal) {
    val = stateTable_STATE->VYBG;
  } else {
    val = stateTable_ROW->storeVal;
  }
  addr = (stateTable_ROW->storeAddr & mADDRLOW) + ((stateTable_ROW->storeAddr & mADDRHI) >> mADDRHIrshift)
  if (stateTable_ROW->storeAddr & mIDX) {
    addr += theStates->ramVals[(stateTable_ROW->storeAddr & mIDX) >> mIDXrshift]
  }
  EEPROM[stateTable_ROW->storeAddr] = addr
  EEPROM[stateTable_ROW->storeVal] = val
} // end stateTable_store()

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
      }
      break;
    default:
      break;
  }
} // end DFprintDetail()
#else  // no DFPRINTDETAIL
void DFprintDetail(uint8_t type, int value) {} // just return
#endif // DFPRINTDETAIL
