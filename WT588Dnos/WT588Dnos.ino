/*
 * This code originally came from:
 *    Getting the Most Out of a WT588D Sound Module
 *    https://www.instructables.com/id/Getting-the-Most-Out-of-a-WT588D-Sound-Module/
 *    By FlyingDrMike in CircuitsElectronics
 *
 * This code supports Three-line serial interface control mode of the WT588D
 * 
 */

/*
 * This information from "WT588D CHIP&MODULE DETAILED INFORMATION.doc" section 1.6.2 "SPEECH AND COMMAND"
 * 
 * selecting an audio file by number (0x00 to 0xDA)
 * commands other than selecting an audio file by number:
 * CODE       FUNCTION            DESCRIPTION
 * E0H-E7H    VOLUME ADJUSTMENT   DURING THE PLAYING OR STANDBY,8 LEVEL VOLUME CAN BE ADJUSTED BY SENDING COMMAND, E0H IS MINIMUM, E7H IS MAXIMUM
 * F2H        LOOP                PLAY DURING THE PLAY, SPEECH IN CURRENT ADDRESS CAN BE LOOP PLAYED BY SENDING COMMAND
 * FEH        STOP PLAY           THE COMMAND OF STOP PLAYING
 * F5H        ENTRY I/O           IN THE COMMOND THREE-LINE SERIAL MODE,
 *              EXTENSION OUTPUT     ENTER I/O EXTENSION OUTPUT STATE BY SENDING 0xF5 COMMAND
 * F6H        EXIT I/O            IN THE I/O EXTENSION OUTPUT STATE
 *              EXTENSION OUTPUT     ENTER COMMOND THREE-LINE SERIAL MODE BY SENDING 0xF6 COMMAND
 *
 * Mark Olson comments:
 * I don't see a reason to use I/O Extension Output mode
 * Comments in forums indicate volume 0xE5 is default and settings above that are noisy
 * 
 * The sequence below is is based on the timing diagram in "WT588D CHIP&MODULE DETAILED INFORMATION.doc"
 *     see section 12.6.5 "THREE-LINE SERIAL CONTROL TIMING"
 * In WT588D timing diagram (not the code from the article), serial bits sent as follows:
 *    RST, CS, CLK all high; DAT is don't care. NOTE: clock cycle is anywhere from 40 microsec to 2 millisec per bit
 *    RST goes low for two milliseconds then back high
 *    wait for 17 milliseconds
 * At this point the code below and the timing diagram merge
 *    CS goes low and then stays low until at least 2 millisec past last CLK-to-high transition
 *    CS still low; wait 2 milliseconds
 *    CS still low; CLK goes low; wait 20 microseconds or more
 *    CS still low; DAT to lsbit (bit 0); wait ???
 *    CS still low; CLK goes high; wait 20 microseconds or more
 *    CS still low; repeat above 3 steps for remaining 7 bits
 *    CS still low; wait 2 milliseconds
 *    CS still low; diagram shows hold CS low until busy goes high then low but PROBABLY can raise CS here
 * 
 * code below does not use the RSTpin; the Instructables article did not use it
 * I fixed a few typos etc. in the original code. Also changed the output pins.
 * 
 */
const int CSpin = 11;
const int CLKpin = 12;
const int DATpin = 10;
//const int RSTpin = 5;

byte Num = 0;

// 3 wire send data to WT588D
void WT588D(byte data){

  digitalWrite(CSpin,LOW);
  delay(2);
  
  for(byte i=0;i<8;i++) {
    digitalWrite(CLKpin,LOW);
    if(data & 1 == 1){
      digitalWrite(DATpin, HIGH);
    } else {
      digitalWrite(DATpin, LOW);
    }
    delayMicroseconds(25);
    digitalWrite(CLKpin,HIGH);
    delayMicroseconds(25);
    data = data>>1;
  }
  digitalWrite(CSpin,HIGH);
}


void setup() {
  pinMode(CSpin, OUTPUT);
  pinMode(CLKpin, OUTPUT);
  pinMode(DATpin, OUTPUT);
  //pinMode(RSTpin, OUTPUT);
  digitalWrite(CSpin, HIGH);
  digitalWrite(CLKpin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  WT588D(Num);
  Num +=1;
  delay(1000);

  if(Num>100) Num=0;
}
