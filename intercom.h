/* intercom.h */
/* brollyflock
   22 June 2011
   common file for interprocessor communication between the LED controller and
   the fire controller
*/
#include <ctype.h>

#ifndef intercom_h
#define intercom_h


#define BUTTONONE (1+64)
#define BUTTONTWO (2+64)
#define BUTTONTHREE (3+64)

void setup_serial();
uint8_t listen_from_firectl(char result[]);
uint8_t hexToByte(char hi, char lo);
#endif

