
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
#define DPIN_BTN_TRIGGER  4  // digital input - the trigger (we only count once per trigger press)
#define DPIN_BTN_YELLOW   5  // digital input - yellow configuration button
#define DPIN_BTN_GREEN    6  // digital input - green configuration button
#define DPIN_BTN_BLACK    7  // digital input - black configuration button
#define DPIN_BTN_BLUE     8  // digital input - blue configuration button
#define DPIN_LOCK_LOAD    9  // digital input - grounded when in lock and load position
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
#define mSPCL_EFCT_NONE       0x8000 // set this bit for no jump and no continuous sound
#define mSPCL_EFCT_ONETIME    0x4000 // set this bit for onetime sound play then jump while waiting for other input or sound end
#define mSPCL_EFCT_CONTINUOUS 0x2000 // set this bit for continuous sound play while waiting for other input
#define mSPCL_EFCT_CONFIGURE  0x1000 // set this bit to use configuration variables instead of EEPROM and do continuous
#define mSPCL_HANDLER         0x0010 // mask for functions is ((uint16_t) (mSPCL_HANDLER-1))
#define mSPCL_HANDLER_SHOOT        2 // solenoid ON
#define mSPCL_HANDLER_SOLENOID     3 // solenoid OFF
#define mSPCL_HANDLER_CFGSTART     4 // configuration - store value at address
#define mSPCL_HANDLER_CFGNEXT      5 // configuration - go to next value at address
#define mSPCL_HANDLER_CFG2STORAGE  6 // configuration - install current config num in EEPROM or myState
// these are used with mSPCL_HANDLER_START and _NEXT
#define mADDR_CFG_CATEGORY         1 // for looping through SOUND or LED PATTERN
#define mADDR_CFG_TYPE             2 // for looping through number groups: shooting, open, close, etc.
#define mADDR_CFG_EFFECT           3 // for looping through the effects for that CATEGORY and TYPE
#define mEFCT_TYPE_CFG_STOREADDR_MAX mADDR_CFG_EFFECT // .storeAddr - maximum value

// define the symbols - .blkFlags:
#define mBLOCKSTART 0x80
#define mBLOCKEND   0x40

#define mROW_POWERON 0  // first address in myStateTable[]
#define mROW_PWRON_OPEN 2
#define mROW_PWRON_LOCKED 4
#define mROW_MENU 7
#define mROW_MENU_OPEN 9
#define mROW_MENU_CLOSED 11
#define mROW_WINDUP_SOUND 15
#define mROW_SHOOT 16
#define mROW_SHOOT_SOUND 17
#define mROW_SOLENOID 18
#define mROW_OPNBRL 19
#define mROW_LOKLOD 21
#define mROW_CFG_MENU 24
#define mROW_CFG_CATEGORY 27
#define mROW_CFG_CATEGORY_LOOPSTART 28
#define mROW_CFG_CATEGORY_LOOP 31
#define mROW_CFG_CATEGORY_NEXT 34
#define mROW_CFG_CATEGORY_CHOICE 35
#define mROW_CFG_TYPE 36
#define mROW_CFG_TYPE_LOOPSTART 37
#define mROW_CFG_TYPE_LOOP 40
#define mROW_CFG_TYPE_NEXT 42
#define mROW_CFG_TYPE_CHOICE 43
#define mROW_CFG_EFFECT 44
#define mROW_CFG_EFFECT_LOOPSTART 45
#define mROW_CFG_EFFECT_LOOP 46
#define mROW_CFG_EFFECT_NEXT 48
#define mROW_CFG_EFFECT_CHOICE 49

