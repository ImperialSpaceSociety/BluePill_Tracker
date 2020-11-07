
/*

  Listfiles

  This example shows how print out the files in a

  directory on a SD card.Pin numbers reflect the default

  SPI pins for Uno and Nano models

  The circuit:

   SD card attached to SPI bus as follows:

 ** SDO - pin 11

 ** SDI - pin 12

 ** CLK - pin 13

 ** CS - depends on your SD card shield or module.

        Pin 10 used here for consistency with other Arduino examples

    (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010

  by David A. Mellis

  modified 9 Apr 2012

  by Tom Igoe

  modified 2 Feb 2014

  by Scott Fitzgerald

  modified 24 July 2020

  by Tom Igoe

  

  This example code is in the public domain.

*/
#include <SD.h>
#include <SPI.h>

const int chipSelect = PB12;

File root;

void setup() {

 // Open serial communications and wait for port to open:
  SPI.setModule(2);
  Serial.begin(115200);

  // wait for Serial Monitor to connect. Needed for native USB port boards only:

  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {

    Serial.println("initialization failed. Things to check:");

    Serial.println("1. is a card inserted?");

    Serial.println("2. is your wiring correct?");

    Serial.println("3. did you change the chipSelect pin to match your shield or module?");

    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");

    while (true);

  }

  Serial.println("initialization done.");


  File root2= SD.open("/");

  deleteDirectory(root2);

  Serial.println("done!");
}

void loop() {

  // nothing happens after setup finishes.
}

void deleteDirectory(File dir) {

  while (true) {

    File entry =  dir.openNextFile();

    if (! entry) {
      break;
    }

    Serial.print("Removing: ");
    Serial.println(entry.name());
    if (SD.exists(entry.name())){
      Serial.println("exists!!");
    }
    String entryname = entry.name();
    //entryname = "/SYSTEM~1/" + entryname;
    SD.rmdir(entryname);
    entry.close();

  }
}