#include <Arduino.h>
#include <SoftwareSerial.h> 
#include <BH1750.h>
#include <Wire.h>
#include <IRremote.h>

BH1750 lightMeter;
#define TFT_RX 2//RX D2
#define TFT_TX 4//TX of Serial TFT to D4
#define NONGYEADDR 0x10
#define TRAFFICADDR 0x11



//教室窗帘 CLOPEN CLOSE 不能同时为高；
#define CLOPEN 10
#define CLCLOSE 11
#define JSMOPEN 6
#define JSMCLOSE 9
//路灯
#define LUDENG 5
#define IR 3                //遥控
#define KEY0 16738455       //开灯
#define KEY1 16724175         //关灯
#define KEY2 16718055         //开门
#define KEY3 16743045         //关门
#define KEY4 16716015         //开窗帘
#define KEY5 16726215         //关窗帘
#define KEY6 16734885         //开顶棚
#define KEY7 16728765         //关顶棚
#define KEY8 16730805         //开风扇
#define KEY9 16732845         //关风扇
#define KEY10 16769055         //关水泵  -
#define KEY11  16754775        //开水泵 +
#define KEY12 16753245   //CH-
#define KEY13 16736925  //ch
#define KEY14 16769565  //CH+



//光强
#define LBORDER 400 //临界值
//语音识别
SoftwareSerial SBS(2, 4); // RX, TX
//语音合成
//SoftwareSerial HC(13,12); //RX,TX
IRrecv ir(IR);
decode_results results;

String result="";
uint16_t curlight=0;
unsigned char qs[]={0xFD,0x00,0x07,0x01,0x01,0xC7,0xEB,0xCB,0xB5,0xA8};
unsigned char kl[]={0xFD,0x00,0x07,0x01,0x01,0xBF,0xDA,0xC1,0xEE,0xB0};
byte x=0;

long keyval;
//


void kd(){
  digitalWrite(LUDENG,HIGH);
  }
void gd(){      
  digitalWrite(LUDENG,LOW);
  }

 void km(){
   
     digitalWrite(JSMCLOSE,LOW);
     delay(100);
     digitalWrite(JSMOPEN,HIGH);
     delay(3000);
      digitalWrite(JSMOPEN,LOW);
  }
  void gm(){
    digitalWrite(JSMOPEN,LOW);
  delay(100);
  digitalWrite(JSMCLOSE,HIGH);
  delay(3000);
    digitalWrite(JSMCLOSE,LOW);
    }

    void kc(){
        digitalWrite(CLCLOSE,LOW);
        delay(10);
        digitalWrite(CLOPEN,HIGH);
        delay(9000);
        digitalWrite(CLOPEN,LOW);    
      }

     void gc(){
      
    digitalWrite(CLOPEN,LOW);
    delay(100);
    digitalWrite(CLCLOSE,HIGH);
    delay(9000);
    digitalWrite(CLCLOSE,LOW);
      }
     void kdp(){
       Serial.println(result);

     x=3;
  Wire.beginTransmission(NONGYEADDR); // transmit to device #4
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();  
      }

      void gdp(){
        Serial.println(result);
       x=4;
  Wire.beginTransmission(NONGYEADDR); // transmit to device #4
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();  
  
        }

      void kf(){
       Serial.println(result);
  x=1;
  Wire.beginTransmission(NONGYEADDR); // transmit to device #4
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();  
        
        }

       void gf(){

        Serial.println(result);
  x=2;
  Wire.beginTransmission(NONGYEADDR); // transmit to device #4
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();  
            
  }
  void kpump(){
 Serial.println(result);
  x=5;
  Wire.beginTransmission(NONGYEADDR); // transmit to device #4
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();  
  }
  void gpump(){
  Serial.println(result);
  x=6;
  Wire.beginTransmission(NONGYEADDR); // transmit to device #4
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();  
  }

       
