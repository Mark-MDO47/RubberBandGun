#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port

#define DPIN_SIMPLENEO    2  // serial out - talk to single LED in handle
#define DPIN_FASTLED      3  // serial out - talk to LED rings
#define DPIN_BTN_TRIGGER  4  // digital input - the trigger (we only count once per trigger press)
#define DPIN_BTN_YELLOW   5  // digital input - yellow (or red) configuration button
#define DPIN_BTN_GREEN    6  // digital input - green configuration button
#define DPIN_BLUESRL_RX   7  // serial in  - talk to Bluetooth module (KCX_BT_EMITTER)
#define DPIN_LOCK_LOAD    8  // digital input - grounded when in lock and load position
#define DPIN_BLUESRL_TX   9  // serial out  - talk to Bluetooth module (KCX_BT_EMITTER)
#define DPIN_SWSRL_RX    10  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_TX    11  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY  12  // digital input - signals when audio finishes
#define DPIN_SOLENOID    13  // often has internal LED and resistor soldered to board, can make INPUT not work

#define NUMBAUDS 10
#define NUMCMDS  3
#define NUMWAIT  1000

SoftwareSerial myBlueSerial(DPIN_BLUESRL_RX, DPIN_BLUESRL_TX); // to talk to Bluetooth 
char inByte[1024];
unsigned int idx = 0;
unsigned int odx = 0;
unsigned int  idxBaud = 0;
char cmd1[32] = "AT+";
char cmd2[32] = "AT+\n";
char cmd3[32] = "AT+\r\n";
int long bauds[NUMBAUDS] = { 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600 };
char * cmds[NUMCMDS] = { cmd1, cmd2, cmd3 };

unsigned int reportBlueCom();
void sendBlueCmd( char * cmd );

void setup() {

  Serial.begin(115200);         // this is for general debug
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println();
  Serial.println("Bluetooth testing init...");


}  // end setup()

void loop() {
  int cmdIdx;

  Serial.println("");
  Serial.print("Baud Rate ");
  Serial.println(bauds[idxBaud]);
  myBlueSerial.begin(bauds[idxBaud]); // this is control for Bluetooth module (KCX_BT_EMITTER)

  for (cmdIdx = 0; cmdIdx < NUMCMDS; cmdIdx += 1) {
    Serial.println("");
    Serial.print("--CMD ");
    Serial.println(cmdIdx);
    sendBlueCmd(cmds[cmdIdx]);
  }

  myBlueSerial.end();
  idxBaud += 1;
  if (idxBaud >= NUMBAUDS) { idxBaud = 0; }
  delay(100);
/*
  idx = 0;
  while (Serial.available()) {
    inByte[idx++] = Serial.read(); // this side is faster
  }
  if (idx > 0) {
    odx = 0;
    for (odx = 0; odx < idx; odx += 1) {
      myBlueSerial.print(inByte[odx]);
      Serial.print(inByte[odx]);
    }
    idx = 0;
  } // if anything to send to Bluetooth chip
  
  reportBlueCom();
  */

} // end loop()

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
