#include<Servo.h>
const int servo = 10;
const int bt = 2;

int serang = 0;
bool bsc = false;
Servo sv;

void bf(){
  serang = (serang==0?180:0);
  bsc = true;
}
void setup() {
  // put your setup code here, to run once:

  attachInterrupt(digitalPinToInterrupt(bt),bf,RISING);
  sv.attach(servo);
  sv.write(0);
  delay(1000);
  pinMode(bt,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(bsc){
    sv.write(serang);
    bsc = false;
    delay(100);
  }

}
