#include <Arduino.h>

#include <SoftwareSerial.h>   //Software Serial Port
#include <OS_SerialTFT.h>
#include <BH1750.h>
#include <AM2320.h>
#define TFT_RX 4//RX of Serial TFT module connect to D4 of Arduino / OPEN-SMART UNO
#define TFT_TX 2//TX of Serial TFT to D2


//pwm 3, 5, 6, 9, 10, 11



AM2320 th;

BH1750 lightMeter;
SerialTFT myTFT(TFT_RX, TFT_TX);

int l,t,h;
int s=0;
void setup() {
  // put your setup code here, to run once:
  myTFT.begin(9600);
  myTFT.reset();
  myTFT.setBacklight(150);//0~255
  myTFT.setTextSize(4);
  myTFT.setRotation(1);
 lightMeter.begin();
  pinMode(3,OUTPUT);


}

void loop() {

h=th.getHumidity();
t=th.getTemperature();

if(s==0){
myTFT.fillScreen(BLACK);
myTFT.setCursor(10,100);
myTFT.setTextColor(RED);
myTFT.print("Temper:");
myTFT.print(t);
delay(3000);
s=1;
}

if(s==1){

myTFT.fillScreen(BLACK);
myTFT.setTextColor(WHITE);

myTFT.setCursor(10,100);
myTFT.print("Humidity:");
myTFT.print(h);
myTFT.print(" %");
delay(3000);

s=2;

}

if(s==2){

    l=lightMeter.readLightLevel();

myTFT.fillScreen(BLACK);
myTFT.setCursor(10,100);
myTFT.setTextColor(GREEN);

myTFT.print("Light:");
myTFT.print(l);
myTFT.print(" lux");
delay(3000);

s=0;
}
    
   
}

