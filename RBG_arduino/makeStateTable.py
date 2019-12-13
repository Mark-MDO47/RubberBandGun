# Author: Mark Olson 2019-11-03
#
# Rubber Band Gun - https://github.com/Mark-MDO47/RubberBandGun
# RBG - A high-tech imagining of the rubber band gun
#
# This program will read a spreadsheet with info to be encoded into the state table for RBG_SciFi.ino

import pandas as pd
import copy
import sys

from makeStateTable_dict import *

DEBUGflag = False  # global debug flag

def print_debug(the_str):
    """only prints if DEBUGflag is true
    :param the_str: string to print
    """
    if DEBUGflag:
        print("%s" % the_str)


def mark_end_block(curr_symb, curr_state_table_idx):
    """mark_end_block on curr_symb with curr_state_table_idx
    :param curr_symb: string for current symbol
    :param curr_state_table_idx: corresponding index into STATETABLE
    :return:
    """
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


def make_new_block(curr_state_table_idx,curr_symb,  debug_string="debugUNKNOWN"):
    """make_new_block starting on curr_symb
    :param curr_symb: string for current symbol found in "index" column. Will be coerced to single lower-case then all upper
    :param curr_state_table_idx: index to state table where curr_symb was found
    :param debug_string: call-identifying string to append to debug messages
    :return: curr_state_table_idx, curr_symb
    """
    global SYMBTABLE
    global STATETABLE
    curr_symb = curr_symb.lower()[0] + curr_symb.upper()[1:] # enforce capitalization rules
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


def complete_block_field():
    """Complete the block fields; fill in with mZERO if empty"""
    global STATETABLE
    for idx in range(len(STATETABLE)):
        if 0 == len(STATETABLE[idx]["blkFlags"]):
            STATETABLE[idx]["blkFlags"] = "mZERO"

