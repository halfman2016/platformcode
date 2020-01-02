#include <Arduino.h>
#include<Ultrasonic.h>
#include<LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>

SoftwareSerial HC(2, 4); // RX, TX

LiquidCrystal_I2C lcd(0x27,16,22); // LCD arduino library
Ultrasonic ultrasonic1(8,7); // (Trig PIN,Echo PIN)

unsigned char dyi[]={0xFD,0x00,0x0D,0x01,0x01,0xB5,0xDA,0xD2,0xBB,0xD5,0xBE,0xB5,0xBD,0xC1,0xCB,0x9F};
unsigned char der[]={0xFD,0x00,0x0D,0x01,0x01,0xB5,0xDA,0xB6,0xFE,0xD5,0xBE,0xB5,0xBD,0xC1,0xCB,0xBE};
void setup() {
lcd.begin();  // put your setup code here, to run once:
HC.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 if (ultrasonic1.Ranging(CM)<10)
 {
   lcd.clear();
   lcd.print("come");
  HC.write(dyi,16);
 }

 

}