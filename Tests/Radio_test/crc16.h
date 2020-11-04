#include "Arduino.h"

uint16_t my_crc_xmodem_update (uint16_t crc, uint8_t data) {
  int i;
  crc = crc ^ ((uint16_t)data << 8);
  for (i=0; i<8; i++) {
    if (crc & 0x8000) {
      crc = (crc << 1) ^ 0x1021;
    } else {
      crc <<= 1;
    }
  }
  return crc;
}

uint16_t gps_CRC16_checksum (char *string) {
  size_t i, len = strlen(string);
  uint16_t crc = 0xFFFF;
  uint8_t c;
 
  // Calculate checksum ignoring the first two $s
  for (i = 2; i < len; i++) {
    c = string[i];
    crc = my_crc_xmodem_update (crc, c);
  }
 
  return crc;
}