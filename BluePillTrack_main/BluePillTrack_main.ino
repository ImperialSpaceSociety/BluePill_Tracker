
#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_Ublox_GPS
SFE_UBLOX_GPS myGPS;
long lastTime = 0; //Simple local timer. Limits amount of I2C traffic to Ublox module.

#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;

void setup()
{
  Serial.begin(115200);
  while (!Serial); //Wait for user to open terminal
  
  //                                    UART for GPS
  ////////////////////////////////////////////////////////////////////////////////////////////// 

  //Assume that the U-Blox GPS is running at 9600 baud (the default) or at 38400 baud.
  //Loop until we're in sync and then ensure it's at 38400 baud.
  do {
    Serial.println("GPS: trying 38400 baud");
    Serial1.begin(38400);
    if (myGPS.begin(Serial1) == true) break;

    delay(100);
    Serial.println("GPS: trying 9600 baud");
    Serial1.begin(9600);
    if (myGPS.begin(Serial1) == true) {
        Serial.println("GPS: connected at 9600 baud, switching to 38400");
        myGPS.setSerialRate(38400);
        delay(100);
    } else {
        delay(2000); //Wait a bit before trying again to limit the Serial output
    }
  } while(1);
  Serial.println("GPS serial connected");

  myGPS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR

  ////////////////////////////////////////////////////////////////////////////////////////////// 

  //                                      I2C ACCELEROMETER
  ////////////////////////////////////////////////////////////////////////////////////////////// 
  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 5 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_5HZ);
  // setting SRD to 99 for a 10 Hz (1000/(1+99)) update rate. Must be >= 2dlpf_bandwith
  IMU.setSrd(99);
  ////////////////////////////////////////////////////////////////////////////////////////////// 
}

void loop()
{
  //Query module only every second. Doing it more often will just cause I2C traffic.
  //The module only responds when a new position is available
  if (millis() - lastTime > 1000)
  {
    lastTime = millis(); //Update the timer
    
    long latitude = myGPS.getLatitude();
    Serial.print(F("Lat: "));
    Serial.print(latitude);

    long longitude = myGPS.getLongitude();
    Serial.print(F(" Long: "));
    Serial.print(longitude);
    Serial.print(F(" (degrees * 10^-7)"));

    long altitude = myGPS.getAltitude();
    Serial.print(F(" Alt: "));
    Serial.print(altitude);
    Serial.print(F(" (mm)"));

    byte SIV = myGPS.getSIV();
    Serial.print(F(" SIV: "));
    Serial.print(SIV);

    Serial.println();
    IMU.readSensor();
    // display the data
    Serial.print(IMU.getAccelX_mss(),3);
    Serial.print("\t");
    Serial.print(IMU.getAccelY_mss(),3);
    Serial.print("\t");
    Serial.print(IMU.getAccelZ_mss(),3);
    Serial.print("\t");
    Serial.print(IMU.getGyroX_rads(),3);
    Serial.print("\t");
    Serial.print(IMU.getGyroY_rads(),3);
    Serial.print("\t");
    Serial.print(IMU.getGyroZ_rads(),3);
    Serial.print("\t");
    Serial.print(IMU.getMagX_uT(),3);
    Serial.print("\t");
    Serial.print(IMU.getMagY_uT(),3);
    Serial.print("\t");
    Serial.print(IMU.getMagZ_uT(),3);
    Serial.print("\t");
    Serial.println(IMU.getTemperature_C(),3);

  }
}

