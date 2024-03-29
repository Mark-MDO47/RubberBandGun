# Author: Mark Olson 2019-11-03
#
# Rubber Band Gun - https://github.com/Mark-MDO47/RubberBandGun
# RBG - A high-tech imagining of the rubber band gun
#
# This program will read the arduino code for RBG_SciFi.ino and create on stdout a mostly-debuggable form for Microsoft Visual Studio Community 2019
# Used mostly to debug the state table machine.
#

# import copy
# import sys

myFirstInclude = """
// DebugRBG01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

static uint32_t globalLoopCount = 0;

"""

# some other inputs for testing
"""
} myInputs[] = { // for open barrel
        mVINP_LOCK, " // mVINP_LOCK row 0 start",
        mVINP_LOCK | mVINP_SOUNDACTV, " // mVINP_LOCK|mVINP_SOUNDACTV row 0 FOOF RBG Gun 1.0",
        mVINP_LOCK, " // mVINP_LOCK row 0 end of FOOF, go to row 1",
        mVINP_LOCK | mVINP_SOUNDACTV, " // mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " // mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " // mVINP_LOCK row 1 restart sound",
        mVINP_LOCK | mVINP_SOUNDACTV, " // mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_OPEN | mVINP_SOUNDACTV, " // mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active but barrel opens",
        mVINP_OPEN, " // mVINP_OPEN barrel open sound no longer active",
        mVINP_OPEN | mVINP_SOUNDACTV, " // mVINP_OPEN|mVINP_SOUNDACTV barrel open sound active again "
}; // myInputs for open barrel

    } myInputs[] = { // for Trigger
        mVINP_LOCK,                " mVINP_LOCK row 0 start",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 0 FOOF RBG Gun 1.0",
        mVINP_LOCK,                " mVINP_LOCK row 0 end of FOOF, go to row 1",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK,                  " mVINP_LOCK row 1 restart sound",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mINP_TRIG | mVINP_SOUNDACTV, " mVINP_LOCK|mINP_TRIG|mVINP_SOUNDACTV row 1 waiting sound active but TRIGGER",
        mVINP_LOCK | mINP_TRIG | mVINP_SOUNDACTV, " mVINP_LOCK|mINP_TRIG|mVINP_SOUNDACTV sound no longer active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV windup sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV windup sound still active",
        mVINP_LOCK, " mVINP_LOCK should switch to SHOOT",
        mVINP_LOCK, " mVINP_LOCK should switch to SHOOT",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV should switch to SHOOT"
    }; // myInputs for Trigger

    } myInputs[] = { // for continuous
        mVINP_LOCK,                " mVINP_LOCK row 0 start",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 0 FOOF RBG Gun 1.0",
        mVINP_LOCK,                " mVINP_LOCK row 0 end of FOOF, go to row 1",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
    }; // myInputs for continuous

    } myInputs[] = { // for continuous restart
        mVINP_LOCK,                " mVINP_LOCK row 0 start",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 0 FOOF RBG Gun 1.0",
        mVINP_LOCK,                " mVINP_LOCK row 0 end of FOOF, go to row 1",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK | mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
    }; // myInputs for continuous restart

    } myInputs[] = { // for continuous restart and trigger
        mVINP_LOCK,                " mVINP_LOCK row 0 start",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 0 FOOF RBG Gun 1.0",
        mVINP_LOCK|mVINP_SOUNDACTV,  " mVINP_LOCK|mVINP_SOUNDACTV still at row 0 FOOF RBG Gun 1.0",
        mVINP_LOCK,                " mVINP_LOCK row 0 end of FOOF, go to row 1",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",	
        mVINP_LOCK|mVINP_SOUNDACTV	, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV|mVINP_TRIG,  "mVINP_LOCK|mVINP_SOUNDACTV|mVINP_TRIG go from 1 to 4",
        mVINP_LOCK, " mVINP_LOCK shoot",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV after shoot",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV after shoot",	
        mVINP_LOCK, " mVINP_LOCK go from 4 to 7",
        mVINP_LOCK, " mVINP_LOCK ???",
        mVINP_LOCK, " mVINP_LOCK ???",
        mVINP_LOCK|mVINP_TRIG, " mVINP_LOCK|mVINP_TRIG go from 1 to 4"
        mVINP_LOCK, " mVINP_LOCK shoot",	
    }; // myInputs for continuous restart and trigger
"""