// define the effect number ranges - must be divisible by 10
#define mEFCT_WIND_UP       0  // 001 to 009 - wind-up effects
#define mEFCT_SHOOT        10  // 011 to 019 - shoot effects
#define mEFCT_OPEN_BARREL  20  // 021 to 029 - open barrel effects
#define mEFCT_LOCK_LOAD    30  // 031 to 039 - lock and load barrel effects
#define mEFCT_PWRON        40  // 041 to 049 - initial power-up effects
#define mEFCT_WAIT         50  // 051 to 059 - waiting for trigger
#define mEFCT_UNIQ         60  // 061 to 127 - unique effects used to navigate menus or other unique effects

#define mEFCT_LAST_EEP_CONFIG 50  // this is the last EEPROM-configurable set of effects

#define mMASK_EFCT_SND_NUM 255  // mask for sound number
#define mSHIFT_EFCT_SND_VOL 8  // shift for volume
#define mMASK_EFCT_SND_VOL 31   // mask for volume once shifted in place
#define mDEFAULT_EFCT_SND_VOL 25  // default volume - 25 is pretty good

/////////////////// end -> INPUTS 1 FROM makeStateTable.py <- //////////////////////////////////

//
// define the UNIQUE effects (lights and sounds) here. These cannot be configured as the other effects can.
//
#define mEFCT_UNIQ_INTRO               62 // Welcome to FOOF RBG configuration! Your call is important to us. Press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow, Green or Black button then press trigger. To exit configuration, hold down Blue button then press trigger.
#define mEFCT_UNIQ_CFG_CATEGORY        63 // Now choose which effect category: sounds or LED patterns. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow, Green or Black button then press trigger. To exit configuration, hold down Blue button thenpress trigger.
#define mEFCT_UNIQ_CFG_TYPE            64 // Now choose when the effect happens. This list includes when powering-on, when shooting, etc. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow, Green or Black button then press trigger. To exit configuration, hold down Blue button thenpress trigger.
#define mEFCT_UNIQ_CFG_EFECT           65 // Now choose the effect itself. This list cycles through the effects one by one. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow, Green or Black button then press trigger. To exit configuration, hold down Blue button thenpress trigger.
#define mEFCT_UNIQ_CFG_WINDUP_DESCRIP  71 // Effect happens during wind-up to shooting
#define mEFCT_UNIQ_CFG_SHOOT_DESCRIP   72 // Effect happens during shooting itself
#define mEFCT_UNIQ_CFG_OPEN_DESCRIP    73 // Effect happens during opening of the barrel
#define mEFCT_UNIQ_CFG_LKLOD_DESCRIP   74 // Effect happens during lock-and-load of the barrel
#define mEFCT_UNIQ_CFG_PWRON_DESCRIP   75 // Effect happens during initial power-on
#define mEFCT_UNIQ_CFG_WAIT_DESCRIP    76 // Effect happens when waiting to shoot


#define mEFCT_UNIQ_SILENCE            101 // silence
#define mEFCT_UNIQ_NOT_IMPL           102 // Not yet implemented

// EEPROM addresses
// EEPROM[eeSoundSave+idx] idx: 0 WindUp, 1 Shoot, 2 Open, 3 Load, 4 PowerUp, 8 Configure
#define eeSoundSave 0x0000 // EEPROM starting address for sound configuration
#define eeLEDSave   0x0010 // EEPROM starting address for LED pattern configuration
#define eeLastNonChksum  0x1E // EEPROM address of last non-checksum data
#define eeInvertedChksum 0x1F // EEPROM address of checksum data

#define EEPOFFSET(parm)   ((uint16_t) (parm / 10)) // example: EEPOFFSET(mEFCT_SHOOT) = 1
#define EFCT_IS_EEP(parm) (0 == ((uint16_t) parm) % 10) // if (EFCT_IS_EEP(mEFCT_PWRON)) will be true


typedef struct _decodeBits_t { uint16_t theBit; const char * theText; } decodeBits_t;

