#include <Arduino.h>
#include <IRremote.h>
#include <SoftwareSerial.h>
#define TX 4
#define RX 2

#define IR 7                //遥控

#define KEY12 16753245   //CH-
#define KEY13 16736925  //ch
#define KEY14 16769565  //CH+
SoftwareSerial my(RX, TX);
unsigned char uart_Send_Buff1[7] ={0x55,0x55,0x05,0x06,0x00,0x01,0x00};
unsigned char uart_Send_Buff2[7] ={0x55,0x55,0x05,0x06,0x01,0x01,0x00};
unsigned char uart_Send_Buff3[7] ={0x55,0x55,0x05,0x06,0x02,0x01,0x00};

IRrecv ir(IR);
decode_results results;
String result="";
long keyval;

void setup(){
  // put your setup code here, to run once:
my.begin(9600);
ir.enableIRIn();


}

void loop() {
  // put your main code here, to run repeatedly:
  if (ir.decode(&results)) {
    
keyval=results.value;
    ir.resume(); // Receive the next value
  }

  if(keyval==KEY12){
  //kaideng
  Serial.println("KEY12");
  my.write(uart_Send_Buff1,7);
  keyval=0;

  }
 if(keyval==KEY13){
  //kaideng
  Serial.println("KEY12");
  my.write(uart_Send_Buff2,7);
  keyval=0;

  }
 if(keyval==KEY14){
  //kaideng
  Serial.println("KEY12");
  my.write(uart_Send_Buff3,7);
  keyval=0;

  }

}