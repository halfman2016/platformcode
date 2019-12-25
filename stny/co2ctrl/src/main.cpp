#include <Arduino.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h> 
#include <Adafruit_CCS811.h>
#include <IRremote.h>



SoftwareSerial g39(10,11); // RX, TX


Adafruit_CCS811 ccs;


LiquidCrystal_I2C lcd(0x27); // 0x27 is the I2C bus address for an unmodified backpack 

unsigned char Re_buf[15],counter=0;
unsigned char sign=0;
typedef struct
{
    uint32_t P;
    uint16_t Temp;
    uint16_t Hum;
    uint16_t Alt;
} bme;

uint32_t p;//气压
uint16_t co2;
uint16_t tvoc;

//控制继电器

#define FAN 7
#define PUMP 8
#define KDP 12
#define GDP 13
#define DPDELAY 9000 //顶棚开启关闭运行时间长度


#define IR 9               //遥控
#define KEY0 16738455       //开灯
#define KEY1 16724175         //
#define KEY2 16718055         //开门
#define KEY3 16743045         //关门
#define KEY4 16716015         //开窗帘
#define KEY5 16726215         //关窗帘
#define KEY6 16734885         //开顶棚
#define KEY7 16728765         //关顶棚
#define KEY8 16730805         //开风扇
#define KEY9 16732845         //关风扇

  
uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};

IRrecv ir(IR);
decode_results results;

long keyval;
void kf();
void gf();
void gs();
void ks();
void kdp();
void gdp();
void myserialEvent();

void setup(){

lcd.createChar(0, bell);


  Serial.begin(9600); 
  g39.begin(9600); 
  delay(1);    
  //g39 cmd
  g39.write(0XA5); 
  Serial.write(0XA5);
  g39.write(0X02);    //初始化,连续输出模式
  g39.write(0XA7);    //初始化,连续输出模式

 lcd.begin(16,2); // for 16 x 2 LCD module  
 lcd.setBacklight(HIGH); 
 lcd.print("hello");


//811初始化

ccs.begin();

//calibrate temperature sensor
while(!ccs.available());
float temp = ccs.calculateTemperature();
ccs.setTempOffset(temp - 25.0);
  
  //继电器控制
  pinMode(FAN,OUTPUT);
  pinMode(PUMP,OUTPUT);
  pinMode(KDP,OUTPUT);
  pinMode(GDP,OUTPUT);

  //红外初始化

  ir.enableIRIn();


  }

 void loop(){
   
if (ir.decode(&results)) {
    
keyval=results.value;
Serial.println(keyval);
    ir.resume(); // Receive the next value
  }

  if(keyval==KEY1){
  //kaideng
  Serial.println("KEY1 fanopen");
  kf();
  keyval=0;
  }
  if(keyval==KEY2){
  //kaideng
  Serial.println("KEY2 fanclose");
  gf();
  keyval=0;
  }

  if(keyval==KEY3){
  //kaideng
  Serial.println("KEY3 kaishuiben");
  ks();
  keyval=0;
  }
  if(keyval==KEY4){
  //kaideng
  Serial.println("KEY4 guanshuiben");
  gs();
  keyval=0;
  }
  if(keyval==KEY5){
  //kaideng
  Serial.println("KEY5 kaidingpeng");
  kdp();
  keyval=0;
  }
  if(keyval==KEY6){
  //kaideng
  Serial.println("KEY6 guandingpeng");
  gdp();
  keyval=0;
  }

unsigned char i=0,sum=0;
   uint16_t data_16[2]={0};
    bme Bme;
    if(g39.available()>0){
      myserialEvent();
      }
  if(sign)
  {   
  
     for(i=0;i<14;i++)
      sum+=Re_buf[i]; 
     if(sum==Re_buf[i] )        //检查帧头，帧尾
     {  	 
       Bme.Temp=(Re_buf[4]<<8)|Re_buf[5];
        data_16[0]=(Re_buf[6]<<8)|Re_buf[7];
        data_16[1]=(Re_buf[8]<<8)|Re_buf[9];
       p=Bme.P=(((uint32_t)data_16[0])<<16)|data_16[1];
       Bme.Hum=(Re_buf[10]<<8)|Re_buf[11];
       Bme.Alt=(Re_buf[12]<<8)|Re_buf[13];      
       Serial.print("Temp: ");
       Serial.print( (float)Bme.Temp/100);
       Serial.print(" DegC  PRESS : ");
       Serial.print( ((float)Bme.P)/100);
       Serial.print(" Pa  HUM : ");
       Serial.print( (float)Bme.Hum/100);
       Serial.print(" % ALT:");
       Serial.print( Bme.Alt);
       Serial.println("m");
 
   
    sign=0;        
   }

  } 

  // 
if(ccs.available()){
float temp = ccs.calculateTemperature();
if(!ccs.readData()){
Serial.print("CO2: ");
co2=ccs.geteCO2();
Serial.print(co2);
Serial.print("ppm, TVOC: ");
tvoc=ccs.getTVOC();
Serial.print(tvoc);
Serial.print("ppb Temp:");
Serial.println(temp);
}
else{
Serial.println("ERROR!");
while(1);
}

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Press:");
lcd.print(p);
lcd.print("Pa");
lcd.setCursor(0,1);
lcd.print("CO2:");
lcd.print(co2);
lcd.print(" ppm");
   delay(50);


}
}



void myserialEvent() {

 
      while (g39.available()) {   
      Re_buf[counter]=(unsigned char)g39.read();
      if(counter==0&&Re_buf[0]!=0x5A) return;      // 检查帧头         
      counter++;       
      if(counter==15)                //接收到数据
      {    
         counter=0;                 //重新赋值，准备下一帧数据的接收 
         sign=1;
      }      
      }

}

void kf(){
digitalWrite(FAN,HIGH);

}
void gf(){
  digitalWrite(FAN,LOW);


}
void ks(){
digitalWrite(PUMP,HIGH);

}

void gs(){
digitalWrite(PUMP,LOW);
}

void kdp(){
//顶棚设定标志位 开顶棚
digitalWrite(KDP,HIGH);  //开顶棚方向停机
delay(500);
digitalWrite(KDP,LOW);

}
void gdp(){
digitalWrite(GDP,HIGH);  //开顶棚方向停机
delay(500);
digitalWrite(GDP,LOW); //开关顶棚方向开机


}

void fana0(int dl){
  for(int i=0;i<200;i++){
   analogWrite(A0,i-5);
      analogWrite(A1,i+5);
   analogWrite(A2,i);

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
   for(int i=0;i<190;i++){
   analogWrite(A2,i);
   delay(dl);
   }
}
