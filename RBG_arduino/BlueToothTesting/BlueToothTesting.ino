#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port

#define DPIN_BLUESRL_RX   9  // serial in  - talk to Bluetooth module (KCX_BT_EMITTER) - connect to GREEN wire
#define DPIN_BLUESRL_TX   2  // serial out  - talk to Bluetooth module (KCX_BT_EMITTER) - connect to YELLOW wire

#define NUMWAIT  3000

SoftwareSerial myBlueSerial(DPIN_BLUESRL_RX, DPIN_BLUESRL_TX); // to talk to Bluetooth 


char inByte[100];
char const * cmd1 = "AT+";
char const * cmd2 = "AT+REST";
char const * cmd3 = "AT+GMR";
char const * cmd4 = "AT+STATUS";
char const * cmd5 = "AT+VMLINK?";
char const * cmd6 = "AT+DISCON";
char const * cmd7 = "AT+ADDLINKADD=0xf44efdecd39d"; // NOTE: must be exactly 12 characters for hex string
char const * cmd8 = "AT+ADDLINKNAME=S1 Pro MDO";
char const * cmd9 = "AT+VMLINK?";
char const * cmd10 = "AT+";

// #define NUMBAUDS 10
// int long bauds[NUMBAUDS] = { 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600 };

// program
// #define NUMCMDS  10
// char const * cmds[NUMCMDS] = { cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, cmd8, cmd9, cmd10 };

// examine
#define NUMCMDS 5
char const * cmds[NUMCMDS] = { cmd1, cmd2, cmd3, cmd4, cmd5 };

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
  testEcho();
  // testCmds();

} // end loop()

void testRx() {

  reportBlueCom();

}
void testEcho() {

  static char inByte[100];
  static unsigned char mychar;
  static unsigned int idx = 0;
  static unsigned int odx = 0;

  while (Serial.available()) {
    mychar = Serial.read(); // this side is faster
    if (((int) mychar) >= 0x20) { // if it is space or higher
      inByte[idx++] = mychar;
      delay(5);
    } else {
      printf("\neol char 0x%02X\n", (int) mychar);
      while (Serial.available()) {
        mychar = Serial.read(); // this side is faster
        printf("\neol char 0x%02X\n", (int) mychar);
        delay(5);
      }
      break;
    }
  } // end try to read input to the end of line
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
    sendBlueCmd((char *) cmds[cmdIdx]);
  }

  delay(100);

}

unsigned int reportBlueCom() {

  unsigned int idx = 0;
  unsigned int odx = 0;

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
