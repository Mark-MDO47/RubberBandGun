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
EXCELROWNUMOFFSET = 2 # so we can give error messages
SYMBTABLE = {}
SYMBTABLEROW = { "blockStart": -1, "blockEnd": -1 }
STATETABLE = {}
STATETABLEROW = { "blkFlags": 0, "soundAfterInput": 0, "lights": 0, "inputRBG": 0, "storeVal": 0, "storeAddr": 0, "gotoOnInput": 0, "gotoWithoutInput": 0 }

# INPUT:
COLTOINDEX = {"index": -1, "soundAfterInput": -1, "lights": -1, "inputRBG": -1, "storeVal": -1, "storeAddr": -1, "gotoOnInput": -1, "gotoWithoutInput": -1 }

# OUTPUT:
  # uint8_t soundAfterInput;  // index for sound to make after input match
  # uint8_t lights;           // index for light pattern while waiting
  # uint8_t inputRBG;         // mask for input expected
  # uint8_t storeVal;         // value to store, 8 bit uint
  # uint8_t storeAddr;        // address to store; includes mask for mFUNC, mVAL, eeSoundSave|mFUNC: idx= 1 WindUp, 2 Shoot, 4 Open, 7 Load
  # uint8_t gotoOnInput;      // index within table to go with matching input    
  # uint8_t gotoWithoutInput; // index within table to go without waiting for input


def MarkEndBlock(currSymb, currStateTableIdx):
   global SYMBTABLE
   print("DEBUG CALL MarkEndBlock on currSymb |%s| with currStateTableIdx %s" % (currSymb, currStateTableIdx))
   print("  DEBUG BEFORE %s" % SYMBTABLE)
   if 0 == len(currSymb):
      print("  DEBUG AFTER  %s" % SYMBTABLE)
      return "Tried to MarkEndBlock on zero-length currSymb |%s| with currStateTableIdx %s" % (currSymb, currStateTableIdx)
   print("DEBUG MarkEndBlock on currSymb %s with currStateTableIdx %s" % (currSymb, currStateTableIdx))
   if currSymb in SYMBTABLE.keys():
      SYMBTABLE[currSymb]["blockEnd"] = currStateTableIdx
      print("  DEBUG AFTER  %s" % SYMBTABLE)
      return ""
   else:
      print("  DEBUG AFTER  %s" % SYMBTABLE)
      return "Tried to MarkEndBlock on currSymb %s with currStateTableIdx %s but %s not in SYMBTABLE" % (currSymb, currStateTableIdx, currSymb)

def MakeNewBlock(currSymb: object, currStateTableIdx: object, debugString: object = "debugUNKNOWN") -> object:
   global SYMBTABLE
   global STATETABLE
   if currSymb in SYMBTABLE.keys():
      print("DEBUG NEW %s BEFORE: currStateTableIdx %d SYMBTABLE[%s] %s" % (debugString, currStateTableIdx, currSymb, SYMBTABLE[currSymb]))
   else:
      print("DEBUG NEW %s BEFORE: currStateTableIdx %d %s" % (debugString, currStateTableIdx, currSymb))
   print("  DEBUG SYMBTABLE %s" % SYMBTABLE)
   currStateTableIdx += 1
   STATETABLE[currStateTableIdx] = copy.deepcopy(STATETABLEROW)
   SYMBTABLE[currSymb] = copy.deepcopy(SYMBTABLEROW)
   SYMBTABLE[currSymb]["blockStart"] = currStateTableIdx

   print("DEBUG NEW %s  AFTER: currStateTableIdx %d SYMBTABLE[%s] %s" % (debugString, currStateTableIdx, currSymb, SYMBTABLE[currSymb]))
   print("  DEBUG SYMBTABLE %s" % SYMBTABLE)
   return currStateTableIdx, currSymb

def MakeStateTable():
   global SYMBTABLE
   global STATETABLE
   global COLTOINDEX

   # Import the excel file
   xlsFile = pd.ExcelFile('./StateTable.xlsx')
   df = xlsFile.parse(xlsFile.sheet_names[0])
   
   # map the column names to numbers; will barf if there is a problem
   dfColNames = df.columns.values.tolist()
   for col in COLTOINDEX:
      COLTOINDEX[col] = dfColNames.index(col)

   # read through excel file and generate state table
   STATETABLEIdx = -1    # this will be index into state table we are building
   SYMBTABLECurrent = "" # zero length means not processing any state decision block
   for rowNum, row in df.iterrows():
      # the first row (rowNum == 0) is the one after the column titles
      # rowIndexSymb = str(row[dfColNames["index"]]).strip
      rowIndexSymb = str(row["index"]).strip()
      if "nan" == rowIndexSymb: # rows with nothing in "index" column are ignored except...
         # ... they mark the end of the current state decision block
         """
         err = MarkEndBlock(SYMBTABLECurrent, STATETABLEIdx)
         if 0 != len(err):
            print("DEBUG %s SYMBTABLECurrent |%s| from rows with nothing in index column" % (err, SYMBTABLECurrent))
         print("  DEBUG %s" % SYMBTABLE)
         SYMBTABLECurrent = ""
         """
         continue
   
      if 0 == len(SYMBTABLECurrent): # this is a new symbol, possibly the first symbol
         if STATETABLEIdx >= 0:  # mark end of previous block if there is one
            err = MarkEndBlock(SYMBTABLECurrent, STATETABLEIdx)
         STATETABLEIdx, SYMBTABLECurrent = MakeNewBlock(rowIndexSymb, STATETABLEIdx)
      else: # we were processing a symbol before
         if rowIndexSymb == SYMBTABLECurrent: # continuing on with this state decision block
            STATETABLEIdx += 1
         else: # new state decision block
            if STATETABLEIdx >= 0:  # mark end of previous block if there is one
               err = MarkEndBlock(SYMBTABLECurrent, STATETABLEIdx)
            STATETABLEIdx, SYMBTABLECurrent = MakeNewBlock(rowIndexSymb, STATETABLEIdx)

   print("SYMBTABLE")
   print("  %s" % SYMBTABLE)
   for symb in SYMBTABLE:
      print("  %s %s" % (symb, SYMBTABLE[symb]))

   print("STATETABLE")
   for idx in STATETABLE:
      print("  %d %s" % (idx, STATETABLE[idx]))

   # COLTOINDEX = {"index": "", "soundAfterInput", "lights", "input", "storeVal", "storeAddr", "gotoOnInput", "gotoWithoutInput": "" }

if __name__ == "__main__": 
   MakeStateTable()
   
