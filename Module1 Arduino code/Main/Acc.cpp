#include "Acc.H"
#include <Wire.h>
#include "Arduino.h"


 Acc :: Acc ()
{

}

void Acc ::Run()
{
recordAccelRegisters();

//printData();
accel = maximum(gForceX, gForceY, gForceZ);
recordGyroRegisters();
gyro = maximum(rotX, rotY, rotZ);
Serial.println("Maximum Value");
Serial.println(gyro);
if (gyro > gyro_thresh) // GYro threshold also needs to be included.
{
now = millis();
//Serial.println("now");
//Serial.println(now);
if (lastupd == 0)
{

lastupd = now;
count = count + 1;
Serial.print("Count");
Serial.print("\t");
Serial.println(count);
}
else {
tim_diff = now - lastupd;
Serial.println("tim_diff");
Serial.println(tim_diff);

if (tim_diff <= interval)
{
  
count = count + 1;
Serial.print("Count");
Serial.print("\t");
Serial.println(count);
lastupd = now;



if (count == 15)
{
Serial.println(" Audio Device Triggered");
//Serial.println(1);
digitalWrite(13, HIGH); // Toggle the LED on Pin 13
delay(500);
digitalWrite(13, LOW); //Should play for at least 20 secs and continue as long as the count increases
count = 0;
lastupd = 0;
}

}
else if (tim_diff >= interval) {
count = 0;
lastupd = 0;
}

}
}
delay(100);
}


void Acc ::recordGyroRegisters()
{
  Wire.beginTransmission(0x68); //I2C address of the MPU
Wire.write(0x43); //Starting register for Gyro Readings
Wire.endTransmission();
Wire.requestFrom(0b1101000, 6); //Request Gyro Registers (43 - 48)
while (Wire.available() < 6);
gyroX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX gyroY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY

gyroZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
rotX = gyroX / 131.0;
rotY = gyroY / 131.0;
rotZ = gyroZ / 131.0;
}

void Acc ::recordAccelRegisters()
{
  Wire.beginTransmission(0x68); //I2C address of the MPU
Wire.write(0x3B); //Starting register for Accel Readings
Wire.endTransmission();
Wire.requestFrom(0b1101000, 6); //Request Accel Registers (3B - 40)
while (Wire.available() < 6);
accelX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
accelY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
accelZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
gForceX = accelX / 16384.0;
gForceY = accelY / 16384.0;
gForceZ = accelZ / 16384.0;
  
}

float Acc ::  maximum(float x, float y, float z)
{
  float maxi = x;
if (y > maxi)
{
maxi = y;
}
if (z > maxi)
{
maxi = z;
}
return maxi;
  
}


void Acc::setupMPU()
{
    Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
Serial.println("Gyro (deg)");
Serial.print(" X=");
Serial.print(rotX);
//Serial.print("\t");
Serial.print(" Y=");
Serial.print(rotY);

//Serial.print("\t");
Serial.print(" Z=");
Serial.println(rotZ);
//Serial.print("\t");
Serial.print(" Accel (g)");
Serial.print(" X=");
Serial.print(gForceX);
//Serial.print("\t");
Serial.print(" Y=");
Serial.print(gForceY);
// Serial.print("\t"); Serial.print(" Z="); Serial.println(gForceZ); //Serial.print("\t");
}  


