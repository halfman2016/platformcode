#include <Arduino.h>

#include <Wire.h>

#define NONGYEADDR 0x10

#define FAN 9
#define DPOPEN  11
#define DPCLOSE 10



int x=0;
//1 dkfan 2 gbfan 3 dkdp 4 gbdp
void setup() {
  // put your setup code here, to run once:
Wire.begin(NONGYEADDR);
Wire.onReceive(receiveEvent);
Serial.begin(9600);
pinMode(FAN,OUTPUT);
pinMode(DPOPEN,OUTPUT);
pinMode(DPCLOSE,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void receiveEvent(int howMany){
  
  
  x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  if(x==1) {
    digitalWrite(FAN,HIGH);
    }
 if(x==2) {
    digitalWrite(FAN,LOW);
    }
     if(x==3) {
    digitalWrite(DPCLOSE,LOW);
    delay(100);
    digitalWrite(DPOPEN,HIGH);
    delay(10000); //10s
        digitalWrite(DPOPEN,LOW);

    }
     if(x==4) {
    digitalWrite(DPOPEN,LOW);
    delay(100);
    digitalWrite(DPCLOSE,HIGH);
    delay(10000);
    digitalWrite(DPCLOSE,LOW);

     }
  }