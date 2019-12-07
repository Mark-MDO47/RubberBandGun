
// Mark Olson 2019-11
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
// This file has definitions for state tables and input processing (mostly buttons)
//

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


// define the symbols
#define mUNDEFINED 254
#define mNONE 255

//
// used in myStateTable[].efctSound and .efctLED
//
#define mEFCT_SPCLFUNC    0x80
#define mSPCL_ONETIME 0x80
#define mSPCL_SHOOT   0x40
#define mSPARKLE 1  // LED Effect

#define mFOOF 1 // This is the FOOF Science Fiction Rubber Band Gun version 1.0.
#define mBLOCKSTART 0x80
#define mBLOCKEND   0x40
#define mPOWERON 0  // address in myStateTable[]
#define mMENU 1

// define the effect number ranges
#define mEFCT_WIND_UP 0
#define mEFCT_SHOOT 10
#define mEFCT_OPEN_BARREL 20
#define mEFCT_LOCK_LOAD 30
#define mEFCT_INIT_PWR_UP 40
#define mEFCT_CONFIGURE 80


// masks for input detections: button, trigger, sound module, and barrel states and state changes
//   used (only) in .inputRBG in myStateTable and in code to examine that
#define mINP_B01   0x0001      // mask for DPIN_BTN_YELLOW only
#define mINP_B02   0x0002      // mask for DPIN_BTN_GREEN  only
#define mINP_B03   0x0003      // mask for DPIN_BTN_YELLOW and DPIN_BTN_GREEN
#define mINP_B04   0x0004      // mask for DPIN_BTN_BLACK  only
#define mINP_B05   0x0005      // mask for DPIN_BTN_YELLOW and DPIN_BTN_BLACK
#define mINP_B06   0x0006      // mask for DPIN_BTN_GREEN  and DPIN_BTN_BLACK
#define mINP_B07   0x0007      // mask for DPIN_BTN_YELLOW and DPIN_BTN_GREEN and DPIN_BTN_BLACK
#define mINP_BANY  0x0008      // mask for any DPIN_BTN_ combination but at least one of them
#define mINP_BNONE 0x0010      // mask for no DPIN_BTN_ depressed
#define mINP_TRIG  0x0020      // mask for just depressed the trigger
#define mINP_LOCK  0x0040      // mask for just connected the barrel
#define mINP_OPEN  0x0080      // mask for just disconnected the barrel
#define mINP_ENDSOUND 0x0100   // mask for sound just ended

// masks for input values: button, trigger, sound module, and barrel states and state changes
//   used (only) in .VinputRBG in myState
#define mVINP_B01   0x0001     // mask for DPIN_BTN_YELLOW (currently depressed)
#define mVINP_B02   0x0002     // mask for DPIN_BTN_GREEN (currently depressed)
#define mVINP_B04   0x0004     // mask for DPIN_BTN_BLACK (currently depressed)
#define mVINP_TRIG  0x0020     // mask for just depressed the trigger
#define mVINP_LOCK  0x0040     // mask for just connected the barrel
#define mVINP_OPEN  0x0080     // mask for just disconnected the barrel
#define mVINP_PREVLOCK  0x0100 // mask for the barrel was lock/load last time we checked
#define mVINP_SOUNDEND  0x0200 // mask for sound just ended
#define mVINP_SOUNDACTV 0x0400 // mask for sound was previously active

// masks for in-process events: wait-for-sound or wait-for-input
//   used (only) in tableRowInProcFlags
#define mINPROCFLG_WAITFORSOUND ((uint8_t) 0x80)  // wait for sound to finish
#define mINPROCFLG_WAITFORINPUT ((uint8_t) 0x40)  // wait for user input (trigger with perhaps others)

// table to identify input pins and corresponding masks
// DPIN_LOCK_LOAD handled separately in code
// the masks are used (only) in .VinputRBG in myState
typedef struct _pins_to_vals_t {
  uint16_t pin; uint16_t val;
} pins_to_vals_t;
static pins_to_vals_t myPinsToVals[] = {
  { DPIN_BTN_TRIGGER, mVINP_TRIG },
  { DPIN_BTN_YELLOW,  mVINP_B01 },
  { DPIN_BTN_GREEN,   mVINP_B02 },
  { DPIN_BTN_BLACK,   mVINP_B04 },
  { DPIN_AUDIO_BUSY,  mVINP_SOUNDEND },
};


