#ifndef Acc_h
#define Acc_h

#include "Arduino.h"


class Acc
{
  public:
   Acc();
   
 void printData();
 void recordGyroRegisters();
 void recordAccelRegisters();
 void setupMPU();
 //void value();
 float  maximum(float x, float y, float z);
 void Run();
 int Count = 0;  
  int C = 0;
private:
int garbage;
long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;
long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float accel, gyro;
float acc_thresh = 1.40;
float gyro_thresh = 40;
float lastupd = 0;
int count = 0;
//int Count = 0;
float interval = 500;
float now = 0;
float tim_diff = 0;
const int MPU_addr=0x68;

};


#endif