// masks for input detections: button, trigger, sound module, and barrel states and state changes
//   used (only) in .inputRBG in myStateTable and in code to examine that
#define mINP_B01   0x0001      // mask for DPIN_BTN_YELLOW
#define mINP_B02   0x0002      // mask for DPIN_BTN_GREEN
#define mINP_B03   0x0003      // mask for DPIN_BTN_YELLOW, DPIN_BTN_GREEN
#define mINP_B04   0x0004      // mask for DPIN_BTN_BLACK
#define mINP_B05   0x0005      // mask for DPIN_BTN_YELLOW, DPIN_BTN_BLACK
#define mINP_B06   0x0006      // mask for DPIN_BTN_GREEN, DPIN_BTN_BLACK
#define mINP_B07   0x0007      // mask for DPIN_BTN_YELLOW, DPIN_BTN_GREEN, DPIN_BTN_BLACK
#define mINP_B08   0x0008      // mask for DPIN_BTN_BLUE
#define mINP_B0F   0x000F      // mask for DPIN_BTN_YELLOW, DPIN_BTN_GREEN, DPIN_BTN_BLACK, DPIN_BTN_BLUE
#define mINP_YELLOW mINP_B01   // mask for DPIN_BTN_YELLOW
#define mINP_GREEN  mINP_B02   // mask for DPIN_BTN_GREEN
#define mINP_BLACK  mINP_B04   // mask for DPIN_BTN_BLACK
#define mINP_BLUE   mINP_B08   // mask for DPIN_BTN_BLUE
#define mINP_BANY  0x0010      // mask for any of the specified DPIN_BTN_{BYGX} combination but at least one other than trigger
#define mINP_TRIG  0x0040      // mask for just depressed the trigger (edge detect)
#define mINP_LOCK  0x0100      // mask for just connected the barrel
#define mINP_OPEN  0x0200      // mask for just disconnected the barrel

// masks for input values: button, trigger, sound module, and barrel states and state changes
//   used (only) in .VinputRBG in myState
#define mVINP_B01   0x0001     // mask for DPIN_BTN_YELLOW (currently depressed)
#define mVINP_B02   0x0002     // mask for DPIN_BTN_GREEN (currently depressed)
#define mVINP_B04   0x0004     // mask for DPIN_BTN_BLACK (currently depressed)
#define mVINP_BLUE 0x0008     // mask for DPIN_BTN_BLUE (currently depressed)
#define mVINP_TRIG  0x0020     // mask for just depressed the trigger
#define mVINP_LOCK  0x0100     // mask for barrel connected
#define mVINP_OPEN  0x0200     // mask for barrel disconnected
#define mVINP_SOUNDACTV  0x0400 // mask for sound was active last time we checked- twiddled by SW
#define mVINP_TRUESOUNDACTV  0x4000 // TRUE mask for hardware sound was active last time we checked
#define mDELAY_SOUNDACTV 250    // milliseconds to keep SW twiddled sound active after doing myDFPlayer.play(mySound)
static decodeBits_t decodeBits_VinputRBG[] = {
    mVINP_B01, " mVINP_B01 YELLOW",
    mVINP_B02, " mVINP_B02 GREEN",
    mVINP_B04, " mVINP_B04 BLACK",
    mVINP_BLUE, " mVINP_B08 BLUE",
    mVINP_TRIG, " mVINP_TRIG trigger",
    mVINP_LOCK, " mVINP_LOCK barrel lock/load",
    mVINP_OPEN, " mVINP_OPEN barrel open",
    mVINP_SOUNDACTV, " mVINP_SOUNDACTV sound SW",
    mVINP_TRUESOUNDACTV, " mVINP_TRUESOUNDACTV sound HW"
}; // decodeBits_VinputRBG

// table to identify input pins and corresponding masks
// DPIN_LOCK_LOAD handled separately in code
// the masks are used (only) in .VinputRBG in myState
typedef struct _pins_to_vals_t {
  uint16_t pin; uint16_t val;
} pins_to_vals_t;
static pins_to_vals_t myPinsToVals[] = {
  { DPIN_BTN_YELLOW,  mVINP_B01 },
  { DPIN_BTN_GREEN,   mVINP_B02 },
  { DPIN_BTN_BLACK,   mVINP_B04 },
  { DPIN_BTN_BLUE,   mVINP_BLUE },
  { DPIN_AUDIO_BUSY,  mVINP_SOUNDACTV },
  { DPIN_AUDIO_BUSY,  mVINP_TRUESOUNDACTV },
};