# this is the main routine in Microsoft Visual Studio Community Edition 2019
myMain = """
int main()
{
    uint16_t nowVinputRBG;
    static struct {
        uint16_t input;
        const char* str;
    } myInputs[] = { // for continuous restart and trigger
        mVINP_LOCK,                " mVINP_LOCK row 0 start",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 0 FOOF RBG Gun 1.0",
        mVINP_LOCK|mVINP_SOUNDACTV,  " mVINP_LOCK|mVINP_SOUNDACTV still at row 0 FOOF RBG Gun 1.0",
        mVINP_LOCK,                " mVINP_LOCK row 0 end of FOOF, go to row 1",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",	
        mVINP_LOCK|mVINP_SOUNDACTV	, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK, " mVINP_LOCK row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV row 1 waiting sound active",
        mVINP_LOCK|mVINP_SOUNDACTV|mVINP_TRIG,  "mVINP_LOCK|mVINP_SOUNDACTV|mVINP_TRIG go from 1 to 4",
        mVINP_LOCK, " mVINP_LOCK shoot",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV after shoot",
        mVINP_LOCK|mVINP_SOUNDACTV, " mVINP_LOCK|mVINP_SOUNDACTV after shoot",	
        mVINP_LOCK, " mVINP_LOCK go from 4 to 7",
        mVINP_LOCK, " mVINP_LOCK ???",
        mVINP_LOCK, " mVINP_LOCK ???",
        mVINP_LOCK|mVINP_TRIG, " mVINP_LOCK|mVINP_TRIG go from 1 to 4",
        mVINP_LOCK, " mVINP_LOCK shoot",	
    }; // myInputs for continuous restart and trigger

    std::cout << "Hello World!\\n";
    myState.tableRow = 0;
    myState.VinputRBG = 0x0;
    for (int idx = 0; idx < NUMOF(myInputs); idx++) {
        printf("\\n$$$$ VS DEBUGGING idx %d value 0x%04X %s $$$$\\n", idx, myInputs[idx].input, myInputs[idx].str);
        myState.timerNow = millis();
        if (myState.VinputRBG & mVINP_LOCK) {
            myState.VinputRBG |= mVINP_PREVLOCK; // set the bit
        }
        else {
            myState.VinputRBG &= ((uint16_t)~(mVINP_PREVLOCK)); // clear the bit
        }

        nowVinputRBG = myInputs[idx].input; // nowVinputRBG = getButtonInput();
        if (myState.VinputRBG != nowVinputRBG) { printf("DEBUG loop() - nowVinputRBG 0x%04X loopCount %d\\n", nowVinputRBG, globalLoopCount); }
        nowVinputRBG = processStateTable(nowVinputRBG);

        myState.VinputRBG = nowVinputRBG;
        myState.timerPrev = myState.timerNow;
        printAllMyState();
        globalLoopCount += 1;
    } // end for next input
    printf("DONE");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
"""

# README these just make it easier to use Microsoft Visual Studio Community Edition 2019
myStringStandardStart = """//
// some helpful standard definitions
//
#define deltaMsLED 5
#define HIGH 1
#define LOW 0
"""

# README put latest old way from makeStateTable.py so can debug in Microsoft Visual Studio Community Edition 2019 in Console App
myStringForStateTable ="""//
// now the old way so can debug in Microsoft Visual Studio Community Edition 2019 in Console App
//
static RBGStateTable_t myStateTable[10] = {
    { /* row 0 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_PWRON, mEFCT_PWRON, mNONE, mNONE, mNONE, mNONE, mROW_MENU, mROW_POWERON, },
    { /* row 1 */  mBLOCKSTART, mSPCL_EFCT_CONTINUOUS, mEFCT_UNIQ_WAITING, mEFCT_UNIQ_WAITING, mINP_TRIG|mINP_BNONE, mNONE, mNONE, mROW_WINDUP_SOUND, mNONE, mROW_MENU, },
    { /* row 2 */  mZERO, mSPCL_EFCT_CONTINUOUS, mEFCT_UNIQ_WAITING, mEFCT_UNIQ_WAITING, mINP_OPEN, mNONE, mNONE, mROW_OPNBRL, mNONE, mROW_MENU, },
    { /* row 3 */  mBLOCKEND, mSPCL_EFCT_CONTINUOUS, mEFCT_UNIQ_WAITING, mEFCT_UNIQ_WAITING, mINP_LOCK, mNONE, mNONE, mROW_LOKLOD, mNONE, mROW_MENU, },
    { /* row 4 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_WIND_UP, mEFCT_WIND_UP, mNONE, mNONE, mNONE, mNONE, mROW_SHOOT, mROW_WINDUP_SOUND, },
    { /* row 5 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_OPEN_BARREL, mEFCT_OPEN_BARREL, mNONE, mNONE, mNONE, mNONE, mROW_MENU, mROW_OPNBRL, },
    { /* row 6 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_LOCK_LOAD, mEFCT_LOCK_LOAD, mNONE, mNONE, mNONE, mNONE, mROW_MENU, mROW_LOKLOD, },
    { /* row 7 */  mBLOCKSTART|mBLOCKEND, mSPCL_HANDLER | mSPCL_HANDLER_SHOOT, mNONE, mNONE, mNONE, mNONE, mNONE, mNONE, mROW_SHOOT_SOUND, mROW_SHOOT, },
    { /* row 8 */  mBLOCKSTART|mBLOCKEND, mNONE, mEFCT_SHOOT, mEFCT_SHOOT, mNONE, mNONE, mNONE, mNONE, mROW_SOLENOID, mROW_SHOOT_SOUND, },
    { /* row 9 */  mBLOCKSTART|mBLOCKEND, mSPCL_HANDLER | mSPCL_HANDLER_SOLENOID, mNONE, mNONE, mNONE, mNONE, mNONE, mNONE, mROW_MENU, mROW_SOLENOID, },
};
"""