void setup() {
  // put your setup code here, to run ona'a'a'a'a'a'a'a'a'a'a'a'a'a'a'a'a'a'ace:
  pinMode(CLOPEN,OUTPUT);
  pinMode(CLCLOSE,OUTPUT);
  pinMode(LUDENG,OUTPUT);
  pinMode(JSMOPEN,OUTPUT);
  pinMode(JSMCLOSE,OUTPUT);
  digitalWrite(CLCLOSE,LOW);
  digitalWrite(LUDENG,LOW);
  digitalWrite(CLOPEN,LOW);
  digitalWrite(JSMCLOSE,LOW);
  digitalWrite(JSMOPEN,LOW);
  Wire.begin();  //master 
  ir.enableIRIn();
//HC.begin(9600);
SBS.begin(9600);
Serial.begin(9600);
Serial.println("Goodnight moon!");
lightMeter.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
   if(curlight ==lightMeter.readLightLevel())
    {
      }
    else
    {
    curlight = lightMeter.readLightLevel();
    Serial.println(curlight);
if (curlight<LBORDER)
  {
     digitalWrite(LUDENG,HIGH);
  }
  else
  {
     digitalWrite(LUDENG,LOW);

    }
    }

if (ir.decode(&results)) {
    keyval=results.value;
    ir.resume(); // Receive the next value
  }

 if(keyval==KEY0){
  //kaideng
  Serial.println("KEY0 kaideng");
  kd();
  keyval=0;
  }
  
 if(keyval==KEY1){
  //kaideng
  Serial.println("KEY1 guandeng");
  gd();
    keyval=0;

  }
   if(keyval==KEY2){
  //kaideng
  Serial.println("KEY2 kaimeng");
  km();
    keyval=0;

  }
   if(keyval==KEY3){
  //kaideng
  Serial.println("KEY3 guanmeng");
  gm();
    keyval=0;

  }
   if(keyval==KEY4){
  //kaideng
  Serial.println("KEY4 kaichuang");
  kc();
    keyval=0;

  }
   if(keyval==KEY5){
  //kaideng
  Serial.println("KEY5 guanchuang");
  gc();
    keyval=0;

  }
 if(keyval==KEY6){
  //kaideng
  Serial.println("KEY6 kaidingpeng");
  kdp();
    keyval=0;

  }
if(keyval==KEY7){
  //kaideng
  Serial.println("KEY7 guan dingpeng");
  gdp();
    keyval=0;

  }
if(keyval==KEY8){
  //kaideng
  Serial.println("KEY8 kai fan");
  kf();
    keyval=0;

   }
if(keyval==KEY9){
  //kaideng
  Serial.println("KEY9 guan fan");
  gf();
    keyval=0;

  }
if(keyval==KEY10){
  //kaideng
  Serial.println("KEY9 guan pump");
  gpump();
    keyval=0;

  }
if(keyval==KEY11){
  Serial.println("KEY9 kai pump");
  kpump();
    keyval=0;
}
if (SBS.available()) {
  result=SBS.readString();
  Serial.println(result);
if(result=="ok\r\n"){
    //HC.write(qs,10);
    }
if(result=="saykeyword"){
    //HC.write(kl,10);
    }

if(result=="ludengopen")
  {
    kd();
  }

if(result=="ludengclose")
  {
      gd();

  }

  if(result=="clopen")
  {
        kc();

  }


  
  if(result=="clclose")
  {
    gc();
  }
    
  if(result=="dkfan")
  {
    // slave 指令

    kf();
  }
  
    
  if(result=="gbfan")
  {
   //slave 指令
   gf();
  }
    
  if(result=="dkdp")
  {//slave 指令
       Serial.println(result);

     kdp();
  
  }
    
  if(result=="gbdp")
  {
    //slave 指令
    Serial.println(result);

      gdp();

  }
  
  if(result=="dkjsm")
  {
     Serial.println(result);
    km();

  }
    
  if(result=="gbjsm")
  {
  Serial.println(result);

gm();
   
  }
    
         
if(result=="dkpump")

  {
      Serial.println(result);

    kpump();
  }
  if(result=="gbpump")
     {
        Serial.println(result);
        gpump();
    }

    result="";
}
}