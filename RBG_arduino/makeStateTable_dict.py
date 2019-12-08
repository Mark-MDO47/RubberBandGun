# Author: Mark Olson 2019-11-03
#
# Rubber Band Gun - https://github.com/Mark-MDO47/RubberBandGun
# RBG - A high-tech imagining of the rubber band gun
#
# This program will read a spreadsheet with info to be encoded into the state table for RBG_SciFi.ino

# GLOBALS
EXCELROWNUMOFFSET = 2  # so we can give error messages
SYMBTABLE = {}
SYMBTABLEROW = {"blockStart": -1, "blockEnd": -1}
STATETABLE = {}
STATETABLEROW = {"blkFlags": "", "SPECIAL": "", "efctSound": "", "efctLED": "", "inputRBG": "",
                 "storeVal": "", "storeAddr": "", "gotoOnInput": "", "gotoWithoutInput": "", "index": ""}

COLTOSTRUCT = {
               "blkFlags":         "    uint16_t blkFlags;         // mBLOCKSTART, mBLOCKEND or mZERO",
               "SPECIAL":          "    uint16_t SPECIAL;          // special row-handling flags: mSPCL_*",
               "efctSound":  "    uint16_t efctSound;  // index for sound to makeh",
               "efctLED":           "    uint16_t efctLED;           // index for light pattern",
               "inputRBG":         "    uint16_t inputRBG;         // mask for input expected",
               "storeVal":         "    uint16_t storeVal;         // value to store, 8 bit uint",
               "storeAddr":        "    uint16_t storeAddr;        // address to store; includes mask for mFUNC, mVAL,\n" \
                                 + "                              //   eeSoundSave|mFUNC: idx= 3 WindUp, 2 Shoot, 4 Open, 7 Load",
               "gotoOnInput":      "    uint16_t gotoOnInput;      // index within table to go with matching input",
               "gotoWithoutInput": "    uint16_t gotoWithoutInput; // index within table to go without waiting for input",
               "index":            "    uint16_t index;            // input column unused in this table"
              }

FOUNDINCOLUMN = {
    "SPECIAL": [],
    "index": [],
    "efctSound": [],
    "efctLED": [],
    "inputRBG": [],
    "storeVal": [],
    "storeAddr": [],
    "gotoOnInput": [],
    "gotoWithoutInput": []
}

# INPUT:
COLTOINDEX = {"index": -1, "SPECIAL": -1, "efctSound": -1, "efctLED": -1, "inputRBG": -1, "storeVal": -1,
              "storeAddr": -1, "gotoOnInput": -1, "gotoWithoutInput": -1}

STRUCTSTRING = "    typedef struct struct_statetable { \
    uint8_t SPECIAL;          // special row-handling flags: mSPCL_* \
    uint8_t efctSound;  // index for sound to make \
    uint8_t efctLED;           // index for light pattern \
    uint8_t inputRBG;         // mask for input expected \
    uint8_t storeVal;         // value to store, 8 bit uint \
    uint8_t storeAddr;        // address to store; includes mask for mFUNC, mVAL, \
                                    eeSoundSave|mFUNC: idx= 1 WindUp, 2 Shoot, 4 Open, 7 Load \
    uint8_t gotoOnInput;      // index within table to go with matching input \
    uint8_t gotoWithoutInput; // index within table to go without waiting for input \
    } TYPE_STATETABLE; "


translateToMasks = {
    "blkFlags": {},
    "SPECIAL": {},
    "efctSound": {},
    "efctLED": {},
    "inputRBG": {
        "trigPlus": "mINP_TRIG|mINP_BANY",
        "trig00": "mINP_TRIG|mINP_BNONE",
        "trig01": "mINP_TRIG|mINP_B01",
        "trig02": "mINP_TRIG|mINP_B02",
        "trig03": "mINP_TRIG|mINP_B03",
        "trig04": "mINP_TRIG|mINP_B04",
        "trig05": "mINP_TRIG|mINP_B05",
        "trig06": "mINP_TRIG|mINP_B06",
        "trig07": "mINP_TRIG|mINP_B07",
        "open": "mINP_OPEN",
        "lock": "mINP_LOCK",
        "": "mINP_NONE",
        "trigOnly": "mINP_TRIG|mINP_BNONE",
        "trigYellow": "mINP_TRIG|mINP_B01",
        "trigGreen": "mINP_TRIG|mINP_B02",
        "trigBlack": "mINP_TRIG|mINP_B03",
        "trigAll": "mINP_TRIG|mINP_B07",
    },
    "storeVal": {},
    "storeAddr": {},
    "gotoOnInput": {},
    "gotoWithoutInput": {}
}


#
# Map of effects: sounds, LED patterns
#   note: could use folders for the files and repeat numbers, but this also refers to efctLED
#   Files will be in the MP3 folder: for instance, file 4 is SD:/MP3/0004.mp3
mEFCT_WIND_UP = 00  # 001 to 009 - wind-up effects
mEFCT_SHOOT = 10  # 011 to 019 - shoot effects
mEFCT_OPEN_BARREL = 20  # 021 to 029 - open barrel effects
mEFCT_LOCK_LOAD = 30  # 031 to 039 - lock and load barrel effects
mEFCT_PWRON = 40  # 041 to 049 - after initial power-up effects
mEFCT_CONFIGURE = 80  # 081 to 099 - effects used to navigate menus
mEFCT_UNIQ = 100  # 101 to 109 - unique effects not included in configurations
#
EFFECT_MAP = {
    "mEFCT_WIND_UP": [mEFCT_WIND_UP, " // 001 to 009 - wind-up effects"],
    "mEFCT_SHOOT": [mEFCT_SHOOT, " // 011 to 019 - shoot effects"],
    "mEFCT_OPEN_BARREL": [mEFCT_OPEN_BARREL, " // 021 to 029 - open barrel effects"],
    "mEFCT_LOCK_LOAD": [mEFCT_LOCK_LOAD, " // 031 to 039 - lock and load barrel effects"],
    "mEFCT_PWRON": [mEFCT_PWRON, " // 041 to 049 - after initial power-up effects"],
    "mEFCT_CONFIGURE": [mEFCT_CONFIGURE, " // 081 to 099 - effects used to navigate menus"],
    "mEFCT_UNIQ": [mEFCT_UNIQ,  " // 101 to 109 - unique effects not included in configurations"]
}