// STATE TABLE
//  EEPROM[stateTable_ROW->storeAddr] = addr
//  EEPROM[stateTable_ROW->storeVal] = val
// basically there are two possibilities:
//   gotoWithoutInput: play the sound & blink the efctLED then goto when sound done
//   gotoOnInput: wait for input then play the sound & blink the efctLED then goto when sound done
// There can be a "block" of wait for inputs; check each one from mBLOCKSTART to mBLOCKEND
// If the sound includes mEFCT_SPCLFUNC then we call our RBGSpecialFunc to do the task
// 
// 
typedef struct _RBGStateTable {
    uint8_t blkFlags;         // mBLOCKSTART, mBLOCKEND or mNONE
    uint8_t SPECIAL;          // special row-handling flags: mSPCL_*
    uint8_t efctSound;  // index for sound to make after input match
    uint8_t efctLED;           // index for light pattern while waiting
    uint16_t inputRBG;        // mask for input expected: mINP_* - NOTE: 16 bits
    uint8_t storeVal;         // value to store, 8 bit uint
    uint8_t storeAddr;        // address to store; includes mask for mFUNC, mVAL,
                                 // eeSoundSave|mFUNC: idx= 3 WindUp, 2 Shoot, 4 Open, 7 Load
    uint8_t gotoOnInput;      // index within table to go with matching input
    uint8_t gotoWithoutInput; // index within table to go without waiting for input
    uint8_t index;            // input column unused in this table
} RBGStateTable;


static struct myState_t {
  uint8_t tableRow = 0;            // points to state that we will process or are processing
  uint8_t tableRowInProcFlags = 0; // what we are waiting on to process this state
  uint16_t VinputRBG = 0;          // bits for input buttons and sound finish: mVINP_* - NOTE: 16 bits
  uint32_t timerPrev = 0;          // timer from previous time through loop
  uint32_t timerNow = 0;           // timer from this time through loop
  uint32_t timerLed = 0;           // timer for next LED activity
  uint32_t timerSolenoid = 0;      // timer for next solenoid OFF
  uint32_t debounceTimer = 0;      // timer for debounce of buttons
  // LED state info
  int8_t   pattern = 1;            // keep track of patterns - this is what we are doing now
  int8_t   oldPattern = 2;         // this is the previous pattern
  int8_t   nextPattern = 2;        // this is the next pattern
  int8_t   this_ring = 0;          // from ring_3 (value 0, 32 LEDs) to ring_2 (value 1, 24 LEDs) to ring_1 (value 2, 16 LEDs)
  int8_t   this_qrtr = 0;          // from qrtr_1 (value 0) to qrtr_4 (value 3), count modulo in either direction
  int16_t  ptrn_delay = 100;       // proper delay for Mark's patterns
  int16_t  ptrn_delay_fastled = 15;// proper delay for FastLED patterns
} myState;

// patterns: (FIXME these will change)
//   1 = OFF
//   2 = draw then down the drain
//   3 = Radar POLY 2018
//   4 = POLY 2018
//   5 = draw rings
//   6 = do surrounding around letter then fade one to the other
//   7 = rainbowWithGlitter Demo Reel 100 pattern
//   8 = bpm; this is the best Demo Reel 100 pattern on the Mokungit 93 LED disk
//   9 = juggle Demo Reel 100 pattern
//  10 = Fire2012 from another Kriegsman FastLED example
#define MIN_FASTLED_PATTERN 7

//
// the state table itself - automatically generated from makeStateTable.py
//
static RBGStateTable myStateTable[4] = {
    { /* row 0 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mNONE, .efctSound=mFOOF, .efctLED=mSPARKLE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mMENU, .index=mPOWERON, },
    { /* row 1 */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_ONETIME | mSPCL_SHOOT, .efctSound=mEFCT_SPCLFUNC|mEFCT_SHOOT, .efctLED=mEFCT_SPCLFUNC|mEFCT_SHOOT, .inputRBG=mINP_TRIG|mINP_BNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mMENU, .gotoWithoutInput=mNONE, .index=mMENU, },
    { /* row 2 */  .blkFlags=mNONE, .SPECIAL=mSPCL_ONETIME, .efctSound=mEFCT_SPCLFUNC|mEFCT_OPEN_BARREL, .efctLED=mEFCT_SPCLFUNC|mEFCT_OPEN_BARREL, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mMENU, .gotoWithoutInput=mNONE, .index=mMENU, },
    { /* row 3 */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_ONETIME, .efctSound=mEFCT_SPCLFUNC|mEFCT_LOCK_LOAD, .efctLED=mEFCT_SPCLFUNC|mEFCT_LOCK_LOAD, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mMENU, .gotoWithoutInput=mNONE, .index=mMENU, },
};
