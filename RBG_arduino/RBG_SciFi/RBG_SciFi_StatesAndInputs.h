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
// This file has definitions for state tables and input processing (mostly buttons)
//

#define NUMOF(x) (sizeof((x)) / sizeof((*x)))

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
} // returns -1, 0, 1 for (T < 0), (T == 0), (T > 0) respectively. returns warning if used on uintx_t

#define DPIN_FASTLED_SNGL 2  // serial out - talk to single LED in handle
#define NO_FASTLED_SNGL   0  // 1=do not actually write to pin 2, 0=normal

#define DPIN_FASTLED      3  // serial out - talk to LED rings
#define DPIN_BTN_TRIGGER  4  // digital input - the trigger (we only count once per trigger press)
#define DPIN_BTN_YELLOW   5  // digital input - yellow configuration button
#define DPIN_BTN_GREEN    6  // digital input - green configuration button
#define DPIN_BTN_RED      7  // digital input - blue configuration button
#define DPIN_LOCK_LOAD    8  // digital input - grounded when in lock and load position
#define DPIN_UNUSED       9  // digital input - pair the BlueTooth Audio Transmitter
#define DPIN_SWSRL_RX    10  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_TX    11  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY  12  // digital input - signals when audio finishes
#define DPIN_SOLENOID    13  // often has internal LED and resistor soldered to board, can make INPUT not work


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
#define mSPCL_HANDLER         0x0080 // mask for functions is ((uint16_t) (mSPCL_HANDLER-1))
#define mSPCL_HANDLER_SHOOT        2 // solenoid ON
#define mSPCL_HANDLER_SOLENOID     3 // solenoid OFF
#define mSPCL_HANDLER_CFGSTART     4 // configuration - store value at address
#define mSPCL_HANDLER_CFGNEXT      5 // configuration - go to next value at address
#define mSPCL_HANDLER_CFG2STORAGE  6 // configuration - install current config num in EEPROM or myState
#define mSPCL_HANDLER_CFG2STORAGESKIP 7 // configuration - store current config num in EEPROM or myState, skip number based on choice
#define mSPCL_HANDLER_CFG2CPYRST   8 // configuration - use current config num to manage EEPROM with copy or reset, then clear out configuration states
#define mSPCL_HANDLER_FACT2RUN     9 // configuration - factory setting to running configuration
#define mSPCL_HANDLER_FACT2ALL    10 // configuration - factory setting to all saved configuration
#define mSPCL_HANDLER_RUN2ONE     11 // configuration - running configuration to saved config one
#define mSPCL_HANDLER_RUN2TWO     12 // configuration - running configuration to saved config 
#define mSPCL_HANDLER_RUN2THREE   13 // configuration - running configuration to saved config 
#define mSPCL_HANDLER_ONE2RUN     14 // configuration - saved configuration one to running config
#define mSPCL_HANDLER_TWO2RUN     15 // configuration - saved configuration two to running config
#define mSPCL_HANDLER_THREE2RUN   16 // configuration - saved configuration three to running config
#define mSPCL_HANDLER_CFG2ADVNCD  17 // configuration - advanced menu: the selection/skip function
#define mSPCL_HANDLER_STATICMODE  18 // configuration - advanced menu: static-mode
#define mSPCL_HANDLER_ADVFEATURES 19 // configuration - advanced menu: ADVANCED features

// these are used with mSPCL_HANDLER_START and _NEXT
#define mADDR_CFG_CATEGORY         1 // for looping through SOUND or LED PATTERN
#define mADDR_CFG_TYPE             2 // for looping through number groups: shooting, open, close, etc.
#define mADDR_CFG_EFFECT           3 // for looping through the effects for that CATEGORY and TYPE
#define mADDR_CFG_CPY_RST          4 // configuration copies and factory resets
#define mADDR_CFG_ADVANCED         5 // advanced configuration
#define mEFCT_TYPE_CFG_STOREADDR_MAX mADDR_CFG_ADVANCED // .storeAddr - maximum value

// define the symbols - .blkFlags:
#define mBLOCKSTART 0x80
#define mBLOCKEND   0x40

// define the symbols - .index: first the single constant mROW_POWERON one, then the others:
#define mROW_POWERON 0  // first address in myStateTable[]
#define mROW_PWRON_OPEN 2
#define mROW_PWRON_LOCKED 4
#define mROW_MENU 7
#define mROW_MENU_OPEN 9
#define mROW_MENU_CLOSED 12
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
#define mROW_CFG_TYPE 40
#define mROW_CFG_TYPE_LOOPSTART 41
#define mROW_CFG_TYPE_LOOP 44
#define mROW_CFG_TYPE_NEXT 47
#define mROW_CFG_TYPE_CHOICE 48
#define mROW_CFG_EFFECT 49
#define mROW_CFG_EFFECT_LOOPSTART 50
#define mROW_CFG_EFFECT_LOOP 51
#define mROW_CFG_EFFECT_NEXT 54
#define mROW_CFG_EFFECT_CHOICE 55
#define mROW_CFG_ACCEPTED 56
#define mROW_CFG_CPY_RST 58
#define mROW_CFG_CPY_RST_LOOPSTART 59
#define mROW_CFG_CPY_RST_LOOP 60
#define mROW_CFG_CPY_RST_NEXT 63
#define mROW_CFG_CPY_RST_CHOICE 64
#define mROW_CPY_RST_ACCEPTED 73
#define mROW_CFG_ADVANCED 75
#define mROW_CFG_ADVNCD_LOOPSTART 76
#define mROW_CFG_ADVNCD_LOOP 77
#define mROW_CFG_ADVNCD_NEXT 80
#define mROW_CFG_ADVNCD_CHOICE 81
#define mROW_ADVNCD_STATIC_ACCEPTED 85
#define mROW_ADVNCD_PASSWD_VERBAL 87
#define mROW_ADVNCD_PASSWD_DANCE 88
#define mROW_ADVNCD_PASSWD_NOPASSWD 89

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
#define mDEFAULT_EFCT_SND_VOL 30  // default volume - 25 is pretty good

