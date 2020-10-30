# Blue pill High Altitude Balloon Tracker

This repository contains the design files and software for the Blue pill based High Altitude Balloon tracker.

The main components of the system are:

* STM32F103 based Blue pill arduino board
* Ublox MAX-M8Q GPS on breakout board
* NTX2B-FA Radio module
* MPU-9250 9DOF Module 9 Axis Gyroscope Accelerometer Magnetic Field Sensor on breakout board
* SD card reader on breakout board
* potentially other sensors as well

## Programming
The microcontroller is programmed with an ST Link and the serial debug info is transmitted via the in built USB connection on the Blue pill
