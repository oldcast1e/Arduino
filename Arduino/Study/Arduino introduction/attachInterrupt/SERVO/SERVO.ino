# include<Servo.h>

const int M= 10;
const int b =2;

Servo s;

int ST = 30;
bool SC = false;

void bp(){

  ST=(ST==30)?150:30;
  SC = true;
}

void setup() {

 pinMode(b,INPUT);
 attachInterrupt(digitalPinToInterrupt(b),bp,RISING);
 s.attach(M);
 s.write(0);
 delay(1000);
}

void loop() {

 if(SC){
  SC =false;
  s.write(ST);
 }
}