# README put location of  files here
# we will read: RBG_SciFi_StatesAndInputs.h, RBG_SciFi.ino
file_location_no_trail_slash = r'D:\GitHub-Mark-MDO47\RubberBandGun\RBG_arduino\RBG_SciFi'
files_to_read_h = ["RBG_SciFi_StatesAndInputs.h"]
files_to_read_ino = ["RBG_SciFi.ino"]

h_stopread_and_insert = "static RBGStateTable_t myStateTable"
h_typedefs_for_prototypes = ["typedef struct _decodeBits_t"] # we expect these typedefs to be all on one line
print_typedefs_for_prototypes = []
myStubs ="""void myMdoDFPlayer_playMp3Folder(uint16_t mySound) { printf("call playMp3Folder %04d\\n", mySound); }
bool myMdoDFPlayer_available() { return(false); }
uint16_t myMdoDFPlayer_readType()  { return(0); }
uint16_t myMdoDFPlayer_read() { return(0); }
uint16_t DFprintDetail(uint16_t parm1, uint16_t parm2) { return(0); }
uint32_t millis() { return(0); }
void digitalWrite(uint8_t pin, uint8_t val) { printf("call digitalWrite(pin=%d, val=%d)\\n", pin, val); }
uint16_t digitalRead(uint8_t pin) { return(HIGH); }
void delay(uint16_t msec) { }

"""

ino_routines_to_copy = ["processStateTable", "RBG_startRow", "RBG_waitForInput", "RBG_specialProcessing", "RBG_specialProcShoot", "RBG_specialProcSolenoid", "RBG_startEffectSound", "printAllMyState", "printExplainBits", "printAllMyInputs", "printOneInput"]

