/* this is to load the Teensy 3.1's EEPROM with the user definable data
 *
 *  updated for Tracker v 2.02
 * 
 *  this can be optimized, but why bother?
 *
 */
#include <EEPROMex.h>

// define the variables
int8_t utc     = -4;             // UTC value -12 ... 0 ... 12
uint16_t dTime = 45;             // default delay time to next xmit in sec
String sCall   = "W2DEN";        // source callsign 6 max
int sSsid      = 5 ;             // source SSID
String dCall   = "APRS";         // destination call 6 max
int dSsid      = 0;              // dest. ssid
char symTable  = '/';            // primary / secondary \ ... needs the escape \ before a \. / is OK
char symbol    = '>';            // the symbol
String comment = "Teensy APRS Tracker Nokomis, Fl";
int8_t sb               = 1;     // use SB? 1 for tru 0 for false
uint16_t sbFastSpeed    = 60;    //mph speeds stored and compared as integers tostop oscilatting
uint16_t sbFastRate     = 180;   //seconds
uint16_t sbSlowSpeed    = 5;     // mph as integer
uint16_t sbSlowRate     = 1800;  // seconds
uint16_t sbMinTurnTime  = 15;    //sec
uint16_t sbMinTurnAngle = 30;    //degrees
uint16_t sbTurnSlope    = 240;   //
uint16_t axDelay        = 500;    // milliseconds
uint16_t axFlags        = 50;    // number of flags to send
uint16_t axVoxOn        = 0;     // mseconds vox tone sent to xmitter 0 for off
uint16_t axVoxSilent    = 0;     // mseconds VOX tone silent  0 for off
uint16_t pttPin         = 13;    // PTT Teensy Pin usually 13, 0 for off
int8_t   tftOnOff       = 1;     // TFT onn(1) or off (0)
uint16_t squelch        = 100;   // squelch threshold 


int ptr = 0 ; //EEPROM pointer

