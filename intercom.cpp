/* intercom.cpp */
/* brollyflock
   22 Jun 2011
   
*/ 

#include "wProgram.h"
#include "intercom.h"
#include <ctype.h>

// import processing.serial.*;

#define BAUDRATE 9600


void setup_serial(void) {
  Serial.begin(BAUDRATE);
}

char *listen_from_firectl(char[] result) {
  uint8_t count = 0;
  uint8_t listeningState = 0;
  char incomingByte;
  char addressBytes[2];
  uint8_t resultLength = 0;
  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == '.'){
      count = 0;
      listeningState = 0;
    }
    else if (listeningState == 0){
      addressBytes[count++] = incomingByte;
      if (count == 2){
        if (toHex(addressBytes[0], addressBytes[1]) == BOARDADDRESS){
          listeningState = 1; //for us, start saving command data
          count = 0;
        }
        else{
          listeningState = 2; //not for us, ignore
        }
      }
    }    
    else if (listeningState == 1){
      if (incomingByte == '!'){
        listeningState = 2;
      }
      else {
        result[count++] = incomingByte;
        resultLength++;
      }
    }
  }
  return resultLength;
}
uint8_t toHex(char hi, char lo) {
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


void send_to_firectl(char thing_to_send) {
   Serial.print(thing_to_send, BYTE);
}


int listen_from_ledctl(void) {

}


void send_to_ledctl(int thing_to_send) {
   Serial.print(thing_to_send, BYTE);     
}

