#include <Arduino.h>

#include <SoftwareSerial.h> //Software Serial Port
#include <OS_SerialTFT.h>
#include <BH1750.h>
#include <AM2320.h>
#include <Ultrasonic.h>

#define TFT_RX 13 //RX of Serial TFT module connect to D4 of Arduino / OPEN-SMART UNO
#define TFT_TX 12 //TX of Serial TFT to D2

AM2320 th;
BH1750 lightMeter;
SerialTFT myTFT(TFT_RX, TFT_TX);

//报站所需
SoftwareSerial HC(2, 4);      // RX, TX
Ultrasonic ultrasonic1(3, 5); // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic2(6, 9); // (Trig PIN,Echo PIN)
unsigned char bbhhl[] = {0xFD, 0x00, 0x0D, 0x01, 0x01, 0xBB, 0xC6, 0xBA, 0xD7, 0xC2, 0xA5, 0xB5, 0xBD, 0xC1, 0xCB, 0x85};
unsigned char bbdh[] = {0xFD, 0x00, 0x0B, 0x01, 0x01, 0xB6, 0xAB, 0xBA, 0xFE, 0xB5, 0xBD, 0xC1, 0xCB, 0xAD};
unsigned char bbwhdx[] = {0xFD, 0x00, 0x0F, 0x01, 0x01, 0xCE, 0xE4, 0xBA, 0xBA, 0xB4, 0xF3, 0xD1, 0xA7, 0xB5, 0xBD, 0xC1, 0xCB};
unsigned char bbgg[] = {0xFD, 0x00, 0x0B, 0x01, 0x01, 0xB9, 0xE2, 0xB9, 0xC8, 0xB5, 0xBD, 0xC1, 0xCB, 0xDE};
int l, t, h;
int s = 0;
void setup()
{
  HC.begin(9600);

  // put your setup code here, to run once:
  myTFT.begin(9600);
  myTFT.reset();
  myTFT.setBacklight(150); //0~255
  myTFT.setTextSize(4);
  myTFT.setRotation(1);
  myTFT.setBacklight(80);
  lightMeter.begin();
  myTFT.println("Hello");
  Serial.begin(9600);
  Serial.println("Hllo");
}

void loop()
{

  h = th.getHumidity();
  t = th.getTemperature();
  myTFT.fillScreen(BLACK);
  myTFT.setCursor(10, 30);
  myTFT.setTextColor(RED);
  myTFT.print("Temper:");
  myTFT.print(t);
  Serial.println(t);

  myTFT.setTextColor(WHITE);

  myTFT.setCursor(10, 80);
  myTFT.print("Humidity:");
  myTFT.print(h);
  myTFT.print(" %");
  Serial.println(h);

  l = lightMeter.readLightLevel();

  myTFT.setCursor(10, 130);
  myTFT.setTextColor(GREEN);

  myTFT.print("Light:");
  myTFT.print(l);
  myTFT.print(" lux");
  Serial.println(l);

  if (ultrasonic1.Ranging(CM) < 10)
  {
    HC.write(bbhhl, 16);
  }

  if (ultrasonic2.Ranging(CM) < 10)
  {

    HC.write(bbdh, 14);
  }
  delay(500);
}
