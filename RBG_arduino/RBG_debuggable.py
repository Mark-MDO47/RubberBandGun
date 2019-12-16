# Author: Mark Olson 2019-11-03
#
# Rubber Band Gun - https://github.com/Mark-MDO47/RubberBandGun
# RBG - A high-tech imagining of the rubber band gun
#
# This program will read the arduino code for RBG_SciFi.ino and create on stdout a mostly-debuggable form for Microsoft Visual Studio Community 2019
#

import copy
import sys

# README these just make it easier on Microsoft Visual Studio Community Edition 2019
myStringStandardStart = """//
// some helpful standard definitions
//
#define deltaMsLED 5
#define HIGH 1
#define LOW 0
uint32_t millis() { return(0); }
void digitalWrite(uint8_t pin, uint8_t val) {
  printf("call digitalWrite(pin=%d, val=%d", pin, val);
}
uint16_t digitalRead(uint8_t pin) {
  return(HIGH);
}
void delay(uint16_t msec) {
}
"""

# README put latest old way from makeStateTable.py so can debug in Microsoft Visual Studio Community Edition 2019 in Console App
myStringForStateTable ="""//
// now the old way so can debug in Microsoft Visual Studio Community Edition 2019 in Console App
//
static RBGStateTable myStateTable[9] = {
    { /* row 0 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_PWRON, mEFCT_PWRON, mNONE, mNONE, mNONE, mNONE, mROW_MENU, mROW_POWERON, },
    { /* row 1 */  mBLOCKSTART|mBLOCKEND, mSPCL_EFCT_CONTINUOUS|mSPCL_HANDLER | mSPCL_HANDLER_SHOOT, mEFCT_UNIQ_WAITING, mEFCT_UNIQ_WAITING, mINP_TRIG|mINP_BNONE, mNONE, mNONE, mROW_WINDUP, mNONE, mROW_MENU, },
    { /* row 2 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_OPEN_BARREL, mEFCT_OPEN_BARREL, mNONE, mNONE, mNONE, mNONE, mROW_MENU, mROW_OPNBRL, },
    { /* row 3 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_LOCK_LOAD, mEFCT_LOCK_LOAD, mNONE, mNONE, mNONE, mNONE, mROW_MENU, mROW_LOKLOD, },
    { /* row 4 */  mBLOCKSTART|mBLOCKEND, mNONE, mNONE, mNONE, mNONE, mNONE, mNONE, mNONE, mROW_WINDUP_SOUND, mROW_WINDUP, },
    { /* row 5 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_WIND_UP, mEFCT_WIND_UP, mNONE, mNONE, mNONE, mNONE, mROW_SHOOT, mROW_WINDUP_SOUND, },
    { /* row 6 */  mBLOCKSTART|mBLOCKEND, mSPCL_HANDLER | mSPCL_HANDLER_SHOOT, mNONE, mNONE, mNONE, mNONE, mNONE, mNONE, mROW_SHOOT_SOUND, mROW_SHOOT, },
    { /* row 7 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_SHOOT, mEFCT_SHOOT, mNONE, mNONE, mNONE, mNONE, mROW_SOLENOID, mROW_SHOOT_SOUND, },
    { /* row 8 */  mBLOCKSTART|mBLOCKEND, mSPCL_HANDLER | mSPCL_HANDLER_SOLENOID, mNONE, mNONE, mNONE, mNONE, mNONE, mNONE, mROW_MENU, mROW_SOLENOID, },
};
"""

# README put location of  files here
# we will read: RBG_SciFi_StatesAndInputs.h, RBG_SciFi.ino
file_location_no_trail_slash = r'D:\GitHub-Mark-MDO47\RubberBandGun\RBG_arduino\RBG_SciFi'
files_to_read_h = ["RBG_SciFi_StatesAndInputs.h"]
files_to_read_ino = ["RBG_SciFi.ino"]

h_stopread_and_insert = "static RBGStateTable myStateTable"

ino_routines_to_copy = ["processStateTable", "RBG_startRow", "RBG_waitForInput", "RBG_specialProcessing", "RBG_specialProcShoot", "RBG_specialProcSolenoid", "RBG_startEffectSound", "printAllMyState", "printAllMyInputs", "printOneInput"]

