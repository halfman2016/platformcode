//杰纳交通控制
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h> 
#include <MsTimer2.h>
#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
Servo msetc;  // create servo object to control a servo 
Servo msin;
Servo msout;// twelve servo objects can be created on most boards
LiquidCrystal_I2C lcd(0x27,16,2);

#define RED 5000
#define GREEN 5000
#define DZETC  5
#define DZIN   6
#define DZOUT  9
#define DZTIME 3000
#define FAN1 A1
#define FAN2 A2
#define FAN3 A3
#define IRETC 12
#define IRIN  10
#define IROUT 11
#define IRHLD 3 //中断 1
#define HLDRED 8
#define HLDGREEN 7
SoftwareSerial che(4,2);  // RX, TX
void up(Servo ser);
void down(Servo ser);
void onTimer();
void redlight();

int lighgtcolor=0;
int pos=0;

//IRrecv irrecv(11);

decode_results results;
unsigned char ishld;
int in=0,out=0,etc=0;
void setup() {
  lcd.begin();
  // put your setup code here, to run once:
pinMode(HLDRED,OUTPUT);
pinMode(HLDGREEN,OUTPUT);  
pinMode(IRETC,INPUT_PULLUP);
pinMode(IRIN,INPUT_PULLUP);
pinMode(IROUT,INPUT_PULLUP);
pinMode(IRHLD,INPUT_PULLUP);
msetc.attach(DZETC); 
msin.attach(DZIN);
msout.attach(DZOUT);
Serial.begin(9600);
che.begin(9600);
MsTimer2::set(5000, onTimer); //
MsTimer2::start(); //
//attachInterrupt(digitalPinToInterrupt(3), redlight, HIGH); //

//irrecv.enableIRIn(); 

}

void loop() {
  // put your main code here, to run repeatedly:

//ir
/* if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  } */

 if(digitalRead(IRHLD)==LOW)
 {
  redlight();
  }
  


 if(digitalRead(IRETC)==LOW)
 {
  Serial.println("etc ir");
  up(msetc);
  delay(DZTIME);
  down(msetc);
  }
  
        
  if(digitalRead(IRIN)==LOW){
    //IN
  Serial.println("in ir");
  up(msin);
  delay(DZTIME);
  down(msin);
  }

if(digitalRead(IROUT)==LOW){
Serial.println("out ir");
up(msout);
delay(DZTIME);
down(msout);
  }
   
}

 

void up(Servo ser){
  ser.write(0);
  }

void down(Servo ser){
   ser.write(90);
  }
  
void onTimer()
{
    Serial.println("on time");
  if(lighgtcolor==0)
{
  digitalWrite(HLDRED,HIGH);
  digitalWrite(HLDGREEN,LOW);
  che.print("0RED"); //编码0 红绿time 1 位置

  lighgtcolor=1;
  }else{
  digitalWrite(HLDGREEN,HIGH);
  digitalWrite(HLDRED,LOW);
  che.print("0GRE");
  lighgtcolor=0;
 }
}
void redlight(){
  che.print("1HLD");
  Serial.println("redlight");
 }