/////////////////////////////// do it
void setup() {
  // pad everything
  while (comment.length() < 35) { //pad to len = 35
    comment = comment  + " ";
  }
  while (sCall.length() < 6) { //pad to len = 6
    sCall = sCall  + " ";
  }
  while (dCall.length() < 6) { //pad to len = 6
    dCall = dCall  + " ";
  }
  Serial.begin(9600);
  delay (1500);
  ////////////////////////////// print input
  Serial.println("IN:");
  Serial.println(utc);
  Serial.println(dTime);
  Serial.print(sCall);
  Serial.print("-");
  Serial.print(sSsid);
  Serial.println("  source Call");
  Serial.print(dCall);
  Serial.print("-");
  Serial.print(dSsid);
  Serial.println("  dest.Call");
  Serial.println(symTable);
  Serial.println(symbol);
  Serial.println(comment);
  Serial.println(sb);
  Serial.println(sbFastSpeed);    //mph speeds stored and compared as integers tostop oscilatting
  Serial.println(sbFastRate);     //seconds
  Serial.println(sbSlowSpeed);    // mph as integer
  Serial.println(sbSlowRate);
  Serial.println(sbMinTurnTime);  //sec
  Serial.println(sbMinTurnAngle); //degrees
  Serial.println(sbTurnSlope );    //
  Serial.println(axDelay);        // milliseconds
  Serial.println(axFlags);          // number of flags to send
  Serial.println(axVoxOn);         // mseconds vox tone sent to xmitter 0 for off
  Serial.println(axVoxSilent);     // mseconds VOX tone silent  0 for off
  Serial.println(pttPin);
  Serial.println(tftOnOff);
  Serial.println(squelch);
  Serial.println();

  ////////////////////////////// now save to EEPROM
  EEPROM.update(ptr++, char('*')); // flag that there is data in the EEPROM
  EEPROM.update(ptr++, utc);
  EEPROM.updateInt(ptr++, dTime);    // two bytes here
  ptr++;
  for (int i = 0; i < sCall.length(); i++) {
    EEPROM.update(ptr++, char(sCall[i]));
  }
  EEPROM.update(ptr++, sSsid);      //SSID
  for (int i = 0; i < dCall.length(); i++) {
    EEPROM.update(ptr++, char(dCall[i]));
  }
  EEPROM.update(ptr++, dSsid);      //SSID
  EEPROM.update(ptr++, symTable); //symTable
  EEPROM.update(ptr++, symbol); //symbol
  for (int i = 0; i < 35; i++) {
    EEPROM.update(ptr++, char(comment[i]));
  }
  ptr = 55;
  EEPROM.update(ptr++, sb);
  EEPROM.updateInt(ptr++, sbFastSpeed);   //mph speeds stored and compared as integers tostop oscilatting
  ptr++;
  EEPROM.updateInt(ptr++, sbFastRate);    //seconds
  ptr++;
  EEPROM.updateInt(ptr++, sbSlowSpeed);   // mph as integer
  ptr++;
  EEPROM.updateInt(ptr++, sbSlowRate);
  ptr++;
  EEPROM.updateInt(ptr++, sbMinTurnTime); //sec
  ptr++;
  EEPROM.updateInt(ptr++, sbMinTurnAngle); //degrees
  ptr++;
  EEPROM.updateInt(ptr++, sbTurnSlope );   //
  ptr++;
  EEPROM.updateInt(ptr++, axDelay);
  ptr++;
  EEPROM.updateInt(ptr++, axFlags);
  ptr++;
  EEPROM.updateInt(ptr++, axVoxOn );
  ptr++;
  EEPROM.updateInt(ptr++, axVoxSilent);
  ptr++;
  EEPROM.updateInt(ptr++, pttPin);
  ptr++;
  EEPROM.update(ptr++, tftOnOff);  // note this is a single byte.
  EEPROM.updateInt(ptr++, squelch);
  ptr++;


  /////////////////////////////// read back from EEPROM
  ptr = 0;
  utc = 0;
  dTime = 0;
  sCall = "";
  sSsid = 0;
  dCall = "";
  dSsid = 0;
  comment = "";
  sb = 0;
  sbFastSpeed    = 0;    //mph speeds stored and compared as integers tostop oscilatting
  sbFastRate     = 0;    //seconds
  sbSlowSpeed    = 0;    // mph as integer
  sbSlowRate     = 0;
  sbMinTurnTime  = 0;    //sec
  sbMinTurnAngle = 0;    //degrees
  sbTurnSlope    = 0;    //
  axDelay        = 0;    // milliseconds
  axFlags        = 0;    // number of flags to send
  axVoxOn        = 0;    // mseconds vox tone sent to xmitter 0 for off
  axVoxSilent    = 0;    // mseconds VOX tone silent  0 for off
  pttPin         = 0;    // PTT Teensy Pin usually 13, 0 for off
  tftOnOff       = 0;
  squelch        = 0;

  char check = EEPROM.read(ptr++); // 0
  utc = EEPROM.read(ptr++);        // 1
  dTime = EEPROM.readInt(ptr++);   // 2,3
  ptr++;
  char inCall;
  for (int i = 1; i < 7; i++) {    // 4,5,6,7,8,9
    inCall = EEPROM.read(ptr++);
    sCall = sCall + inCall;
  }
  sSsid = EEPROM.read(ptr++);      // 10
  for (int i = 1; i < 7; i++) {    // 11,12,13,14,15,16
    inCall = EEPROM.read(ptr++);
    dCall = dCall + inCall;
  }
  dSsid = EEPROM.read(ptr++);      // 17
  symTable = EEPROM.read(ptr++);   // 18
  symbol = EEPROM.read(ptr++);     // 19
  for (int i = 1; i < 34; i++) {   // 20 ...
    inCall = EEPROM.read(ptr++);
    comment = comment + inCall;
  }
  ptr = 55; // just to be sure we are where we should be
  sb             = EEPROM.read(ptr++);
  sbFastSpeed    = EEPROM.readInt(ptr++);    //mph speeds stored and compared as integers tostop oscilatting
  ptr++;
  sbFastRate     = EEPROM.readInt(ptr++);     //seconds
  ptr++;
  sbSlowSpeed    = EEPROM.readInt(ptr++);  // mph as integer
  ptr++;
  sbSlowRate     = EEPROM.readInt(ptr++);
  ptr++;
  sbMinTurnTime  = EEPROM.readInt(ptr++);  //sec
  ptr++;
  sbMinTurnAngle = EEPROM.readInt(ptr++); //degrees
  ptr++;
  sbTurnSlope    = EEPROM.readInt(ptr++);
  ptr++;
  axDelay        = EEPROM.readInt(ptr++);
  ptr++;
  axFlags        = EEPROM.readInt(ptr++);
  ptr++;
  axVoxOn        = EEPROM.readInt(ptr++);
  ptr++;
  axVoxSilent    = EEPROM.readInt(ptr++);
  ptr++;
  pttPin         = EEPROM.readInt(ptr++);
  ptr++;
  tftOnOff       = EEPROM.read(ptr++); // tft on/off single byte
  squelch        = EEPROM.readInt(ptr++);
  ptr++;

  ////////////////////////////// output
  Serial.println();
  Serial.println("Out");
  Serial.println(check);
  Serial.println(utc);
  Serial.println(dTime);
  Serial.print(sCall);
  Serial.print("-");
  Serial.print(sSsid);
  Serial.println("  source Call");
  Serial.print(dCall);
  Serial.print("-");
  Serial.print(dSsid);
  Serial.println("  dest.Call");
  Serial.println(symTable);
  Serial.println(symbol);
  Serial.println(comment);
  if (sb) {
    Serial.println("sb: True");
  }
  else {
    Serial.println("sb: False");
  }
  Serial.println(sbFastSpeed);    //mph speeds stored and compared as integers tostop oscilatting
  Serial.println(sbFastRate);     //seconds
  Serial.println( sbSlowSpeed);    // mph as integer
  Serial.println( sbSlowRate);
  Serial.println(sbMinTurnTime);  //sec
  Serial.println( sbMinTurnAngle); //degrees
  Serial.println(sbTurnSlope );    //
  Serial.println(axDelay);        // milliseconds
  Serial.println(axFlags);          // number of flags to send
  Serial.println(axVoxOn);         // mseconds vox tone sent to xmitter 0 for off
  Serial.println(axVoxSilent);     // mseconds VOX tone silent  0 for off
  Serial.println(pttPin);
  if (tftOnOff) {
    Serial.println("TFT On");
  }
  else {
    Serial.println("TFT Off");
  }
  Serial.println(squelch);
/////////////////////////////////// now just a dump  
  if (check == '*') {
    Serial.println("Check eePROM dump:");
  }
  int r;
  for (int i = 0; i < 83; i++) {
    r = EEPROM.read(i);
    Serial.print(i);
    Serial.print(": ");
    Serial.print(r);
    Serial.print(" ");
    Serial.println(char(r));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
