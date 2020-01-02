#include <Arduino.h>
#define FAN1 A5


void fan(int dl){
  //120 勉强动
   for(int i=0;i<180;i++){
   analogWrite(A5,i);
   delay(dl);
   }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
fan(50);
}