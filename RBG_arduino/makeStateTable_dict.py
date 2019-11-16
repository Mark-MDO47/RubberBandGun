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
STATETABLEROW = {"blkFlags": "", "soundAfterInput": "", "lights": "", "inputRBG": "", "storeVal": "", "storeAddr": "",
                 "gotoOnInput": "", "gotoWithoutInput": "", "index": ""}
FOUNDINCOLUMN = {
    "index": [],
    "soundAfterInput": [],
    "lights": [],
    "inputRBG": [],
    "storeVal": [],
    "storeAddr": [],
    "gotoOnInput": [],
    "gotoWithoutInput": []
}

# INPUT:
COLTOINDEX = {"index": -1, "soundAfterInput": -1, "lights": -1, "inputRBG": -1, "storeVal": -1, "storeAddr": -1,
              "gotoOnInput": -1, "gotoWithoutInput": -1}

# OUTPUT:
# uint8_t soundAfterInput;  // index for sound to make after input match
# uint8_t lights;           // index for light pattern while waiting
# uint8_t inputRBG;         // mask for input expected
# uint8_t storeVal;         // value to store, 8 bit uint
# uint8_t storeAddr;        // address to store; includes mask for mFUNC, mVAL,
#                                 eeSoundSave|mFUNC: idx= 1 WindUp, 2 Shoot, 4 Open, 7 Load
# uint8_t gotoOnInput;      // index within table to go with matching input
# uint8_t gotoWithoutInput; // index within table to go without waiting for input

translateToMasks = {
    "blkFlags": {},
    "soundAfterInput": {},
    "lights": {},
    "inputRBG": {
        "trigPlus": "mTRIG|mBANY",
        "trig00": "mTRIG|mBNONE",
        "trig01": "mTRIG|mB01",
        "trig02": "mTRIG|mB02",
        "trig03": "mTRIG|mB03",
        "trig04": "mTRIG|mB04",
        "trig05": "mTRIG|mB05",
        "trig06": "mTRIG|mB06",
        "trig07": "mTRIG|mB07",
        "open": "mOPEN",
        "lock": "mLOCK",
        "": "mNONE",
        "trigOnly": "mTRIG|mBNONE",
        "trigYellow": "mTRIG|mB01",
        "trigGreen": "mTRIG|mB02",
        "trigBlack": "mTRIG|mB03",
        "trigAll": "mTRIG|mB07",
    },
    "storeVal": {},
    "storeAddr": {},
    "gotoOnInput": {},
    "gotoWithoutInput": {}
}

#
# Map of effects: sounds, LED patterns
EFCT_WIND_UP = 00  # 000 to 009 - wind-up effects
EFCT_SHOOT = 10  # 010 to 019 - shoot effects
EFCT_OPEN_BARREL = 20  # 020 to 029 - open barrel effects
EFCT_LOCK_LOAD = 30  # 030 to 039 - lock and load barrel effects
EFCT_INIT_PWR_UP = 40  # 040 to 049 - after initial power-up effects
EFCT_CONFIGURE = 80  # 080 to 099 - effects used to navigate menus
#
EFFECT_MAP = {
    "EFCT_WIND_UP": EFCT_WIND_UP,  # 000 to 009 - wind-up effects
    "EFCT_SHOOT": EFCT_SHOOT,  # 010 to 019 - shoot effects
    "EFCT_OPEN_BARREL": EFCT_OPEN_BARREL,  # 020 to 029 - open barrel effects
    "EFCT_LOCK_LOAD": EFCT_LOCK_LOAD,  # 030 to 039 - lock and load barrel effects
    "EFCT_INIT_PWR_UP": EFCT_INIT_PWR_UP,  # 040 to 049 - after initial power-up effects
    "EFCT_CONFIGURE": EFCT_CONFIGURE  # 080 to 099 - effects used to navigate menus
}