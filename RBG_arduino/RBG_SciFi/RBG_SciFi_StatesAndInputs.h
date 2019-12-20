
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

#define NUMOF(x) (sizeof((x)) / sizeof((*x)))

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



// values that can be stored in EEPROM (FIXME THIS MAY CHANGE)
#define VYBG 0x10    // whatever is in DPIN_BTN_YELLOW and DPIN_BTN_GREEN and DPIN_BTN_BLACK (0 thru 7)
#define V00  0x00    // the value 0
#define V01  0x01    // the value 1
#define V02  0x02    // the value 2
#define V03  0x03    // the value 3
#define V04  0x04    // the value 4
#define V05  0x05    // the value 5
#define V06  0x06    // the value 6
#define V07  0x07    // the value 7

/////////////////// start -> INPUTS 1 FROM makeStateTable.py <- //////////////////////////////////

// define the symbols - general use symbols:
#define mUNDEFINED 254
#define mNONE 255
#define mZERO 0

// define the symbols - .SPECIAL:
// #define mSPCL_EFCT_ONETIME 0xxxx - this is the standard, no bit needed
#define mSPCL_EFCT_CONTINUOUS 0x1000 // set this bit for continuous play while waiting for input
#define mSPCL_HANDLER         0x0010 // mask for functions is ((uint16_t) (mSPCL_HANDLER-1))
#define mSPCL_HANDLER_SHOOT        1 // a special handler function
#define mSPCL_HANDLER_SOLENOID     2 // a special handler function

// define the symbols - .blkFlags:
#define mBLOCKSTART 0x80
#define mBLOCKEND   0x40

// define the symbols - .index: first the single constant mROW_POWERON one, then the others:
#define mROW_POWERON 0  // first address in myState[]
#define mROW_WINDUP 4
#define mROW_OPNBRL 6
#define mROW_LOKLOD 7
#define mROW_MENU 1
#define mROW_WINDUP_SOUND 5
#define mROW_SHOOT 8
#define mROW_SHOOT_SOUND 9
#define mROW_SOLENOID 10

// define the effect number ranges - must be divisible by 10
#define mEFCT_WIND_UP       0  // 001 to 009 - wind-up effects
#define mEFCT_SHOOT        10  // 011 to 019 - shoot effects
#define mEFCT_OPEN_BARREL  20  // 021 to 029 - open barrel effects
#define mEFCT_LOCK_LOAD    30  // 031 to 039 - lock and load barrel effects
#define mEFCT_PWRON        40  // 041 to 049 - after initial power-up effects
#define mEFCT_CONFIGURE    80  // 081 to 099 - effects used to navigate menus
#define mEFCT_UNIQ        100  // 101 to 109 - unique effects not included in configurations

/////////////////// end -> INPUTS 1 FROM makeStateTable.py <- //////////////////////////////////

//
// define the UNIQUE effects (lights and sounds) here. These cannot be configured as the other effects can.
//
#define mEFCT_UNIQ_WAITING 84  // FIXME 101 not this - waiting pattern: low level spooky sounds, blinky lights
#define mEFCT_UNIQ_SILENCE 85  // FIXME 102 not this

#define mBLOCKSTART 0x80
#define mBLOCKEND   0x40
#define mPOWERON 0  // address in myStateTable[]
#define mMENU 1


// EEPROM addresses
// EEPROM[eeSoundSave+idx] idx: 0 WindUp, 1 Shoot, 2 Open, 3 Load, 4 PowerUp 8 Configure
#define eeSoundSave 0x0000 // EEPROM starting address for sound configuration
#define eeLEDSave   0x0010 // EEPROM starting address for LED pattern configuration
#define eeLastNonChksum  0x1E // EEPROM address of last non-checksum data
#define eeInvertedChksum 0x1F // EEPROM address of last non-checksum data

#define EEPOFFSET(parm)   ((uint16_t) (parm / 10)) // example: EEPOFFSET(mEFCT_SHOOT) = 1
#define EFCT_IS_EEP(parm) (0 == ((uint16_t) parm) % 10) // if (EFCT_IS_EEP(mEFCT_PWRON)) will be true


typedef struct _decodeBits_t { uint16_t theBit; const char * theText; } decodeBits_t;

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
#define mVINP_SOUNDACTV  0x0200 // mask for sound was active last time we checked
// #define mVINP_SOUNDEND 0x0400 // mask for sound was ended and previously active
static decodeBits_t decodeBits_VinputRBG[] = {
    mVINP_B01, " mVINP_B01 YELLOW",
    mVINP_B02, " mVINP_B02 GREEN",
    mVINP_B04, " mVINP_B04 BLACK",
    mVINP_TRIG, " mVINP_TRIG trigger",
    mVINP_LOCK, " mVINP_LOCK barrel lock/load",
    mVINP_OPEN, " mVINP_OPEN barrel open",
    mVINP_PREVLOCK, " mVINP_PREVLOCK barrel prev lock/load",
    mVINP_SOUNDACTV, " mVINP_SOUNDACTV sound"
}; // decodeBits_VinputRBG

