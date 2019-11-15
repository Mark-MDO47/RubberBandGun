# Author: Mark Olson 2019-11-03
#
# Rubber Band Gun - https://github.com/Mark-MDO47/RubberBandGun
# RBG - A high-tech imagining of the rubber band gun
#
# This program will read a spreadsheet with info to be encoded into the state table for RBG_SciFi.ino
#

import pandas as pd
import copy

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

DEBUGflag = False  # global debug flag

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


def print_debug(the_str):
    if DEBUGflag:
        print("%s" % the_str)


def mark_end_block(curr_symb, curr_state_table_idx):
    global SYMBTABLE
    print_debug("DEBUG CALL mark_end_block on curr_symb |%s| with curr_state_table_idx %s"
                 % (curr_symb, curr_state_table_idx))
    print_debug("  DEBUG BEFORE %s" % SYMBTABLE)
    if 0 == len(curr_symb):
        print_debug("  DEBUG AFTER  %s" % SYMBTABLE)
        return "Tried to mark_end_block on zero-length curr_symb |%s| with curr_state_table_idx %s" % (
            curr_symb, curr_state_table_idx)
    print_debug("DEBUG mark_end_block on curr_symb %s with curr_state_table_idx %s" % (curr_symb, curr_state_table_idx))
    if curr_symb in SYMBTABLE.keys():
        SYMBTABLE[curr_symb]["blockEnd"] = curr_state_table_idx
        print_debug("  DEBUG AFTER  %s" % SYMBTABLE)
        return ""
    else:
        print_debug("  DEBUG AFTER  %s" % SYMBTABLE)
        return "Tried to mark_end_block on curr_symb %s with curr_state_table_idx %s but %s not in SYMBTABLE" % (
            curr_symb, curr_state_table_idx, curr_symb)


def make_new_block(curr_symb, curr_state_table_idx, debug_string="debugUNKNOWN") -> object:
    global SYMBTABLE
    global STATETABLE
    if curr_symb in SYMBTABLE.keys():
        print_debug("DEBUG NEW %s BEFORE: curr_state_table_idx %d SYMBTABLE[%s] %s" % (
            debug_string, curr_state_table_idx, curr_symb, SYMBTABLE[curr_symb]))
    else:
        print_debug("DEBUG NEW %s BEFORE: curr_state_table_idx %d %s" % (debug_string, curr_state_table_idx, curr_symb))
    print_debug("  DEBUG SYMBTABLE %s" % SYMBTABLE)
    curr_state_table_idx += 1
    SYMBTABLE[curr_symb] = copy.deepcopy(SYMBTABLEROW)
    SYMBTABLE[curr_symb]["blockStart"] = curr_state_table_idx

    print_debug("DEBUG NEW %s  AFTER: curr_state_table_idx %d SYMBTABLE[%s] %s" % (
        debug_string, curr_state_table_idx, curr_symb, SYMBTABLE[curr_symb]))
    print_debug("  DEBUG SYMBTABLE %s" % SYMBTABLE)
    return curr_state_table_idx, curr_symb


# COLTOINDEX = {"index": "", "soundAfterInput", "lights", "input", "storeVal", "storeAddr",
#               "gotoOnInput", "gotoWithoutInput": "" }
# STATETABLEROW = { "blkFlags": 0, "soundAfterInput": 0, "lights": 0, "inputRBG": 0,
#               "storeVal": 0, "storeAddr": 0, "gotoOnInput": 0, "gotoWithoutInput": 0 }
def fill_state_table_pass1(row, state_idx):
    global FOUNDINCOLUMN
    global STATETABLE

    STATETABLE[state_idx] = copy.deepcopy(STATETABLEROW)
    for key in COLTOINDEX.keys():
        row_text = str(row[key]).strip()
        if "nan" == row_text:
            row_text = "mNONE"
        if row_text not in FOUNDINCOLUMN[key]:
            FOUNDINCOLUMN[key].append(row_text)
        if key in translateToMasks.keys():
            if row_text in translateToMasks[key]:
                row_text = translateToMasks[key][row_text]
            else:
                pass
        if key in STATETABLEROW.keys():
            STATETABLE[state_idx][key] = row_text