/////////////////// end -> INPUTS 1 FROM makeStateTable.py <- //////////////////////////////////

//
// Storage of configuration into EEPROM
//    EEPROM gets copied to RAM to facilitate cycling through EEPROM configurations
//
// In STATIC mode (myState.dynamicMode == mNONE)there are four possible .dynamicMode configurations:
//    0: running configuration
//    1: saved auxilliary configuration 1
//    2: saved auxilliary configuration 2
//    3: saved auxilliary configuration 3
// In DYNAMIC mode (myState.dynamicMode == mNONE) we cycle through all four 
// There is a factory configuration for each of the EEPROM configurations
#define EEPROM_PROCESS_ALL_CONFIG 0x20 // really it is just an arbitrary number
#define EEPROM_CONFIG_RUNNING        0 //
#define EEPROM_SAVED_ONE             1 //
#define EEPROM_SAVED_TWO             2 //
#define EEPROM_SAVED_THREE           3 //
#define EEPROM_SAVED_FIRST EEPROM_SAVED_ONE   //
#define EEPROM_SAVED_LAST  EEPROM_SAVED_THREE //
#define NUM_EEPROM_CONFIGURATIONS    4   // total number of EEPROM configurations: 0 to 3
//
// At this time, the EEPROM configurations implement choices for the effects: SOUNDS or LED PATTERNS.
//       FIXME - I am reserving EEPROM_VOLUME_CONFIG for later volume configuration
//    The choices for effects are in ranges of 10 decimal (example: mEFCT_SHOOT is 10, but choices of shoot must be 11 <= choice <= 19)
//    These #defs will convert or test these ranges
#define EEPOFFSET(parm)   ((uint16_t) (parm / 10)) // example: EEPOFFSET(mEFCT_SHOOT) = 1
#define EFCT_TYPE_OFFSET(parm) (((uint16_t) parm) % 10) // offset from the type (which is multiple of 10). example: EFCT_TYPE_OFFSET(91) = 1
#define EFCT_IS_EEP(parm) (0 == EFCT_TYPE_OFFSET(parm)) // if (EFCT_IS_EEP(mEFCT_PWRON)) will be true
//
// EEPROM addresses within a single configuration
// EEPROM[EEPROM_START_SOUND_CONFIGS+idx] idx: 0 WindUp, 1 Shoot, 2 Open, 3 Load, 4 PowerUp, 5 Wait
// EEPROM[EEPROM_START_LED_CONFIGS  +idx] idx: 0 WindUp, 1 Shoot, 2 Open, 3 Load, 4 PowerUp, 5 Wait
// EEPROM[EEPROM_INVERTED_CHKSM] is checksum byte
//
// Important global offsets within a single configuration
//
#define EEPROM_START_SOUND_CONFIGS    0x0000 // EEPROM starting address for sound configuration
#define EEPROM_VOLUME_CONFIG          0x000e // EEPROM address for volume default FIXME not implemented
#define EEPROM_START_LED_CONFIGS      0x0010 // EEPROM starting address for LED pattern configuration
#define EEPROM_LAST_NON_CHKSM           0x1E // EEPROM address of last non-checksum data
#define EEPROM_INVERTED_CHKSM           0x1F // EEPROM address of checksum data
#define EEPROM_BYTES_PER_CONFIG (EEPROM_INVERTED_CHKSM+1)
#define NUM_EEPROM_EFFECT_TYPES (1 + EEPOFFSET(mEFCT_LAST_EEP_CONFIG)) // at this time, total of six EEPROM configurable effect types

//
// RAM copy of EEPROM settings; these are the active ones right now
//
static uint8_t EEPROM_RAMcopy[EEPROM_BYTES_PER_CONFIG];
//
// Factory Settings: see tab "FactorySettings" in StateTable_minimal.xlsx
static const uint8_t factory_effect_configs[NUM_EEPROM_CONFIGURATIONS*EEPROM_BYTES_PER_CONFIG]
#if USE_PROGMEM
  PROGMEM
