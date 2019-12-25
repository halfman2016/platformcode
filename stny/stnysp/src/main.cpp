#include <Arduino.h>
#include <SoftwareSerial.h>
#include <OS_SerialTFT.h> 
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include <dht.h>
//right board

//串口屏
//1602
//光照
//土壤湿度
//温度湿度
//485串口 读取风向2 ph1 风速3 4800

 


#define MOI A1
#define D A0
#define TX 7
#define RX 8

LiquidCrystal_I2C lcd(0x27,16,2);
SerialTFT myTFT(RX, TX);
dht DHT;
BH1750 lightMeter;  //I2C 接口
int m=0,l=0;
int t,h;

//SoftwareSerial port485(4, 2); // RX, TX

int i=0;


SoftwareSerial mySerial(13, 12); // RX, TX

unsigned char uart_Send_Buff1[8]  = {0x01,0x03,0x00,0x08,0x00,0x01,0x05,0xC8};
unsigned char uart_Send_Buff2[8]  = {0x02,0x03,0x00,0x00,0x00,0x02,0xC4,0x38};
unsigned char uart_Send_Buff3[8] ={0x03,0x03,0x00,0x00,0x00,0x01,0x85,0xE8};
unsigned char phbuff[7];
unsigned char fxbuff[9];
unsigned char fsbuff[7];

int ph;
int fs; //尖头朝北安装 
String fx;
int angle;int temp;
int readirect(unsigned char buff[9])
{
  //fx 计算
  if(!(buff[6]==255 && buff[7]==255 && buff[8]==255)){
temp=buff[0]<<8;
return temp+buff[1];
}
return -1;
}

void displaythlm1602();
void displayno485();
void setup()
{
  // use Serial (port 0); initialize Modbus communication baud rate
  Serial.begin(9600);
  mySerial.begin(4800);

  //  myTFT.begin(9600);
  // myTFT.reset();
  
  // myTFT.fillScreen(BLACK);
  // myTFT.setBacklight(100);//0~255
  
  // myTFT.setRotation(3);

  // myTFT.fillScreen(BLACK);
  // myTFT.setTextSize(5);
  // myTFT.setCursor(110,80);
  
  // myTFT.print("GXEX");
 
  lcd.begin(); // for 16 x 2 LCD module 
  lcd.backlight(); 
  lcd.home (); // set cursor to 0,0 
  lcd.setCursor (0,1); // go to start of 2nd line 
  lcd.print("ok");
 lightMeter.begin();
}


void loop()
{
//displaythlm1602();
// displayno485();

lcd.clear();
lcd.setCursor(0,0);
lcd.print("T :");
lcd.print(t);
lcd.print(" C");


lcd.setCursor(8,0);
lcd.print("H :");
lcd.print(h);
lcd.print("%");

lcd.setCursor(0,1);
lcd.print("L :");
lcd.print(l);
lcd.print(" l");

lcd.setCursor(8,1);

lcd.print("M :");
lcd.print(m);
lcd.print("");


}

void displayno485(){
//DHT.read11(D);
// t=DHT.temperature;
// h=DHT.humidity;
//m=analogRead(MOI);
// l=lightMeter.readLightLevel();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("T :");
lcd.print(t);
lcd.print(" C");


lcd.setCursor(8,0);
lcd.print("H :");
lcd.print(h);
lcd.print("%");

lcd.setCursor(0,1);
lcd.print("L :");
lcd.print(l);
lcd.print(" l");

lcd.setCursor(8,1);

lcd.print("M :");
lcd.print(m);
lcd.print("");


}

void displaythlm1602(){
DHT.read11(D);
t=DHT.temperature;
h=DHT.humidity;
m=analogRead(MOI);
l=lightMeter.readLightLevel();

mySerial.write(uart_Send_Buff1, 8);
  delay(50);
while(mySerial.available()>0){
    mySerial.readBytes(phbuff,7);
    mySerial.flush();
  }
  delay(10);

  /* for(i=0;i<7;i++){
    Serial.print(phbuff[i],HEX);
    Serial.print(":");
    }
    Serial.println();
 */

if(!(phbuff[2]==255 && phbuff[3]==255)){ 
  ph=phbuff[2];
  
  }

  Serial.println(ph);
    
 mySerial.write(uart_Send_Buff2, 8);
  delay(50);
while(mySerial.available()>0){
    mySerial.readBytes(fxbuff,9);
    mySerial.flush();
  }
  delay(10);

  
/*    for(i=0;i<9;i++){
    Serial.print(fxbuff[i],HEX);
    Serial.print("-");
    }  */
    angle=readirect(fxbuff);
    Serial.println(angle);



    

 mySerial.write(uart_Send_Buff3, 8);
  delay(50);
   while(mySerial.available()>0){
    mySerial.readBytes(fsbuff,7);
    mySerial.flush();
  }

  delay(10);

  
  /* for(i=0;i<7;i++){
    Serial.print(fsbuff[i],HEX);
    Serial.print(":");
    } */

  if (!(fsbuff[5]==255 && fsbuff[6]==255))
  {
    /* code */
    fs=fsbuff[0];
  }
      Serial.println(fs);

lcd.setCursor(0,0);
lcd.print("T :");
lcd.print(t);
lcd.print(" C");


lcd.setCursor(8,0);
lcd.print("H :");
lcd.print(h);
lcd.print("%");

lcd.setCursor(0,1);
lcd.print("L :");
lcd.print(l);
lcd.print(" l");

lcd.setCursor(8,1);

lcd.print("M :");
lcd.print(m);
lcd.print("");


  myTFT.fillScreen(BLACK);
  myTFT.setTextSize(5);
  myTFT.setCursor(110,80);
 
  myTFT.print("PH: ");
  int pp=ph / 10 % 10;
  myTFT.print(pp);
  myTFT.print(".");
  myTFT.print(ph % 10);

  myTFT.println("");

  myTFT.print("ANGLE: ");
  
  myTFT.print(angle);

  myTFT.println("");

  myTFT.print("SPEED: ");
  int p=ph / 10 % 10;

  int p10=fs /10 %10;
  int p1=fs%10;

  myTFT.print(p10);
  myTFT.print(".");
  myTFT.print(p1);
  myTFT.println(" m/s");


  }