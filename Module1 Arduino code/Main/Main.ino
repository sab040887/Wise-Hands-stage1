#include "Acc.H"
//#include "Value.H"
#include <Wire.h>
#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


int Count;
RF24 radio(9, 10); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

Acc acc;
//Value value;

void setup() {
Serial.begin(9600);
//Serial.print("Initializing...");
Wire.begin();
radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
acc.setupMPU();
}

void loop ()
{
  
delay(5);
  radio.startListening();
  if ( radio.available())
  {
    while (radio.available()) 
    {
      int Count = 0;
      radio.read(&Count, sizeof(Count));
       Serial.print("count:   "   );
     Serial.println(Count);
     delay(200);
     //Acc :: C = Count;
     
    }
    
  }
  acc.Run();
}

