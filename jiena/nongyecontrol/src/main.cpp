#include <Arduino.h>

#include <Wire.h>

#define NONGYEADDR 0x10 //农业地址

#define FAN 12
#define PUMP 13
#define DPOPEN  7
#define DPCLOSE 8



int x=0;
//1 dkfan 2 gbfan 3 dkdp 4 gbdp

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
    delay(500); //10s
    digitalWrite(DPOPEN,LOW);

    }
     if(x==4) {
    digitalWrite(DPOPEN,LOW);
    delay(10);
    digitalWrite(DPCLOSE,HIGH);
    delay(500);
    digitalWrite(DPCLOSE,LOW);

     }
     if (x==5)
     {
       //kai pump
       digitalWrite(PUMP,HIGH);
       delay(20);
       /* code */
     }
     if (x==6)
     {
       digitalWrite(PUMP,LOW);
       delay(20);
     }
     
     
  }
void setup() {
  // put your setup code here, to run once:
Wire.begin(NONGYEADDR);
Wire.onReceive(receiveEvent);
Serial.begin(9600);
pinMode(FAN,OUTPUT);
pinMode(DPOPEN,OUTPUT);
pinMode(DPCLOSE,OUTPUT);
pinMode (PUMP,OUTPUT);

//digitalWrite(PUMP,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}

