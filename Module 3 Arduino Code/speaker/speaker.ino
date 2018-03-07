//#include "Acc.H"
#include <Wire.h>
#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
int led = 4;
const byte address[6] = "00003";
void setup() {
  Serial.begin(9600);
  digitalWrite(led, LOW); 
  pinMode(led, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) 
  {
    char text[32] = "";
    radio.read(&text, sizeof(text));
   digitalWrite(led, HIGH);
   delay(100);
   digitalWrite(led, LOW);
    Serial.println(text);
  }
}
