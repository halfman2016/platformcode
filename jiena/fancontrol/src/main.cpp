#include <Arduino.h>

//pwm 3, 5, 6, 9, 10, 11
//
#define FAN1 3
#define FAN2 5
#define FAN3 6
#define FAN4 9
#define FAN5 10
#define FAN6 11
//#define FAN7 14  //A1
//#define FAN8 15  //A2
//#define FAN9 16  //A3
//#define FAN10 17 //A4

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println(A0);
Serial.println(A1);
Serial.println(A2);
Serial.println(A3);
Serial.println(A5);
Serial.println(A6);
Serial.println(A7);


}

void loop() {
  // put your main code here, to run repeatedly:
fand(FAN1,20);
fand(FAN2,33);
fand(FAN3,30);
fand(FAN4,30);
fand(FAN5,40);
fand(FAN6,35);
fana1(55);
fana2(35);
fana3(40);
fana4(25);
fana5(35);
fana0(45);


}
void fana0(int dl){
  for(int i=0;i<180;i++){
   analogWrite(A0,i);
   delay(dl);
   }
}
void fana1(int dl){
  //120 勉强动
   for(int i=0;i<180;i++){
   analogWrite(A1,i);
   delay(dl);
   }
}
void fana2(int dl){
  //120 勉强动
   for(int i=0;i<170;i++){
   analogWrite(A2,i);
   delay(dl);
   }
}
void fana3(int dl){
  //120 勉强动
   for(int i=0;i<150;i++){
   analogWrite(A3,i);
   delay(dl);
   }
}
void fana4(int dl){
  //120 勉强动
   for(int i=0;i<200;i++){
   analogWrite(A4,i);
   delay(dl);
   }
}
void fana5(int dl){
  //120 勉强动
   for(int i=0;i<140;i++){
   analogWrite(A5,i);
   delay(dl);
   }
}

void fand(int a,int dl){
  //120 勉强动
   for(int i=0;i<200;i++){
   analogWrite(a,i);
   delay(dl);
   }
}