# transmogrify the Arduino code to something that can be debugged using Microsoft Visual Studio Community Edition 2019
def debuggable():

    # this is the include of iostream
    print(myFirstInclude)

    myDebugLines = []

    # the *.h file is easy to process
    for fn in files_to_read_h:
        fobj = open(file_location_no_trail_slash+"\\"+fn, 'rt')
        myDebugLines.append("\n// following lines from %s\n" % fn)
        theLine = fobj.readline()
        while "" != theLine: # null string means EOF
            theLine = theLine.rstrip()
            if -1 != theLine.find(h_stopread_and_insert):
                myDebugLines.append("%s" % myStringForStateTable)
                break
            for myTypedef in h_typedefs_for_prototypes: # save the single-line typedefs needed for the function prototypes
                if -1 != theLine.find(myTypedef):
                    print_typedefs_for_prototypes.append(theLine)
                    theLine = ""
            if (0 != len(theLine)) and (0 != theLine.find("//")): # don't copy the fluff
                myDebugLines.append("%s" % theLine)
            theLine = fobj.readline()
        fobj.close()

    # this is the tricky one - the *.ino code
    copying = ""
    prototypes = []
    for fn in files_to_read_ino:
        fobj = open(file_location_no_trail_slash+"\\"+fn, 'rt')
        myDebugLines.append("\n// following lines from %s\n" % fn)
        theLine = fobj.readline()
        while "" != theLine: # null string means EOF
            theLine = prepare(theLine)
            theLine = theLine.replace("strcpy(printAsText,", "strcpy_s(printAsText, NUMOF(printAsText),")
            theLine = theLine.replace("strcat(printAsText,", "strcat_s(printAsText, NUMOF(printAsText),")
            theLine = theLine.replace("mySound += EEPROM.read(EEPOFFSET(tmpEfctSound));", "mySound += 1; // assume it is one")
            if (0 != len(theLine)): # don't copy the fluff
                if 0 == len(copying): # need to look for copying start
                    if ("// " == theLine[0:3]):
                        for routine in ino_routines_to_copy:
                            if 3 == theLine.find(routine):
                                copying = routine
                                myDebugLines.append("\n/////////////////////////////////////////////////////////////////////////////////////////////////////////")
                                myDebugLines.append("%s" % theLine)
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
                        elif (-1 != theLine.find("Serial.println(printAsText")):
                            theLine = theLine.replace("Serial.println(printAsText", "printf(\"%s\\n\", printAsText")
                        elif (-1 != theLine.find("Serial.print(printAsText")):
                            theLine = theLine.replace("Serial.print(printAsText", "printf(\"%s\", printAsText")
                        elif -1 != theLine.find("Serial.println(\""):
                            theLine = rplc_no_F(theLine, "Serial.println(\"")
                        elif -1 != theLine.find("Serial.print(\""):
                            theLine = rplc_no_F(theLine, "Serial.print(\"")
                        elif -1 != theLine.find("Serial.println("):
                            theLine = rplc_normal(theLine, "Serial.println(")
                        elif -1 != theLine.find("Serial.print("):
                            theLine = rplc_normal(theLine, "Serial.print(")
                        elif -1 != theLine.find("myDFPlayer."):
                            theLine = theLine.replace("myDFPlayer.", "myMdoDFPlayer_") # don't let this repeat forever
                        else:
                            keep_checking = False
                    if ("}" == theLine[0]) and (-1 != theLine.find("end " + copying)):
                        copying = ""
                    myDebugLines.append("%s" % theLine)
            theLine = fobj.readline()

    #
    # Now we do all the prints
    #   1) typedef(s) needed by prototypes
    #   2) prototypes (Arduino auto generates these but needed for Visual Studio)
    #   3) standard defs and stubs
    #   4) all the other lines collected from the Arduino *.h and *.ino files
    #   5) our VS main() routine including the inputs to test
    #
    for myTypedef in print_typedefs_for_prototypes:
        print("%s" % myTypedef)
    if 0 != len(prototypes):
        print("\n\n//\n// Prototypes: place at the front\n//")
        for proto in prototypes:
            print("%s" % proto)
    print("\n\n//\n// Stub routines:\n//")
    # standard defs at start
    print("%s" % myStringStandardStart)
    print("%s" % myStubs)
    for line in myDebugLines:
        print("%s" % line)
    print(myMain)

def rplc_F(theLine, theRplc): # to handle weird Serial.printx(F("")); replaces
    tmp = theLine.find(theRplc) # where it starts
    str1 = theLine[:tmp]
    str2 = theLine[tmp:]
    str3 = str2[:str2.find(";")] # limit println search to this call
    str2 = str2.replace(theRplc, "printf(", 1)
    str2 = str2.replace("));", ");", 1)
    if -1 != str3.find("println"):
        str2 = str2.replace(");", "); printf(\"\\n\");", 1)
    return str1 + str2

def rplc_no_F(theLine, theRplc): # to handle weird Serial.printx(""); replaces
    tmp = theLine.find(theRplc) # where it starts
    str1 = theLine[:tmp]
    str2 = theLine[tmp:]
    str3 = str2[:str2.find(";")] # limit println search to this call
    str2 = str2.replace(theRplc, "printf(\"", 1)
    if -1 != str3.find("println"):
        str2 = str2.replace(");", "); printf(\"\\n\");", 1)
    return str1 + str2

def rplc_normal(theLine, theRplc): # to handle normal Serial.printx(); replaces
    tmp = theLine.find(theRplc) # where it starts
    str1 = theLine[:tmp]
    str2 = theLine[tmp:]
    str3 = str2[:str2.find(";")] # limit println and HEX search to this call
    if (-1 != str3.find(", HEX")):
        str2 = str2.replace(theRplc, "printf(\"%04X\", ", 1)
        str2 = str2.replace(", HEX", "", 1)
    else:
        str2 = str2.replace(theRplc, "printf(\"%d\", ", 1)
    if -1 != str3.find("println"):
        str2 = str2.replace(");", "); printf(\"\\n\");", 1)
    return str1 + str2

def prepare(theLine):
    myLine = theLine # what's my line :^)
    myLine = myLine.rstrip()
    """
    theSplit = myLine.split("\n")
    myLine = ""
    for idx, mySplit in enumerate(theSplit):
        myLine += mySplit
        if (idx+1) != len(theSplit):
            myLine += "\\n"
    """
    return myLine

if __name__ == "__main__":
    debuggable()
