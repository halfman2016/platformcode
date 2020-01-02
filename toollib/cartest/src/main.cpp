#include <Arduino.h>
#include <WMHead.h>
#include <WMBoard.h>
#include <Chrono.h>

WMDCMotor motorl(8); //left ,from up
WMDCMotor motorr(7); //right ,from up
//遇黑线输出1 否则0 亮灯
WMLineFollower lineFollower1(11, 12); //11 left ,from up 12 right

int s;
int counl, counr;

//readsensor 0 常规，1 right  in dark 2left in dark 3 all dark
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  s = lineFollower1.readSensors();
  if (s == 1 && counr < 20)
  {
    motorl.reverseRun(40);
    motorr.reverseRun(-5);
    counr++;
  }
  if (s == 1 && counr > 20)
  {
    motorl.reverseRun(40);
    motorr.reverseRun(0);
    counr = 0;
  }

  if (s == 0)
  {
    motorl.reverseRun(40);
    motorr.reverseRun(40);
  }

  if (s == 3)
  {
    motorl.reverseRun(0);
    motorr.reverseRun(40);
  }

  if (s == 2 && counl < 20)
  {
    motorl.reverseRun(-5);
    motorr.reverseRun(40);
    counl++;
  }
  if (s == 2 && counl > 20)
  {
    /* code */
    motorr.reverseRun(40);
    motorl.reverseRun(0);
    counl = 0;
  }
}