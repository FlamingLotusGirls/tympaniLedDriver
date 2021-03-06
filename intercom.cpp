/* intercom.cpp */
/* brollyflock
   22 Jun 2011
   
*/ 

#include <Arduino.h>
#include "intercom.h"
#include <ctype.h>

// import processing.serial.*;

#define BAUDRATE 9600
#define BOARDADDRESS 20

void setup_serial(void) {
  Serial.begin(BAUDRATE);
}

uint8_t listen_from_firectl(char result[5]) {
  uint8_t addrCount = 0;
  uint8_t bufferCount = 0;
  uint8_t listeningState = 0;
  char incomingByte;
  char addressBytes[2];
  char buffer[10];
  uint8_t resultLength = 0;
  
  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == '!'){
      addrCount = 0;
      listeningState = 0;
    }
    else if (listeningState == 0){
      addressBytes[addrCount++] = incomingByte;
      if (addrCount == 2){
        if (hexToByte(addressBytes[0], addressBytes[1]) == BOARDADDRESS){
          listeningState = 1; //for us, start saving command data
        }
        else{
          listeningState = 2; //not for us, ignore
        }
      }
    }    
    else if (listeningState == 1){
      if (incomingByte == '.'){
        listeningState = 2;
      }
      else {
        buffer[bufferCount++] = incomingByte;
      }
    }
  }
  uint8_t i = 0;
  while (i < bufferCount - 1){
    result[resultLength++] = hexToByte(buffer[i++], buffer[i++]);
  }
  return resultLength;
}
uint8_t hexToByte(char hi, char lo) {
  uint8_t b;
  hi = toupper(hi);
  if( isxdigit(hi) ) {
    if( hi > '9' ) hi -= 7;      // software offset for A-F
    hi -= 0x30;                  // subtract ASCII offset
    b = hi<<4;
    lo = toupper(lo);
    if( isxdigit(lo) ) {
      if( lo > '9' ) lo -= 7;  // software offset for A-F
      lo -= 0x30;              // subtract ASCII offset
      b = b + lo;
      return b;
    } // else error
  }  // else error
  return 0;
}


/*int listen_from_firectl(void) {
//   returns 0 for nothing of interest yet
//   returns nonzero for something useful

  int inByte = 0;

  if (Serial.available() > 0) {
    inByte = Serial.read();
    
    Serial.println(inByte);
    
    switch (inByte) {
       case BUTTONONE:
       case BUTTONTWO:
       case BUTTONTHREE:    // we got something we like
          return (inByte);
          break;
       default:        // we got something but we didn't like it
//          complain();
          return 0;
          break;
     }
  }

  // we got nuthin
  return 0;

}*/