def make_state_table():
    global SYMBTABLE
    global STATETABLE
    global COLTOINDEX

    # Import the excel file
    xls_file = pd.ExcelFile('./StateTable.xlsx')
    df = xls_file.parse(xls_file.sheet_names[0])

    # map the column names to numbers; will barf if there is a problem
    df_col_names = df.columns.values.tolist()
    for col in COLTOINDEX:
        COLTOINDEX[col] = df_col_names.index(col)

    # Pass 1 - read through excel file and get symbol table
    statetable_idx = -1  # this will be index into state table we are building
    symbtable_current = ""  # zero length means not processing any state decision block
    for row_num, row in df.iterrows():
        # the first row (row_num == 0) is the one after the column titles
        # rowIndexSymb = str(row[df_col_names["index"]]).strip
        row_index_symb = str(row["index"]).strip()
        if "nan" == row_index_symb:  # rows with nothing in "index" column are ignored
            err = mark_end_block(symbtable_current, statetable_idx)
            if 0 != len(err):
                print_debug(
                    "DEBUG %s symbtable_current |%s| from rows with nothing in index column" % (err, symbtable_current))
            print_debug("  DEBUG %s" % SYMBTABLE)
            continue

        if 0 == len(symbtable_current):  # this is a new symbol, possibly the first symbol
            if statetable_idx >= 0:  # mark end of previous block if there is one
                err = mark_end_block(symbtable_current, statetable_idx)
            statetable_idx, symbtable_current = make_new_block(row_index_symb, statetable_idx)
            fill_state_table_pass1(row, statetable_idx)
        else:  # we were processing a symbol before
            if row_index_symb == symbtable_current:  # continuing on with this state decision block
                statetable_idx += 1
                fill_state_table_pass1(row, statetable_idx)
            else:  # new state decision block
                if statetable_idx >= 0:  # mark end of previous block if there is one
                    err = mark_end_block(symbtable_current, statetable_idx)
                statetable_idx, symbtable_current = make_new_block(row_index_symb, statetable_idx)
                fill_state_table_pass1(row, statetable_idx)
    if statetable_idx >= 0:  # mark end of previous block if there is one
        err = mark_end_block(symbtable_current, statetable_idx)
    # mark block start/end in STATETABLE
    for symb in SYMBTABLE:
        STATETABLE[SYMBTABLE[symb]['blockStart']]['blkFlags'] = "mBlockStart"
        separator = ""
        if 0 != len(STATETABLE[SYMBTABLE[symb]['blockEnd']]['blkFlags']):
            separator = "|"
        STATETABLE[SYMBTABLE[symb]['blockEnd']]['blkFlags'] += separator + "mBlockEnd"

    print("Pass 1 SYMBTABLE")
    print_debug("  %s" % SYMBTABLE)
    for symb in SYMBTABLE:
        print("  %s %s" % (symb, SYMBTABLE[symb]))

    print("Pass 1 STATETABLE")
    print_debug("  %s" % STATETABLE)
    for idx in STATETABLE:
        print("  %s %s" % (idx, str(STATETABLE[idx])))

    # collect sounds and light patterns
    found_directpatterns = {'lights': {}, 'soundAfterInput': {}}
    found_indirectpatterns = {'lights': {}, 'soundAfterInput': {}}
    for col in found_directpatterns.keys():
        count_direct = 1
        count_indirect = 1
        for idx in STATETABLE:
            if 0 != len(STATETABLE[idx][col]):
                if -1 == STATETABLE[idx][col].find("["):
                    if STATETABLE[idx][col] not in found_directpatterns[col]:
                        found_directpatterns[col][STATETABLE[idx][col]] = count_direct
                        count_direct += 1
                else:  # indirect
                    if STATETABLE[idx][col] not in found_indirectpatterns[col]:
                        found_indirectpatterns[col][STATETABLE[idx][col]] = count_indirect
                        count_indirect += 1

    print("Pass 1 found_directpatterns: lights, soundAfterInput")
    for col in found_directpatterns.keys():
        print_debug("  %s %s" % (col, found_directpatterns[col]))
        print("  %s" % col)
        for key in found_directpatterns[col].keys():
            print("     %03d\t%s" % (found_directpatterns[col][key], key))
    print("Pass 1 found_indirectpatterns: lights, soundAfterInput")
    for col in found_indirectpatterns.keys():
        print_debug("  %s %s" % (col, found_indirectpatterns[col]))
        print("  %s" % col)
        for key in found_indirectpatterns[col].keys():
            print("     %03d\t%s" % (found_indirectpatterns[col][key], key))

    # collect found symbols from either goto column
    found_symbols = []
    for col in ("gotoOnInput", "gotoWithoutInput"):
        for symb in FOUNDINCOLUMN[col]:
            if symb not in found_symbols:
                found_symbols.append(symb)

    print("Pass 1 found_symbols")
    print_debug("  %s" % found_symbols)
    for key in found_symbols:
        if key == "mNONE":
            print("  %s is valid" % key)
        elif key in SYMBTABLE.keys():
            print("  %s in SYMBTABLE" % key)
        else:
            print("  ERROR - %s not in SYMBTABLE" % key)

    # Pass 2
    """
   for col in ("gotoOnInput", "gotoWithoutInput"):
       for idx in
      for symb in FOUNDINCOLUMN[col]:
         if symb not in found_symbols:
   for key in found_symbols:
      if key == "mNONE":
         print("  %s is valid" % key)
      elif key in SYMBTABLE.keys():
         print("  %s in SYMBTABLE" % key)
   """


if __name__ == "__main__":
    make_state_table()