def debuggable():

    # standard defs at start
    print("%s" % myStringStandardStart)

    # the *.h file is easy to process
    for fn in files_to_read_h:
        fobj = open(file_location_no_trail_slash+"\\"+fn, 'rt')
        print("\n// following lines from %s\n" % fn)
        theLine = fobj.readline()
        while "" != theLine: # null string means EOF
            theLine = theLine.rstrip()
            if -1 != theLine.find(h_stopread_and_insert):
                print("%s" % myStringForStateTable)
                break
            if (0 != len(theLine)) and (0 != theLine.find("//")): # don't copy the fluff
                print("%s" % theLine)
            theLine = fobj.readline()
        fobj.close()

    # this is the tricky one
    copying = ""
    prototypes = []
    for fn in files_to_read_ino:
        fobj = open(file_location_no_trail_slash+"\\"+fn, 'rt')
        print("\n// following lines from %s\n" % fn)
        theLine = fobj.readline()
        while "" != theLine: # null string means EOF
            theLine = theLine.rstrip()
            if (0 != len(theLine)): # don't copy the fluff
                if 0 == len(copying): # need to look for copying start
                    if ("// " == theLine[0:3]):
                        for routine in ino_routines_to_copy:
                            if 3 == theLine.find(routine):
                                copying = routine
                                print("\n/////////////////////////////////////////////////////////////////////////////////////////////////////////")
                                print("%s" % theLine)
                                break
                else:
                    if (-1 != theLine.find(copying)) and ("{" == theLine[-1]):
                        prototypes.append(theLine[:-1].strip()+";")
                    keep_checking = True
                    while keep_checking:
                        if -1 != theLine.find("Serial.println(F("):
                            theLine = rplc_F(theLine, "Serial.println(F(")
                        elif -1 != theLine.find("Serial.print(F("):
                            theLine = rplc_F(theLine, "Serial.print(F(")
                        elif -1 != theLine.find("Serial.println(\""):
                            theLine = rplc_no_F(theLine, "Serial.println(\"")
                        elif -1 != theLine.find("Serial.print(\""):
                            theLine = rplc_no_F(theLine, "Serial.print(\"")
                        elif -1 != theLine.find("Serial.println("):
                            theLine = rplc_normal(theLine, "Serial.println(")
                        elif -1 != theLine.find("Serial.print("):
                            theLine = rplc_normal(theLine, "Serial.print(")
                        elif -1 != theLine.find("myDFPlayer.playMp3Folder"):
                            theLine = theLine.replace("myDFPlayer.playMp3Folder", "// myDFPlayer.playMp3Folder")
                        else:
                            keep_checking = False
                    if ("}" == theLine[0]) and (-1 != theLine.find("end " + copying)):
                        copying = ""
                    print("%s" % theLine)
            theLine = fobj.readline()
    if 0 != len(prototypes):
        print("\n\n//\n// Prototypes: place at the front\n//")
        for proto in prototypes:
            print("%s" % proto)

def rplc_F(theLine, theRplc): # to handle weird Serial.printx(F("")); replaces
    tmp = theLine.find(theRplc) # where it starts
    str1 = theLine[:tmp]
    str2 = theLine[tmp:]
    str2 = str2.replace(theRplc, "printf(", 1)
    str2 = str2.replace("));", ");", 1)
    return str1 + str2

def rplc_no_F(theLine, theRplc): # to handle weird Serial.printx(""); replaces
    tmp = theLine.find(theRplc) # where it starts
    str1 = theLine[:tmp]
    str2 = theLine[tmp:]
    str2 = str2.replace(theRplc, "printf(\"", 1)
    return str1 + str2

def rplc_normal(theLine, theRplc): # to handle normal Serial.printx(); replaces
    tmp = theLine.find(theRplc) # where it starts
    str1 = theLine[:tmp]
    str2 = theLine[tmp:]
    str2 = str2.replace(theRplc, "printf(\"%04X\", ")
    str2 = str2.replace(", HEX", "", 1)
    return str1 + str2


if __name__ == "__main__":
    debuggable()
