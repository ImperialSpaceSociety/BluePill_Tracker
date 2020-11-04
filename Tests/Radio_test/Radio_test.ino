/*  NTX2 Radio Test Part 2
 
    Transmits data via RTTY with a checksum.
 
    Created 2012 by M0UPU as part of a UKHAS Guide on linking NTX2 Modules to Arduino.
    RTTY code from Rob Harrison Icarus Project. 
    http://ukhas.org.uk
*/ 
 
#define RADIOPIN PB15
 
#include <string.h>
#include "rtty.h"
 

RTTY rtty(RADIOPIN, 50, 1.5, CHECKSUM_CRC16);
 
void setup() {                
  pinMode(RADIOPIN,OUTPUT);
}
 
void loop() {
  rtty.transmit("test-transmission!!!$$$\n");
  delay(2000);
}