#endif // end USE_PROGMEM
  = {
/* 0 SOUND */    1, 1, 7, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, mDEFAULT_EFCT_SND_VOL, 1, // EEPROM_VOLUME_CONFIG is 0x000e FIXME not implemented 
/* 0 LED PTRN */ 3, 1, 5, 1, 1, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
/* 1 SOUND */    4, 4, 5, 4, 2, 9, 1, 1, 1, 1, 1, 1, 1, 1, mDEFAULT_EFCT_SND_VOL, 1, // EEPROM_VOLUME_CONFIG is 0x000e FIXME not implemented
/* 1 LED PTRN */ 6, 2, 4, 6, 2, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
/* 2 SOUND */    5, 7, 4, 5, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, mDEFAULT_EFCT_SND_VOL, 1, // EEPROM_VOLUME_CONFIG is 0x000e FIXME not implemented
/* 2 LED PTRN */ 1, 3, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
/* 3 SOUND */    3, 2, 3, 6, 4, 6, 1, 1, 1, 1, 1, 1, 1, 1, mDEFAULT_EFCT_SND_VOL, 1, // EEPROM_VOLUME_CONFIG is 0x000e FIXME not implemented
/* 3 LED PTRN */ 5, 8, 6, 2, 7, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

//
// we don't really need  ALL these definitions since the ones below 60 are a configurable sounds
//
#define mEFCT_PWRON_LFOOF                41 // This is the awesome FOOF Rubber Band Gun, darling.
#define mEFCT_PWRON_MFOOF                42 // This is the awesome FOOF Rubber Band Gun.
#define mEFCT_PWRON_CFOOF                43 // Achtung! This is the awesome FOOF Rubber Band Gun.
#define mEFCT_PWRON_RFOOF                44 // This is the awesome FOOF Rubber Band Gun. Be afraid.

//
// define the UNIQUE effects (lights and sounds) here. These cannot be configured as the other effects can.
//
#define mEFCT_UNIQ_INTRO                62 // Welcome to the FOOF Rubber Band Gun configuration! Your call is important to us. Press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_CATEGORY         63 // Now choose which configuration category: sound effects, LED pattern effects, configuration resets and copying, or advanced settings. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_TYPE             64 // Now choose when the effect happens. This list includes when powering-on, when shooting, etc. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_EFFECT           65 // Now choose the effect itself. This list cycles through the effects one by one. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_LED2CHOOSE       66 // This is an LED pattern you can choose. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_ACCEPT           67 // Your choice has been saved into the running settings.
#define mEFCT_UNIQ_NOT_IMPL             68 // This feature is not yet implemented.
#define mEFCT_UNIQ_SILENCE              69 // silence

#define mEFCT_UNIQ_CFG_WINDUP_DESCRIP   71 // The effect happens during wind-up to shooting
#define mEFCT_UNIQ_CFG_SHOOT_DESCRIP    72 // The effect happens during shooting itself
#define mEFCT_UNIQ_CFG_OPEN_DESCRIP     73 // The effect happens during opening of the barrel
#define mEFCT_UNIQ_CFG_LKLOD_DESCRIP    74 // The effect happens during lock-and-load of the barrel
#define mEFCT_UNIQ_CFG_PWRON_DESCRIP    75 // The effect happens during initial power-on
#define mEFCT_UNIQ_CFG_WAIT_DESCRIP     76 // The effect happens when waiting to shoot

#define mEFCT_UNIQ_CFG_SOUNDS_DESCRIP     81 // The category is SOUNDS.
#define mEFCT_UNIQ_CFG_LEDPTRN_DESCRIP    82 // The category is L. E. D. PATTERNS.
#define mEFCT_UNIQ_CFG_CPY_RST_DESCRIP    83 // The category is configuration resets and copying.
#define mEFCT_UNIQ_CFG_ADVANCED_DESCRIP   84 // The category is advanced settings.

#define mEFCT_UNIQ_CFG_ENTER_PASSWORD     86 // Please state password loudly, then press trigger.
#define mEFCT_UNIQ_CFG_ENTER_DANCE        87 // I could not understand your password, please enter password by interpretive dance, then press trigger.
#define mEFCT_UNIQ_CFG_SORRY_NO_PASSWORD  88 // Sorry, I don't have a password, but you dance very well. Please press trigger.
#define mEFCT_UNIQ_CFG_CREDITS            89 // The FOOF Science Fiction Rubber Band Gun was originally conceived by Mark and Keith. The hardware implementation was designed and built by Jim. The software and most of the sounds were generated by Mark. Some build information is at Git Hub dot Com slash Mark Dash Em Dee Oh Forty Seven dot Com slash Rubber Band Gun. Some sounds are recordings of Mark's family. Many of the Sci Fi sounds are transmogrified versions of Creative Commons sounds stored on Free Sound dot Org. Other Sci Fi sounds originated from El Eye Gee Oh gravity wave detections of stellar events found at Gee Double You Dash Open Science dot Org slash Audio Gee Double You Tee See One. The robotic voice sounds were generated using the eSpeak speech to text program found on eSpeak dot Source Forge dot net. See the Git Hub page for more attributions.

#define mEFCT_UNIQ_CFG_MGMT_01            91 // Erase the running setting only and reset the running setting to the factory settings. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_MGMT_02            92 // Erase the running setting and erase all saved auxilliary settings and reset to the factory settings. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_MGMT_03            93 // Copy the running setting and overwrite into saved auxilliary setting number one. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_MGMT_04            94 // Copy the running setting and overwrite into saved auxilliary setting number two. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_MGMT_05            95 // Copy the running setting and overwrite into saved auxilliary setting number three. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_MGMT_06            96 // Copy the saved auxilliary setting number one and overwrite into the running setting. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_MGMT_07            97 // Copy the saved auxilliary setting number two and overwrite into the running setting. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_MGMT_08            98 // Copy the saved auxilliary setting number three and overwrite into the running setting. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.

#define mEFCT_UNIQ_CFG_ADVANCED_01       101 // Static mode: Don't switch through the saved configurations each time you shoot. Power cycle to exit Static mode. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_ADVANCED_02       102 // Enable time travel and teleportation capabilities (requires password). As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_ADVANCED_03       103 // Hear Rubber Band Gun credits. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.

#define mEFCT_UNIQ_CFG_ADVANCED          106 // Now choose which ADVANCED configuration category: Static Mode, Time Travel and Teleportation, or Credits. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_STATIC_STARTED    107 // Static mode started. Power cycle to exit static mode.
#define mEFCT_UNIQ_CFG_CPY_RST           108 // Now choose the, factory reset, or, configuration, copy, option. This list cycles through the options one by one. As always, press trigger by itself to go forward to next step or to cycle through choices. To select a choice, first hold down any combination of Yellow or Green button then press trigger. To exit configuration, hold down Red button then press trigger.
#define mEFCT_UNIQ_CFG_CPY_RST_ACCEPT    109 // Your, factory reset, or, configuration copy, option, has been accepted. Rebooting.


typedef struct _decodeBits_t { uint16_t theBit; const char * theText; } decodeBits_t;

// masks for input detections: button, trigger, sound module, and barrel states and state changes
//   used (only) in .inputRBG in myStateTable and in code to examine that
#define mINP_B01   0x0001      // mask for DPIN_BTN_YELLOW
#define mINP_B02   0x0002      // mask for DPIN_BTN_GREEN
#define mINP_B03   0x0003      // mask for DPIN_BTN_YELLOW, DPIN_BTN_GREEN
#define mINP_B04   0x0004      // mask for DPIN_BTN_RED
#define mINP_B05   0x0005      // mask for DPIN_BTN_YELLOW, DPIN_BTN_RED
#define mINP_B06   0x0006      // mask for DPIN_BTN_GREEN, DPIN_BTN_RED
#define mINP_B07   0x0007      // mask for DPIN_BTN_YELLOW, DPIN_BTN_GREEN, DPIN_BTN_RED
#define mINP_YELLOW mINP_B01   // mask for DPIN_BTN_YELLOW
#define mINP_GREEN  mINP_B02   // mask for DPIN_BTN_GREEN
#define mINP_RED    mINP_B04   // mask for DPIN_BTN_RED
#define mINP_BANY  0x0010      // mask for any of the specified DPIN_BTN_{YR} combination but at least one other than trigger
#define mINP_TRIG  0x0040      // mask for just depressed the trigger (edge detect)
#define mINP_LOCK  0x0100      // mask for just connected the barrel
#define mINP_OPEN  0x0200      // mask for just disconnected the barrel

// masks for input values: button, trigger, sound module, and barrel states and state changes
//   used (only) in .VinputRBG in myState
#define mVINP_B01   0x0001      // mask for DPIN_BTN_YELLOW (currently depressed)
#define mVINP_B02   0x0002      // mask for DPIN_BTN_GREEN (currently depressed)
#define mVINP_B04   0x0004      // mask for DPIN_BTN_RED (currently depressed)
#define mVINP_TRIG_EDGE  0x0040 // mask for just depressed the trigger
#define mVINP_LOCK  0x0100      // mask for barrel connected
#define mVINP_OPEN  0x0200      // mask for barrel disconnected
#define mVINP_SOUNDACTV  0x0400 // mask for sound was active last time we checked- twiddled by SW
#define mVINP_TRIG_STATE 0x2000 // TRUE if trigger is down, FALSE if trigger is up
#define mVINP_TRUESOUNDACTV  0x4000 // TRUE mask for hardware sound was active last time we checked
#define mDELAY_SOUNDACTV 250    // milliseconds to keep SW twiddled sound active after doing myDFPlayer.play(mySound)
static decodeBits_t decodeBits_VinputRBG[] = {
    mVINP_B01,           " mVINP_B01 YELLOW",
    mVINP_B02,           " mVINP_B02 GREEN",
    mVINP_B04,           " mVINP_B04 RED",
    mVINP_TRIG_EDGE,     " mVINP_TRIG_EDGE trigger, handled in SW",
    mVINP_TRIG_STATE,    " mVINP_TRIG_STATE trigger 1=pressed",
    mVINP_LOCK,          " mVINP_LOCK barrel lock/load",
    mVINP_OPEN,          " mVINP_OPEN barrel open",
    mVINP_SOUNDACTV,     " mVINP_SOUNDACTV sound SW",
    mVINP_TRUESOUNDACTV, " mVINP_TRUESOUNDACTV sound HW"
}; // decodeBits_VinputRBG

// table to identify input pins and corresponding masks
// DPIN_LOCK_LOAD->mVINP_LOCK|mVINP_OPEN handled separately in code in getButtonInput()
// DPIN_BTN_TRIGGER->mVINP_TRIG_EDGE (edge detect) handled separately in code in getButtonInput()
// the masks are used (only) in .VinputRBG in myState
typedef struct _pins_to_vals_t {
  uint16_t pin; uint16_t val;
} pins_to_vals_t;
static pins_to_vals_t myPinsToVals[] = {
  { DPIN_BTN_YELLOW,  mVINP_B01 },
  { DPIN_BTN_GREEN,   mVINP_B02 },
  { DPIN_BTN_RED,     mVINP_B04 },
  { DPIN_BTN_TRIGGER, mVINP_TRIG_STATE }, // just the state, not the edge-detect
  { DPIN_AUDIO_BUSY,  mVINP_SOUNDACTV },
  { DPIN_AUDIO_BUSY,  mVINP_TRUESOUNDACTV }, // this one is for debugging
};

static struct _myState_t {
  uint16_t tableRow = 0;             // points to state that we will process or are processing
  uint16_t VinputRBG = 0;            // bits for input buttons and sound finish: mVINP_*
  uint16_t currVolume = 0;           // avoid sending volume when not needed - FIXME FUTURE FEATURE
  uint32_t timerNow = 0;             // timer now
  uint32_t timerPrevState = 0;       // start timer from previous time through state loop
  uint32_t timerPrevLEDstep = 0;     // start timer from previous LED activity
  uint32_t timerForceSoundActv = 0;  // end timer for forcing mVINP_SOUNDACTV true
  uint32_t timerMinForceSolenoidLow = 0; // min end timer for forcing solenoid to go back low
  uint32_t timerMaxForceSolenoidLow = 0; // max end timer for forcing solenoid to go back low
  uint8_t  timerSoundFinishedCanForceSolenoidLow = 1; // zero - firing sound did not finish; nonzero = sound did finish
  uint8_t  dynamicMode = EEPROM_CONFIG_RUNNING; // [0-3] for dynamic mode: switch through the saved configurations each time you shoot. Power cycle to exit dynamic mode.
  uint8_t  ptrnDelayLEDstep = 7;     // proper delta delay for Mark's patterns
  uint8_t  cfg_curnum = mNONE;       // current number for configuration list of choices
  uint8_t  cfg_maxnum = mNONE;       // maximum number for configuration list of choices
  uint8_t  cfg_category = mNONE;     // either 1 = SOUND or 2 = LED Pattern - used to tell sounds when configuring LEDs
  uint8_t  cfg_category2save = mNONE;// either 1 = SOUND or 2 = LED Pattern
  uint8_t  cfg_type = mNONE;         // example: mEFCT_LOCK_LOAD
  uint8_t  cfg_type2save = mNONE;    // example: mEFCT_LOCK_LOAD
  uint8_t  cfg_addr = mNONE;         // code: mADDR_CFG_CATEGORY, mADDR_CFG_TYPE, mADDR_CFG_EFFECT
} myState;
#define mCFG_CATEGORY_SOUND    1 // for myState.cfg_category
#define mCFG_CATEGORY_LEDPTRN  2 // for myState.cfg_category
#define mCFG_CATEGORY_CPY_RST  3 // for myState.cfg_category
#define mCFG_CATEGORY_ADVANCED 4 // for myState.cfg_category
#define mCFG_CATEGORY_MAXNUM  mCFG_CATEGORY_ADVANCED // for myState.cfg_category
// too lazy to use doubly-dimensioned arrays
static uint8_t cfgMaxSoundForType[EEPOFFSET(mEFCT_UNIQ)] = {
  8, 9, 8, 8, 4, 9 // sound - mEFCT_WIND_UP mEFCT_SHOOT mEFCT_OPEN_BARREL mEFCT_LOCK_LOAD mEFCT_PWRON mEFCT_WAIT
};
static uint8_t cfgMaxLEDForType[EEPOFFSET(mEFCT_UNIQ)] = {
  7, 8, 6, 6, 7, 7 // LED - mEFCT_WIND_UP mEFCT_SHOOT mEFCT_OPEN_BARREL mEFCT_LOCK_LOAD mEFCT_PWRON mEFCT_WAIT
}; // end theMaxForCategType[]

// some delays in milliseconds
//
#define SOLENOID_IF_NONZERO 0 // 1 for CLOTHESPIN (SOLENOID), 0 for SIDEWINDER (MOTOR) processing
#if SOLENOID_IF_NONZERO
  #define DLYSOLENOID_MAX 201  // max num milliseconds to leave solenoid on if CLOTHESPIN
  #define DLYSOLENOID_MIN 200  // min num milliseconds to leave solenoid on if CLOTHESPIN
#else
  #define DLYSOLENOID_MAX 6666  // max num milliseconds to leave motor on if SIDEWINDER (1 turn)
  #define DLYSOLENOID_MIN 1666  // min num milliseconds to leave motor on if SIDEWINDER (1/4 turn)
#endif
// Five factors: SOLENOID_IF_NONZERO, DLYSOLENOID_MIN and _MAX, end of shooting sound, releasing the trigger
//   SOLENOID/CLOTHESPIN approach - ignore the trigger, just use the edge signal to start
//                         hold the solenoid for at least DLYSOLENOID_MIN milliseconds
//                         after that, when shooting sound finishes, then release the solenoid
//                         release the solenoid after DLYSOLENOID_MAX milliseconds no matter what
//   MOTOR/SIDEWINDER approach - we also take into account how long the trigger is held in
//                         run the motor for at least DLYSOLENOID_MIN milliseconds
//                         after that, when BOTH the trigger is released AND shooting sound finishes, stop the motor
//                         stop the motor after DLYSOLENOID_MAX milliseconds no matter what
//                         NOTE that Tamiya 70189 Mini Motor with 661:1 ration runs at 9 RPM or about 6.6 sec per turn.
//                         These selected values make the motor turn a min of 1/4 and a max of about 1 turn per shot
//                            should allow firing most rubber bands or most multi-rubber-band loads; also allow single shot with multi-load

#define DLYLED_MIN 7
#define DLYLED_ringRotateAndFade 7 // for RBG_ringRotateAndFade
#define DLYLED_diskDownTheDrain 7 // for RBG_DiskDownTheDrain

// lookupLEDpattern - table to go from "when" and "configurable" to LED pattern number
//
#define TYPEOF_lookupLEDpatternTbl uint8_t // so we can match syses
#define mEFCT_PTRNLED_OFF 254
static const TYPEOF_lookupLEDpatternTbl lookupLEDpatternTbl[]
#if USE_PROGMEM
  PROGMEM
#endif // end USE_PROGMEM
  = { 
        7,  5,  2,  1,  6, 11,  12, 254, 254, 254,  // 000 to 009 - wind-up effects
        8,  9, 10, 11,  1,  7,   5,  12, 254, 254,  // 010 to 019 - shoot effects
        4, 11,  2,  7,  5, 13, 254, 254, 254, 254,  // 020 to 029 - open barrel effects
        4, 11,  2,  7,  5, 13, 254, 254, 254, 254,  // 030 to 039 - lock and load barrel effects
        5,  6,  3,  1, 11,  2,   7, 254, 254, 254,  // 040 to 049 - initial power-up effects
        6,  3,  5,  1, 11,  2,   7, 254, 254, 254   // 050 to 059 - waiting for trigger
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
    uint16_t efctSound;        // index for sound to make | (loud << mSHIFT_EFCT_SND_VOL) | masks
    uint16_t efctLED;          // index for light pattern
    uint16_t inputRBG;         // mask for input expected
    uint16_t storeVal;         // value to store, 8 bit uint
    uint16_t storeAddr;        // address to store; includes mask for mFUNC, mVAL,
                               //   EEPROM_START_SOUND_CONFIGS|mFUNC: idx= 3 WindUp, 2 Shoot, 4 Open, 7 Load
    uint16_t gotoOnInput;      // index within table to go with matching input
    uint16_t gotoWithoutInput; // index within table to go without waiting for input
    // uint16_t index;            // input column unused in this table
} RBGStateTable_t;

//
// the state table itself - automatically generated from makeStateTable.py
//
static const RBGStateTable_t myStateTable[90]
#if USE_PROGMEM
  PROGMEM
#endif // end USE_PROGMEM
  = {
      { /* row 0 mROW_POWERON */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mEFCT_PTRNLED_OFF, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_PWRON_OPEN, .gotoWithoutInput=mNONE, },
      { /* row 1 mROW_POWERON */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mEFCT_PTRNLED_OFF, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_PWRON_LOCKED, .gotoWithoutInput=mNONE, },
      { /* row 2 mROW_PWRON_OPEN */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, },
      { /* row 3 mROW_PWRON_OPEN */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B02|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_MENU, .gotoWithoutInput=mNONE, },
      { /* row 4 mROW_PWRON_LOCKED */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, },
      { /* row 5 mROW_PWRON_LOCKED */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_WINDUP_SOUND, .gotoWithoutInput=mNONE, },
      { /* row 6 mROW_PWRON_LOCKED */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_PWRON, .efctLED=mEFCT_PWRON, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B02|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_MENU, .gotoWithoutInput=mNONE, },
      { /* row 7 mROW_MENU */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mEFCT_PTRNLED_OFF, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_MENU_OPEN, .gotoWithoutInput=mNONE, },
      { /* row 8 mROW_MENU */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_NONE, .efctSound=mNONE, .efctLED=mEFCT_PTRNLED_OFF, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_MENU_CLOSED, .gotoWithoutInput=mNONE, },
      { /* row 9 mROW_MENU_OPEN */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_WINDUP_SOUND, .gotoWithoutInput=mNONE, },
      { /* row 10 mROW_MENU_OPEN */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_LOKLOD, .gotoWithoutInput=mNONE, },
      { /* row 11 mROW_MENU_OPEN */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B02|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_MENU, .gotoWithoutInput=mNONE, },
      { /* row 12 mROW_MENU_CLOSED */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_WINDUP_SOUND, .gotoWithoutInput=mNONE, },
      { /* row 13 mROW_MENU_CLOSED */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_OPNBRL, .gotoWithoutInput=mNONE, },
      { /* row 14 mROW_MENU_CLOSED */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_WAIT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B02|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_MENU, .gotoWithoutInput=mNONE, },
      { /* row 15 mROW_WINDUP_SOUND */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_WIND_UP, .efctLED=mEFCT_WIND_UP, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_SHOOT, },
      { /* row 16 mROW_SHOOT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_SHOOT, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_SHOOT_SOUND, },
      { /* row 17 mROW_SHOOT_SOUND */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_SHOOT, .efctLED=mEFCT_SHOOT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_SOLENOID, },
      { /* row 18 mROW_SOLENOID */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_SOLENOID, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_POWERON, },
      { /* row 19 mROW_OPNBRL */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_OPEN_BARREL, .efctLED=mEFCT_OPEN_BARREL, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, },
      { /* row 20 mROW_OPNBRL */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_OPEN_BARREL, .efctLED=mEFCT_OPEN_BARREL, .inputRBG=mINP_LOCK, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_LOKLOD, .gotoWithoutInput=mNONE, },
      { /* row 21 mROW_LOKLOD */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_LOCK_LOAD, .efctLED=mEFCT_LOCK_LOAD, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_MENU, },
      { /* row 22 mROW_LOKLOD */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_LOCK_LOAD, .efctLED=mEFCT_LOCK_LOAD, .inputRBG=mINP_OPEN, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_OPNBRL, .gotoWithoutInput=mNONE, },
      { /* row 23 mROW_LOKLOD */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_LOCK_LOAD, .efctLED=mEFCT_LOCK_LOAD, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_WINDUP_SOUND, .gotoWithoutInput=mNONE, },
      { /* row 24 mROW_CFG_MENU */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_INTRO, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY, .gotoWithoutInput=mNONE, },
      { /* row 25 mROW_CFG_MENU */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_INTRO, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY, .gotoWithoutInput=mNONE, },
      { /* row 26 mROW_CFG_MENU */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_INTRO, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_B02, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_MENU, .gotoWithoutInput=mNONE, },
      { /* row 27 mROW_CFG_CATEGORY */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGSTART, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=4.0, .storeAddr=mADDR_CFG_CATEGORY, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_CATEGORY_LOOPSTART, },
      { /* row 28 mROW_CFG_CATEGORY_LOOPSTART */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_CATEGORY, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 29 mROW_CFG_CATEGORY_LOOPSTART */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_CATEGORY, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 30 mROW_CFG_CATEGORY_LOOPSTART */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_CATEGORY, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_B02, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_MENU, .gotoWithoutInput=mNONE, },
      { /* row 31 mROW_CFG_CATEGORY_LOOP */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY_NEXT, .gotoWithoutInput=mNONE, },
      { /* row 32 mROW_CFG_CATEGORY_LOOP */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY_CHOICE, .gotoWithoutInput=mNONE, },
      { /* row 33 mROW_CFG_CATEGORY_LOOP */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_B02, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_POWERON, .gotoWithoutInput=mNONE, },
      { /* row 34 mROW_CFG_CATEGORY_NEXT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGNEXT, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_CATEGORY_LOOP, },
      { /* row 35 mROW_CFG_CATEGORY_CHOICE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFG2STORAGESKIP, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=4.0, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_TYPE, },
      { /* row 36 mROW_CFG_CATEGORY_SKIP1 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_TYPE, },
      { /* row 37 mROW_CFG_CATEGORY_SKIP2 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_TYPE, },
      { /* row 38 mROW_CFG_CATEGORY_SKIP3 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_CPY_RST, },
      { /* row 39 mROW_CFG_CATEGORY_SKIP4 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_ADVANCED, },
      { /* row 40 mROW_CFG_TYPE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGSTART, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=6.0, .storeAddr=mADDR_CFG_TYPE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_TYPE_LOOPSTART, },
      { /* row 41 mROW_CFG_TYPE_LOOPSTART */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_TYPE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_TYPE_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 42 mROW_CFG_TYPE_LOOPSTART */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_TYPE, .efctLED=mEFCT_WAIT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mNONE, },
      { /* row 43 mROW_CFG_TYPE_LOOPSTART */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_TYPE, .efctLED=mEFCT_WAIT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mNONE, },
      { /* row 44 mROW_CFG_TYPE_LOOP */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_TYPE_NEXT, .gotoWithoutInput=mNONE, },
      { /* row 45 mROW_CFG_TYPE_LOOP */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_TYPE_CHOICE, .gotoWithoutInput=mNONE, },
      { /* row 46 mROW_CFG_TYPE_LOOP */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG|mINP_B02, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_POWERON, .gotoWithoutInput=mNONE, },
      { /* row 47 mROW_CFG_TYPE_NEXT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGNEXT, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_TYPE_LOOP, },
      { /* row 48 mROW_CFG_TYPE_CHOICE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFG2STORAGE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_EFFECT, },
      { /* row 49 mROW_CFG_EFFECT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGSTART, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=0.0, .storeAddr=mADDR_CFG_EFFECT, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_EFFECT_LOOPSTART, },
      { /* row 50 mROW_CFG_EFFECT_LOOPSTART */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_EFFECT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_EFFECT_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 51 mROW_CFG_EFFECT_LOOP */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_EFFECT_NEXT, .gotoWithoutInput=mNONE, },
      { /* row 52 mROW_CFG_EFFECT_LOOP */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_EFFECT_CHOICE, .gotoWithoutInput=mNONE, },
      { /* row 53 mROW_CFG_EFFECT_LOOP */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mINP_TRIG|mINP_B02, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_POWERON, .gotoWithoutInput=mNONE, },
      { /* row 54 mROW_CFG_EFFECT_NEXT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGNEXT, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_EFFECT_LOOP, },
      { /* row 55 mROW_CFG_EFFECT_CHOICE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFG2STORAGE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_ACCEPTED, },
      { /* row 56 mROW_CFG_ACCEPTED */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_UNIQ_CFG_ACCEPT, .efctLED=mEFCT_WAIT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_CATEGORY, },
      { /* row 57 mROW_CFG_ACCEPTED */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_UNIQ_CFG_ACCEPT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CATEGORY, .gotoWithoutInput=mNONE, },
      { /* row 58 mROW_CFG_CPY_RST */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGSTART, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=8.0, .storeAddr=mADDR_CFG_CPY_RST, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_CPY_RST_LOOPSTART, },
      { /* row 59 mROW_CFG_CPY_RST_LOOPSTART */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_CPY_RST, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CPY_RST_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 60 mROW_CFG_CPY_RST_LOOP */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CPY_RST_NEXT, .gotoWithoutInput=mNONE, },
      { /* row 61 mROW_CFG_CPY_RST_LOOP */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_CPY_RST_CHOICE, .gotoWithoutInput=mNONE, },
      { /* row 62 mROW_CFG_CPY_RST_LOOP */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_B02, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_POWERON, .gotoWithoutInput=mNONE, },
      { /* row 63 mROW_CFG_CPY_RST_NEXT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGNEXT, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_CPY_RST_LOOP, },
      { /* row 64 mROW_CFG_CPY_RST_CHOICE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFG2CPYRST, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=8.0, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_POWERON, },
      { /* row 65 mROW_CFG_CPY_RST_SKIP1 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_FACT2RUN, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CPY_RST_ACCEPTED, },
      { /* row 66 mROW_CFG_CPY_RST_SKIP2 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_FACT2ALL, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CPY_RST_ACCEPTED, },
      { /* row 67 mROW_CFG_CPY_RST_SKIP3 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_RUN2ONE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CPY_RST_ACCEPTED, },
      { /* row 68 mROW_CFG_CPY_RST_SKIP4 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_RUN2TWO, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CPY_RST_ACCEPTED, },
      { /* row 69 mROW_CFG_CPY_RST_SKIP5 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_RUN2THREE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CPY_RST_ACCEPTED, },
      { /* row 70 mROW_CFG_CPY_RST_SKIP6 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_ONE2RUN, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CPY_RST_ACCEPTED, },
      { /* row 71 mROW_CFG_CPY_RST_SKIP7 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_TWO2RUN, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CPY_RST_ACCEPTED, },
      { /* row 72 mROW_CFG_CPY_RST_SKIP8 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_THREE2RUN, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CPY_RST_ACCEPTED, },
      { /* row 73 mROW_CPY_RST_ACCEPTED */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_UNIQ_CFG_CPY_RST_ACCEPT, .efctLED=mEFCT_WAIT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_POWERON, },
      { /* row 74 mROW_CPY_RST_ACCEPTED */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_UNIQ_CFG_CPY_RST_ACCEPT, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_POWERON, .gotoWithoutInput=mNONE, },
      { /* row 75 mROW_CFG_ADVANCED */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGSTART, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=3.0, .storeAddr=mADDR_CFG_ADVANCED, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_ADVNCD_LOOPSTART, },
      { /* row 76 mROW_CFG_ADVNCD_LOOPSTART */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_ADVANCED, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_ADVNCD_LOOP, .gotoWithoutInput=mNONE, },
      { /* row 77 mROW_CFG_ADVNCD_LOOP */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_ADVNCD_NEXT, .gotoWithoutInput=mNONE, },
      { /* row 78 mROW_CFG_ADVNCD_LOOP */  .blkFlags=mZERO, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_BANY|mINP_B01|mINP_B04, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_CFG_ADVNCD_CHOICE, .gotoWithoutInput=mNONE, },
      { /* row 79 mROW_CFG_ADVNCD_LOOP */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONFIGURE, .efctSound=mNONE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG|mINP_B02, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_POWERON, .gotoWithoutInput=mNONE, },
      { /* row 80 mROW_CFG_ADVNCD_NEXT */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFGNEXT, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_CFG_ADVNCD_LOOP, },
      { /* row 81 mROW_CFG_ADVNCD_CHOICE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_CFG2ADVNCD, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=3.0, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_POWERON, },
      { /* row 82 mROW_CFG_ADVNCD_SKIP1 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_STATICMODE, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_ADVNCD_STATIC_ACCEPTED, },
      { /* row 83 mROW_CFG_ADVNCD_SKIP2 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_HANDLER | mSPCL_HANDLER_ADVFEATURES, .efctSound=mNONE, .efctLED=mNONE, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_ADVNCD_PASSWD_VERBAL, },
      { /* row 84 mROW_CFG_ADVNCD_SKIP3 */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_UNIQ_CFG_CREDITS, .efctLED=mEFCT_WAIT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_POWERON, },
      { /* row 85 mROW_ADVNCD_STATIC_ACCEPTED */  .blkFlags=mBLOCKSTART, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_UNIQ_CFG_STATIC_STARTED, .efctLED=mEFCT_WAIT, .inputRBG=mNONE, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mNONE, .gotoWithoutInput=mROW_POWERON, },
      { /* row 86 mROW_ADVNCD_STATIC_ACCEPTED */  .blkFlags=mBLOCKEND, .SPECIAL=mSPCL_EFCT_ONETIME, .efctSound=mEFCT_UNIQ_CFG_STATIC_STARTED, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_POWERON, .gotoWithoutInput=mNONE, },
      { /* row 87 mROW_ADVNCD_PASSWD_VERBAL */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_ENTER_PASSWORD, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_ADVNCD_PASSWD_DANCE, .gotoWithoutInput=mNONE, },
      { /* row 88 mROW_ADVNCD_PASSWD_DANCE */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_ENTER_DANCE, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_ADVNCD_PASSWD_NOPASSWD, .gotoWithoutInput=mNONE, },
      { /* row 89 mROW_ADVNCD_PASSWD_NOPASSWD */  .blkFlags=mBLOCKSTART|mBLOCKEND, .SPECIAL=mSPCL_EFCT_CONTINUOUS, .efctSound=mEFCT_UNIQ_CFG_SORRY_NO_PASSWORD, .efctLED=mEFCT_WAIT, .inputRBG=mINP_TRIG, .storeVal=mNONE, .storeAddr=mNONE, .gotoOnInput=mROW_POWERON, .gotoWithoutInput=mNONE, },
}; // end definition of myStateTable[]