// masks for in-process events: wait-for-sound or wait-for-input
//   used (only) in tableRowInProcFlags
//   NOTE: maximum of one of these bits can be set at any time
#define mINPROCFLG_WAITFORSOUND     ((uint16_t)   0x80)  // wait for sound to finish
#define mINPROCFLG_WAITFORINPUT     ((uint16_t)   0x40)  // wait for user input (trigger with perhaps others)
#define mINPROCFLG_WAITFORSOLENOID  ((uint16_t)   0x20)  // wait for timeout on solenoid (special, not directly set in state table)
#define mINPROCFLG_SPCL_IN_PROC     ((uint16_t)  0x100)  // Special is in process; don't process this row at this time
static decodeBits_t decodeBits_inProc[] = {
    mINPROCFLG_WAITFORSOUND, " mINPROCFLG_WAITFORSOUND wait sound finish",
    mINPROCFLG_WAITFORINPUT, " mINPROCFLG_WAITFORINPUT wait input (trigger & perhaps others)",
    mINPROCFLG_WAITFORSOLENOID, " mINPROCFLG_WAITFORSOLENOID wait solenoid timeout",
    mINPROCFLG_SPCL_IN_PROC, " mINPROCFLG_SPCL_IN_PROC Special is in proc"
}; // decodeBits_inProc

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
  { DPIN_AUDIO_BUSY,  mVINP_SOUNDACTV },
};


// STATE TABLE
//  EEPROM[stateTable_ROW->storeAddr] = addr
//  EEPROM[stateTable_ROW->storeVal] = val
// basically there are two possibilities:
//   gotoWithoutInput: play the sound & blink the efctLED then goto when sound done
//   gotoOnInput: wait for input then play the sound & blink the efctLED then goto when sound done
// There can be a "block" of wait for inputs; check each one from mBLOCKSTART to mBLOCKEND
// If the SPECIAL column includes mSPCL_HANDLER then we call our RBGSpecialHandler to do the task
// 
// 
typedef struct _RBGStateTable_t {
    uint16_t blkFlags;         // mBLOCKSTART, mBLOCKEND or mZERO
    uint16_t SPECIAL;          // special row-handling flags: mSPCL_*
    uint16_t efctSound;  // index for sound to makeh
    uint16_t efctLED;           // index for light pattern
    uint16_t inputRBG;         // mask for input expected
    uint16_t storeVal;         // value to store, 8 bit uint
    uint16_t storeAddr;        // address to store; includes mask for mFUNC, mVAL,
                              //   eeSoundSave|mFUNC: idx= 3 WindUp, 2 Shoot, 4 Open, 7 Load
    uint16_t gotoOnInput;      // index within table to go with matching input
    uint16_t gotoWithoutInput; // index within table to go without waiting for input
    uint16_t index;            // input column unused in this table
} RBGStateTable_t;


static struct myState_t {
  uint16_t tableRow = 0;            // points to state that we will process or are processing
  uint16_t tableRowInProcFlags = 0; // what we are waiting on to process this state
  uint16_t VinputRBG = mVINP_PREVLOCK; // bits for input buttons and sound finish: mVINP_*
  uint32_t timerPrev = 0;          // timer from previous time through loop
  uint32_t timerNow = 0;           // timer from this time through loop
  uint32_t timerLed = 0;           // timer for next LED activity
  uint32_t timerSolenoidStart = 0;      // timer for next solenoid OFF
  uint32_t timerSolenoidEnd   = 0;      // timer for next solenoid OFF
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
static RBGStateTable_t myStateTable[11] = {
    { /* row 0 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mNONE, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, .index=mROW_POWERON, },
    { /* row 1 */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_WAITING, .efctLED=mEFCT_UNIQ_WAITING, .inputRBG=mINP_TRIG|mINP_BNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_WINDUP, .gotoWithoutInput=mNONE, .index=mROW_MENU, },
    { /* row 2 */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_WAITING, .efctLED=mEFCT_UNIQ_WAITING, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_OPNBRL, .gotoWithoutInput=mNONE, .index=mROW_MENU, },
    { /* row 3 */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_WAITING, .efctLED=mEFCT_UNIQ_WAITING, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_LOKLOD, .gotoWithoutInput=mNONE, .index=mROW_MENU, },
    { /* row 4 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mNONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_WINDUP_SOUND, .index=mROW_WINDUP, },
    { /* row 5 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mNONE, .efctSound=mEFCT_WIND_UP, .efctLED=mEFCT_WIND_UP, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_SHOOT, .index=mROW_WINDUP_SOUND, },
    { /* row 6 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mNONE, .efctSound=mEFCT_OPEN_BARREL, .efctLED=mEFCT_OPEN_BARREL, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, .index=mROW_OPNBRL, },
    { /* row 7 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mNONE, .efctSound=mEFCT_LOCK_LOAD, .efctLED=mEFCT_LOCK_LOAD, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, .index=mROW_LOKLOD, },
    { /* row 8 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_SHOOT, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_SHOOT_SOUND, .index=mROW_SHOOT, },
    { /* row 9 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mNONE, .efctSound=mEFCT_SHOOT, .efctLED=mEFCT_SHOOT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_SOLENOID, .index=mROW_SHOOT_SOUND, },
    { /* row 10 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_SOLENOID, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, .index=mROW_SOLENOID, },
};
