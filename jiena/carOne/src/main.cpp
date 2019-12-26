#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WMHead.h>
#include <WMBoard.h>
#include <Chrono.h>

SoftwareSerial BTSerial(9,10); 

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
WMRGBLed rgbLED(0,4);
WMLineFollower lineFollower1(11,12);
WMDCMotor motor1(8);
WMDCMotor motor2(7);

double distance;
WMUltrasonic Ultrasonic(4,3);
WMPasBuzzer PasBuzzer(2);

String hld;
String loc;
Chrono chronoA; 
Chrono cb;

void jiema();
void setup() {
  Serial.begin(9600);//  
  BTSerial.begin(9600);

  rgbLED.setColor(0,0);
  rgbLED.show();
  
}
String s;
void loop() {
		distance=Ultrasonic.Distance();
cb.restart();
		while (distance<40)
		{
			if(cb.hasPassed(100)){
				distance=Ultrasonic.Distance();
				cb.restart();
			}
				motor1.reverseRun(0);
				motor2.reverseRun(0);
				PasBuzzer.setBuzzerTone(440,500);
			
		}
		
			
Serial.println(distance);
jiema();
 
if(lineFollower1.readSensorStatus(1)){
		motor1.reverseRun(50);
		motor2.reverseRun(20);
	}else{
		if(lineFollower1.readSensorStatus(2)){
			motor1.reverseRun(20);
			motor2.reverseRun(50);
		}else{
			if (hld=="RED")
			{
				chronoA.restart();
				while (loc=="HLD")
				{
					motor1.reverseRun(0);
					motor2.reverseRun(0);
					if(chronoA.hasPassed(10)){
						chronoA.restart();
						jiema();
					}

				}	
			}
			
			motor1.reverseRun(40);
			motor2.reverseRun(40);
			
		}
	}
	}

void jiema(){
if (BTSerial.available()){
s=BTSerial.readString();
Serial.println("***************************************************");
Serial.println(s);
//s="0RED1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD1HLD0GRE1NOH";
int last0=s.lastIndexOf("0");
int last1=s.lastIndexOf("1");
if(last0>=0){hld=s.substring(last0+1,last0+4);}
if(last1>=0){loc=s.substring(last1+1,last1+4);}
Serial.print("hld="+hld);
if (hld=="GRE")
{
	loc="NOH";
}
Serial.println(" loc="+loc);
}
}


