#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port

#define DPIN_SIMPLENEO    2  // serial out - talk to single LED in handle
#define DPIN_FASTLED      3  // serial out - talk to LED rings
#define DPIN_BLUESRL_RX   4  // serial in  - talk to Bluetooth module (KCX_BT_EMITTER)
#define DPIN_BLUESRL_TX   5  // serial out  - talk to Bluetooth module (KCX_BT_EMITTER)
#define DPIN_LOCK_LOAD    8  // digital input - grounded when in lock and load position
#define DPIN_SWSRL_RX    10  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_TX    11  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY  12  // digital input - signals when audio finishes
#define DPIN_SOLENOID    13  // often has internal LED and resistor soldered to board, can make INPUT not work

#define APIN_BTN_TRIGGER  4  // analog input - the trigger (we only count once per trigger press)
#define APIN_BTN_YELLOW   5  // analog input - yellow configuration button
#define APIN_BTN_GREEN    6  // analog input - green configuration button
#define APIN_BTN_RED      7  // analog input - blue configuration button

#define NUMWAIT  3000

SoftwareSerial myBlueSerial(DPIN_BLUESRL_RX, DPIN_BLUESRL_TX); // to talk to Bluetooth 

// SoftwareSerial myYX5200Serial(DPIN_SWSRL_RX, DPIN_SWSRL_TX);   // to talk to YX5200 audio player
// DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player
// void DFsetup();                                                // how to initialize myDFPlayer


char inByte[1024];
unsigned int idx = 0;
unsigned int odx = 0;
unsigned int  idxBaud = 0;
char cmd1[32] = "AT+";
char cmd2[32] = "AT+REST";
char cmd3[32] = "AT+GMR";
char cmd4[32] = "AT+STATUS";
char cmd5[32] = "AT+VMLINK?";
char cmd6[32] = "AT+DISCON";
char cmd7[32] = "AT+ADDLINKADD=0xf44efdecd39d"; // NOTE: must be exactly 12 characters for hex string
char cmd8[32] = "AT+ADDLINKNAME=S1 Pro MDO";
char cmd9[32] = "AT+VMLINK?";
char cmd10[32] = "AT+";
#define NUMBAUDS 10
int long bauds[NUMBAUDS] = { 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600 };

// program
// #define NUMCMDS  10
// char * cmds[NUMCMDS] = { cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, cmd8, cmd9, cmd10 };

// examine
#define NUMCMDS 5
char * cmds[NUMCMDS] = { cmd1, cmd2, cmd3, cmd4, cmd5 };

unsigned int reportBlueCom();
void sendBlueCmd( char * cmd );

void setup() {

  Serial.begin(115200);         // this is for general debug
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println();
  Serial.println("Bluetooth testing init...");

  myBlueSerial.begin(9600); // this is control for Bluetooth module (KCX_BT_EMITTER)

}  // end setup()

void loop() {

  // testRx();
  // testEcho();
  testCmds();

} // end loop()

void testRx() {

  reportBlueCom();

}
void testEcho() {

  idx = 0;
  while (Serial.available()) {
    inByte[idx++] = Serial.read(); // this side is faster
  }
  if (idx > 0) {
    odx = 0;
    for (odx = 0; odx < idx; odx += 1) {
      if (inByte[odx] > ' ') {
        myBlueSerial.print(inByte[odx]);
      }
      Serial.print(inByte[odx]);
    }
    idx = 0;
  } // if anything to send to Bluetooth chip
  
  reportBlueCom();

} // end test1()

void testCmds() {

  int cmdIdx;

  for (cmdIdx = 0; cmdIdx < NUMCMDS; cmdIdx += 1) {
    Serial.println("");
    Serial.print("--CMD ");
    Serial.print(cmdIdx);
    Serial.print(" ");
    Serial.println(cmds[cmdIdx]);
    sendBlueCmd(cmds[cmdIdx]);
  }

  delay(100);

}

char * msgDetect[] = { "POWER ON", "ALL Devices=", "New Devices:", "CONNECTED", "DISCONNECT" };
// enum myMsgDetect
unsigned int reportBlueCom() {
  unsigned int idx = 0;
  while (myBlueSerial.available()) {
    inByte[idx++] = myBlueSerial.read();
  }
  if (idx > 0) {
    odx = 0;
    for (odx = 0; odx < idx; odx += 1) {
      Serial.print(inByte[odx]);
    }
  } // if anything received from Bluetooth chip
  return(idx);
} // end reportBlueCom

void sendBlueCmd( char * cmd ) {
  int loopIdx;
  // Serial.println(cmd); // send this before sending to device
  myBlueSerial.print(cmd);
  for (loopIdx = 0; loopIdx < NUMWAIT; loopIdx += 1) {
    reportBlueCom();
    delay(5);
  }
} // end sendBlueCmd
