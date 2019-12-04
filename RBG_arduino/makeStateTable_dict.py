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
               "blkFlags":         "    uint8_t blkFlags;         // mBLOCKSTART, mBLOCKEND or mNONE",
               "SPECIAL":          "    uint8_t SPECIAL;          // special row-handling flags: mSPCL_*",
               "efctSound":  "    uint8_t efctSound;  // index for sound to make after input match",
               "efctLED":           "    uint8_t efctLED;           // index for light pattern while waiting",
               "inputRBG":         "    uint8_t inputRBG;         // mask for input expected",
               "storeVal":         "    uint8_t storeVal;         // value to store, 8 bit uint",
               "storeAddr":        "    uint8_t storeAddr;        // address to store; includes mask for mFUNC, mVAL,\n" \
                                 + "                              //   eeSoundSave|mFUNC: idx= 3 WindUp, 2 Shoot, 4 Open, 7 Load",
               "gotoOnInput":      "    uint8_t gotoOnInput;      // index within table to go with matching input",
               "gotoWithoutInput": "    uint8_t gotoWithoutInput; // index within table to go without waiting for input",
               "index":            "    uint8_t index;            // input column unused in this table"
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
    uint8_t efctSound;  // index for sound to make after input match \
    uint8_t efctLED;           // index for light pattern while waiting \
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
mEFCT_WIND_UP = 00  # 000 to 009 - wind-up effects
mEFCT_SHOOT = 10  # 010 to 019 - shoot effects
mEFCT_OPEN_BARREL = 20  # 020 to 029 - open barrel effects
mEFCT_LOCK_LOAD = 30  # 030 to 039 - lock and load barrel effects
mEFCT_INIT_PWR_UP = 40  # 040 to 049 - after initial power-up effects
mEFCT_CONFIGURE = 80  # 080 to 099 - effects used to navigate menus
#
EFFECT_MAP = {
    "mEFCT_WIND_UP": mEFCT_WIND_UP,  # 000 to 009 - wind-up effects
    "mEFCT_SHOOT": mEFCT_SHOOT,  # 010 to 019 - shoot effects
    "mEFCT_OPEN_BARREL": mEFCT_OPEN_BARREL,  # 020 to 029 - open barrel effects
    "mEFCT_LOCK_LOAD": mEFCT_LOCK_LOAD,  # 030 to 039 - lock and load barrel effects
    "mEFCT_INIT_PWR_UP": mEFCT_INIT_PWR_UP,  # 040 to 049 - after initial power-up effects
    "mEFCT_CONFIGURE": mEFCT_CONFIGURE  # 080 to 099 - effects used to navigate menus
}