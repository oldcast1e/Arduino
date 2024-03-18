#include "PinChangeInterrupt.h"
#include<Servo.h>
Servo sv;

const int bt = 2;
const int servo = 10;
int angle = 0;
bool bsc = false;

void bf(){
  angle = (angle==0?180:0);
  bsc = false;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(bt,INPUT);

  attachPCINT(digitalPinToPCINT(bt),bf,RISING);
  sv.attach(servo);
  sv.write(0);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(bsc){
    sv.write(angle);
    bsc = false;
  }

}