static struct _myState_t {
  uint16_t tableRow = 0;            // points to state that we will process or are processing
  uint16_t VinputRBG = 0;           // bits for input buttons and sound finish: mVINP_*
  uint16_t currVolume = 0;          // avoid sending volume when not needed - FIXME FUTURE FEATURE
  uint32_t timerNow = 0;            // timer now
  uint32_t timerPrevState = 0;      // start timer from previous time through state loop
  uint32_t timerPrevLEDstep = 0;    // start timer from previous LED activity
  uint32_t timerForceSoundActv = 0; // end timer for forcing mVINP_SOUNDACTV true
  uint32_t timerForceSolenoidLow = 0; // end timer for forcing mVINP_SOUNDACTV true
  uint8_t ptrnDelayLEDstep = 7;     // proper delta delay for Mark's patterns
  uint8_t cfg_curnum = mNONE;       // current number for configuration list of choices
  uint8_t cfg_maxnum = mNONE;       // maximum number for configuration list of choices
  uint8_t cfg_category = mNONE;     // either 1 = SOUND or 2 = LED Pattern - used to tell sounds when configuring LEDs
  uint8_t cfg_category2save = mNONE;// either 1 = SOUND or 2 = LED Pattern
  uint8_t cfg_type = mNONE;         // example: mEFCT_LOCK_LOAD
  uint8_t cfg_type2save = mNONE;    // example: mEFCT_LOCK_LOAD
  uint8_t cfg_addr = mNONE;         // code: mADDR_CFG_CATEGORY, mADDR_CFG_TYPE, mADDR_CFG_EFFECT
} myState;
#define mCFG_CATEGORY_SOUND   1 // for myState.cfg_category
#define mCFG_CATEGORY_LEDPTRN 2 // for myState.cfg_category
#define mCFG_CATEGORY_MAXNUM  mCFG_CATEGORY_LEDPTRN // for myState.cfg_category
// apparently no doubly dimensioned arrays for Arduino
static uint8_t cfgMaxSoundForType[EEPOFFSET(mEFCT_UNIQ)] = {
  6, 9, 6, 6, 3, 8 // sound - mEFCT_WIND_UP mEFCT_SHOOT mEFCT_OPEN_BARREL mEFCT_LOCK_LOAD mEFCT_PWRON mEFCT_WAIT
};
static uint8_t cfgMaxLEDForType[EEPOFFSET(mEFCT_UNIQ)] = {
  3, 3, 3, 3, 3, 3 // LED - mEFCT_WIND_UP mEFCT_SHOOT mEFCT_OPEN_BARREL mEFCT_LOCK_LOAD mEFCT_PWRON mEFCT_WAIT
}; // end theMaxForCategType[]

#define DLYSOLENOID 200  // num milliseconds to leave solenoid on

#define DLYLED_MIN 7
#define PTRNLED_OFF 258
// #define PTRNLED_diskDownTheDrain_rot 1
// #define PTRNLED_diskDownTheDrain_blk 2
#define PTRNLED_pwron1    (1+mEFCT_PWRON)
#define PTRNLED_open1     (1+mEFCT_OPEN_BARREL)
#define PTRNLED_lock1     (1+mEFCT_LOCK_LOAD)
#define PTRNLED_wait1     (1+mEFCT_WAIT)
#define PTRNLED_windup1   (1+mEFCT_WIND_UP)
#define PTRNLED_shoot1    (1+mEFCT_SHOOT)
#define PTRNLED_uniq1     (1+mEFCT_UNIQ)

