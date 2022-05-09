# Author: Mark Olson 2020-01-18
#
# Rubber Band Gun - https://github.com/Mark-MDO47/RubberBandGun
# RBG - A high-tech imagining of the rubber band gun
#
# This crude program will read from the state table spreadsheet for the RBG, extract the unique sounds, and create
#    a bash file to generate a *.wav file for further audio processing.
# The bash file invokes the "original" eSpeak program. This produces sounds with a robotic flavor, which I wanted.
#    Kudos to (email)   jonsd at users dot sourceforge.net  for creating eSpeak
#    Kudos to Reece H. Dunn for continuing the good work
# I used eSpeak version 1.48.04
#
#
# After creating text file(s), this is how I processed them:
#    open file in Audacity, set to mono if not already set
#    duplicate the track (select track, then Edit->Duplicate)
#    reverse one of the tracks (select track, then Effect->Reverse)
#    select reversed track and change pitch (Effect->ChangePitch, choose -2 semitones)
#    for both tracks one at a time, echo effect (Effect->Echo, choose DelayTime about 0.01 sec and DecayFactor about 0.5)
#    select reversed track and reverse it back to normal order (select track, then Effect->Reverse)
#    select both tracks (ctrl-A) then render (Tracks->Mix->MixAndRender)
#    save as 22050Hz mono, "WAV (microsoft) signed 16-bit PCM"
#
# The following resources are available as shown; they are not included in the RBG repository.
#
# The original eSpeak text to speech code and compiled versions can be found at
#    http://espeak.sourceforge.net/
#        Note that eSpeak project is inactive since disappearance of Jonathan Duddington.
#        Active development and support now happens in eSpeak NG project
#        https://github.com/espeak-ng/espeak-ng maintained by Reece H. Dunn.
#        Mailing list of espeak-ng project is https://groups.io/g/espeak-ng
# A web implementation of eSpeak can be found as below; it is great fun, and just one of many STT engines on the site.
#    https://lingojam.com/RobotVoiceGenerator
#
# Audacity: https://www.audacityteam.org/
#

myPattern = "#define mEFCT_UNIQ_"
COLTOINDEX =  {"usage": -1, "num": -1, "File Name": -1, "Description": -1, "all usage": -1, "License": -1, "Who": -1, "URL": -1, "Mnemonic": -1, "#define": -1}

# import io
# import sys
import pandas as pd

def readSounds():
    # Import the excel file
    xls_file = pd.ExcelFile(r'd:/GitHub-Mark-MDO47/RubberBandGun/RBG_arduino/StateTable_minimal.xlsx')
    idx = xls_file.sheet_names.index('Sounds')
    df = xls_file.parse(xls_file.sheet_names[idx])

    # map the column names to numbers; will barf if there is a problem
    df_col_names = df.columns.values.tolist()
    for col in COLTOINDEX:
        COLTOINDEX[col] = df_col_names.index(col)

    totString = "Ah. Ah. Ah. "
    for row_num, row in df.iterrows():
        # the first row (row_num == 0) is the one after the column titles
        row_index_num = str(row["num"]).strip()
        if 'END' == row_index_num:
            break
        row_index_Mnemonic = str(row["Mnemonic"]).strip()
        if 0 != row_index_Mnemonic.find('mEFCT_UNIQ_'):
            continue
        row_index_Desc = str(row["Description"]).strip()
        if -1 == row_index_Desc.find("mdo47 recording of "):
            continue
        row_index_Desc = row_index_Desc[1 + row_index_Desc.find('"'):] # remove up to first "
        row_index_Desc = row_index_Desc[:row_index_Desc.find('"')] # remove second " and beyond
        row_index_fname = str(row["File Name"]).strip()
        if len(totString) > 0:
            totString += " Ah. Ah. Ah. "
        totString += row_index_Desc
        if len(row_index_fname) > 0:
            print("espeak -g 5 -v en-us -w raw_%s \"%s\"" % (row_index_fname, row_index_Desc))
    print("\nespeak -g 5 -v en-us -w totString.wav \"%s\"" % totString)

if __name__ == "__main__":
    readSounds()


