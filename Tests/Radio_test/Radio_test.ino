#define RADIOPIN PB15
 
#include <string.h>
#include "crc16.h"
#include "radiolib.h"
 
char datastring[80];

rtty Rtty(RADIOPIN,300);
 
void setup() {                
  pinMode(RADIOPIN,OUTPUT);
}
 
void loop() {
 
  sprintf(datastring,"RTTY TEST BEACON RTTY TEST BEACON"); // Puts the text in the datastring
  unsigned int CHECKSUM = gps_CRC16_checksum(datastring);  // Calculates the checksum for this datastring
  char checksum_str[6];
  sprintf(checksum_str, "*%04X\n", CHECKSUM);
  strcat(datastring,checksum_str);
 
  Rtty.rtty_txstring (datastring);
  delay(2000);
}
 
 