#define DLYLED_ringRotateAndFade 25 // for RBG_ringRotateAndFade
#define DLYLED_diskDownTheDrain 25 // for RBG_DiskDownTheDrain



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
    uint16_t efctSound;        // index for sound to make | (loud << mSHIFT_EFCT_SND_VOL) | masks
    uint16_t efctLED;          // index for light pattern
    uint16_t inputRBG;         // mask for input expected
    uint16_t storeVal;         // value to store, 8 bit uint
    uint16_t storeAddr;        // address to store; includes mask for mFUNC, mVAL,
                               //   eeSoundSave|mFUNC: idx= 3 WindUp, 2 Shoot, 4 Open, 7 Load
    uint16_t gotoOnInput;      // index within table to go with matching input
    uint16_t gotoWithoutInput; // index within table to go without waiting for input
    // uint16_t index;            // input column unused in this table
} RBGStateTable_t;

//
// the state table itself - automatically generated from makeStateTable.py
//
static const RBGStateTable_t myStateTable[50]
#if USE_PROGMEM
  PROGMEM
#endif // end USE_PROGMEM
  = {
      { /* row 0 mROW_POWERON */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_PWRON_OPEN, .gotoWithoutInput=mNONE, },
      { /* row 1 mROW_POWERON */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_PWRON_LOCKED, .gotoWithoutInput=mNONE, },
      { /* row 2 mROW_PWRON_OPEN */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, },
      { /* row 3 mROW_PWRON_OPEN */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B0F, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_MENU, .gotoWithoutInput=mNONE, },
      { /* row 4 mROW_PWRON_LOCKED */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, },
      { /* row 5 mROW_PWRON_LOCKED */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_WINDUP_SOUND, .gotoWithoutInput=mNONE, },
      { /* row 6 mROW_PWRON_LOCKED */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B0F, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_MENU, .gotoWithoutInput=mNONE, },
      { /* row 7 mROW_MENU */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_MENU_OPEN, .gotoWithoutInput=mNONE, },
      { /* row 8 mROW_MENU */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_MENU_CLOSED, .gotoWithoutInput=mNONE, },
      { /* row 9 mROW_MENU_OPEN */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_WINDUP_SOUND, .gotoWithoutInput=mNONE, },
      { /* row 10 mROW_MENU_OPEN */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_LOKLOD, .gotoWithoutInput=mNONE, },
      { /* row 11 mROW_MENU_CLOSED */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B0F, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_MENU, .gotoWithoutInput=mNONE, },
      { /* row 12 mROW_MENU_CLOSED */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_WINDUP_SOUND, .gotoWithoutInput=mNONE, },
      { /* row 13 mROW_MENU_CLOSED */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_OPNBRL, .gotoWithoutInput=mNONE, },
      { /* row 14 mROW_MENU_CLOSED */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B0F, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_MENU, .gotoWithoutInput=mNONE, },
      { /* row 15 mROW_WINDUP_SOUND */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_WIND_UP, .efctLED=mEFCT_WIND_UP, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_SHOOT, },
      { /* row 16 mROW_SHOOT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_SHOOT | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_SHOOT_SOUND, },
      { /* row 17 mROW_SHOOT_SOUND */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_SHOOT, .efctLED=mEFCT_SHOOT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_SOLENOID, },
      { /* row 18 mROW_SOLENOID */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_SOLENOID | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, },
      { /* row 19 mROW_OPNBRL */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_OPEN_BARREL, .efctLED=mEFCT_OPEN_BARREL, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, },
      { /* row 20 mROW_OPNBRL */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_OPEN_BARREL, .efctLED=mEFCT_OPEN_BARREL, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_LOKLOD, .gotoWithoutInput=mNONE, },
      { /* row 21 mROW_LOKLOD */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_LOCK_LOAD, .efctLED=mEFCT_LOCK_LOAD, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, },
      { /* row 22 mROW_LOKLOD */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_LOCK_LOAD, .efctLED=mEFCT_LOCK_LOAD, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_OPNBRL, .gotoWithoutInput=mNONE, },
      { /* row 23 mROW_LOKLOD */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_LOCK_LOAD, .efctLED=mEFCT_LOCK_LOAD, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_WINDUP_SOUND, .gotoWithoutInput=mNONE, },
      { /* row 24 mROW_CFG_MENU */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_INTRO, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY, .gotoWithoutInput=mNONE, },
      { /* row 25 mROW_CFG_MENU */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_INTRO, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B07, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY, .gotoWithoutInput=mNONE, },
      { /* row 26 mROW_CFG_MENU */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_INTRO, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BLUE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_MENU, .gotoWithoutInput=mNONE, },
      { /* row 27 mROW_CFG_CATEGORY */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGSTART | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=0.0, .storeAddr=mADDR_CFG_CATEGORY, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_CATEGORY_LOOPSTART, },
      { /* row 28 mROW_CFG_CATEGORY_LOOPSTART */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_CATEGORY, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 29 mROW_CFG_CATEGORY_LOOPSTART */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_CATEGORY, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B07, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 30 mROW_CFG_CATEGORY_LOOPSTART */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_CATEGORY, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BLUE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_MENU, .gotoWithoutInput=mNONE, },
      { /* row 31 mROW_CFG_CATEGORY_LOOP */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY_NEXT, .gotoWithoutInput=mNONE, },
      { /* row 32 mROW_CFG_CATEGORY_LOOP */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B07, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY_CHOICE, .gotoWithoutInput=mNONE, },
      { /* row 33 mROW_CFG_CATEGORY_LOOP */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG|mINP_BLUE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_MENU, .gotoWithoutInput=mNONE, },
      { /* row 34 mROW_CFG_CATEGORY_NEXT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGNEXT | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_CATEGORY_LOOP, },
      { /* row 35 mROW_CFG_CATEGORY_CHOICE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFG2STORAGE | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_TYPE, },
      { /* row 36 mROW_CFG_TYPE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGSTART | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=0.0, .storeAddr=mADDR_CFG_TYPE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_TYPE_LOOPSTART, },
      { /* row 37 mROW_CFG_TYPE_LOOPSTART */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_TYPE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_TYPE_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 38 mROW_CFG_TYPE_LOOPSTART */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_TYPE, .efctLED=mEFCT_WAIT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mNONE, },
      { /* row 39 mROW_CFG_TYPE_LOOPSTART */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_TYPE, .efctLED=mEFCT_WAIT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mNONE, },
      { /* row 40 mROW_CFG_TYPE_LOOP */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_TYPE_NEXT, .gotoWithoutInput=mNONE, },
      { /* row 41 mROW_CFG_TYPE_LOOP */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B07, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_TYPE_CHOICE, .gotoWithoutInput=mNONE, },
      { /* row 42 mROW_CFG_TYPE_NEXT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGNEXT | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_TYPE_LOOP, },
      { /* row 43 mROW_CFG_TYPE_CHOICE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFG2STORAGE | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_EFFECT, },
      { /* row 44 mROW_CFG_EFFECT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGSTART | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=0.0, .storeAddr=mADDR_CFG_EFFECT, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_EFFECT_LOOPSTART, },
      { /* row 45 mROW_CFG_EFFECT_LOOPSTART */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_EFECT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_EFFECT_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 46 mROW_CFG_EFFECT_LOOP */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_EFFECT_NEXT, .gotoWithoutInput=mNONE, },
      { /* row 47 mROW_CFG_EFFECT_LOOP */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B07, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_EFFECT_CHOICE, .gotoWithoutInput=mNONE, },
      { /* row 48 mROW_CFG_EFFECT_NEXT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGNEXT | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_EFFECT_LOOP, },
      { /* row 49 mROW_CFG_EFFECT_CHOICE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFG2STORAGE | mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_MENU, },
}; // end definition of myStateTable[]