# COLTOINDEX = {"index": -1, "SPECIAL": -1, "efctSound": -1, "efctLED": -1, "inputRBG": -1, "storeVal": -1,
#               "storeAddr": -1, "gotoOnInput": -1, "gotoWithoutInput": -1}
# STATETABLEROW = {"blkFlags": "", "SPECIAL": "", "efctSound": "", "efctLED": "", "inputRBG": "",
#                  "storeVal": "", "storeAddr": "", "gotoOnInput": "", "gotoWithoutInput": "", "index": ""}
def fill_state_table_pass1(row, state_idx):
    """fill_state_table_pass1 on current row
    :param row: row from spreadsheet input file; access via COLTOINDEX
    :param state_idx: corresponding index into STATETABLE
    """
    global FOUNDINCOLUMN
    global STATETABLE

    STATETABLE[state_idx] = copy.deepcopy(STATETABLEROW)
    for key in COLTOINDEX.keys():
        row_text = str(row[key]).strip()
        if "nan" == row_text:
            row_text = "mNONE"
        elif key in ["index", "gotoOnInput", "gotoWithoutInput"]:
            row_text = row_text.lower()[0] + row_text.upper()[1:] # enforce capitalization
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
    """make_state_table then print info"""
    global SYMBTABLE
    global STATETABLE
    global COLTOINDEX

    # Import the excel file
    xls_file = pd.ExcelFile('./StateTable_minimal.xlsx')
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
            statetable_idx, symbtable_current = make_new_block(statetable_idx, row_index_symb)
            fill_state_table_pass1(row, statetable_idx)
        else:  # we were processing a symbol before
            if row_index_symb == symbtable_current:  # continuing on with this state decision block
                statetable_idx += 1
                fill_state_table_pass1(row, statetable_idx)
            else:  # new state decision block
                if statetable_idx >= 0:  # mark end of previous block if there is one
                    err = mark_end_block(symbtable_current, statetable_idx)
                statetable_idx, symbtable_current = make_new_block(statetable_idx, row_index_symb)
                fill_state_table_pass1(row, statetable_idx)
    if statetable_idx >= 0:  # mark end of previous block if there is one
        err = mark_end_block(symbtable_current, statetable_idx)
    # mark block start/end in STATETABLE
    for symb in SYMBTABLE:
        STATETABLE[SYMBTABLE[symb]['blockStart']]['blkFlags'] = "mBLOCKSTART"
        separator = ""
        if 0 != len(STATETABLE[SYMBTABLE[symb]['blockEnd']]['blkFlags']):
            separator = "|"
        STATETABLE[SYMBTABLE[symb]['blockEnd']]['blkFlags'] += separator + "mBLOCKEND"

    print_debug("Pass 1 SYMBTABLE")
    print_debug("  %s" % SYMBTABLE)
    for symb in SYMBTABLE:
        print_debug("  %s %s" % (symb, SYMBTABLE[symb]))

    print_debug("Pass 1 STATETABLE")
    print_debug("  %s" % STATETABLE)
    for idx in STATETABLE:
        print_debug("  %s %s" % (idx, str(STATETABLE[idx])))

    # collect sounds and light patterns
    known_effects = {"mNONE": 0xFF, "mEFCT_SPCL": 0x40, "mEFCT_SHOOT": 1, "mEFCT_OPEN_BARREL": 2, "mEFCT_LOCK_LOAD": 3} ### FIXME is this a good list ???
    count_effects = {'efctLED': 1, 'efctSound': 1}
    found_effects = {'efctLED': {}, 'efctSound': {}}
    for efct in count_effects.keys(): ### FIXME this needs work. What are we looking for here? does not find mSPCL_EFCT_CONTINUOUS
        for idx in STATETABLE:
            if 0 != len(STATETABLE[idx][efct]):
                txt = STATETABLE[idx][efct]
                if txt.split('|')[0] in known_effects.keys(): ### FIXME only looks at first one
                    pass
                elif txt not in found_effects[efct].keys():
                    found_effects[efct][txt] = count_effects[efct]
                    count_effects[efct] += 1

    print_debug("Pass 1 found_effects: efctLED, efctSound")
    for efct in found_effects.keys():
        for symb in found_effects[efct]:
            print_debug("  %s %s %d" % (efct, symb, found_effects[efct][symb]))

    # Pass 2

    # collect found symbols from either goto column
    found_symbols = []
    for col in ("gotoOnInput", "gotoWithoutInput"):
        for row, symb in enumerate(FOUNDINCOLUMN[col]):
            if symb not in found_symbols:
                found_symbols.append(symb)

    print("\n// define the symbols - general use symbols:"
            + "\n#define mUNDEFINED 254"
            + "\n#define mNONE 255"
            + "\n#define mZERO 0"
            + "\n\n// define the symbols - .SPECIAL:"
            + "\n#define mSPCL_HANDLER         0x0100"
            + "\n#define mSPCL_HANDLER_SHOOT        1 // a special handler function"
            + "\n\n// define the symbols - .blkFlags:"
            + "\n#define mBLOCKSTART 0x80"
            + "\n#define mBLOCKEND   0x40"
            + "\n\n// define the symbols - .index: first the single constant mPOWERON one, then the others:"
            + "\n#define mPOWERON 0  // first address in myState[]")

    print_debug("Pass 2 found_symbols")
    for key in found_symbols:
        if key == "mNONE":
            print_debug("  %s is valid" % key)
        elif key in SYMBTABLE.keys():
            print_debug("  %s in SYMBTABLE" % key)
            print("#define %s %d" % (key, SYMBTABLE[key]["blockStart"]))
        else:
            print_debug("  ERROR - %s not in SYMBTABLE" % key)
            print("#define %s mUNDEFINED" % key)
    print("\n// define the effect number ranges - must be divisible by 10")
    for key in EFFECT_MAP:
        print("#define %s %*d %s" %(key, 20-len(key), EFFECT_MAP[key][0], EFFECT_MAP[key][1]))
    print("\n")


    known_effects = {"mNONE": 0xFF, "mEFCT_UNIQ_WAITING": 91}
    count_effects = {'efctLED': 1, 'efctSound': 1}
    found_effects = {'efctLED': {}, 'efctSound': {}}

    complete_block_field()

    print("typedef struct RBGStateTable_t {")
    for key in COLTOSTRUCT:
        print("%s" % COLTOSTRUCT[key]
              )
    print("} RBGStateTable;\n\n")
    len_statetable = len(STATETABLE)
    len_statetablekeys = len(STATETABLE[0])
    print("static RBGStateTable myStateTable[%d] = {" % len_statetable)
    for idx in range(len_statetable):
        sys.stdout.write("    { /* row %d */ " % idx)
        for count, key in enumerate(STATETABLE[idx]):
            sys.stdout.write(" .%s=%s," % (key, STATETABLE[idx][key]))
            # print("         %s, // %s" % (STATETABLE[idx][key], key))
        print(" },")  # C is no longer picky about the last comma
    print("};")

    ### also the old way
    print("\n// now the old way\n")
    print("static RBGStateTable myStateTable[%d] = {" % len_statetable)
    for idx in range(len_statetable):
        sys.stdout.write("    { /* row %d */ " % idx)
        for count, key in enumerate(STATETABLE[idx]):
            sys.stdout.write(" %s," % (STATETABLE[idx][key]))
        print(" },")  # C is no longer picky about the last comma
    print("};")


if __name__ == "__main__":
    make_state_table()
