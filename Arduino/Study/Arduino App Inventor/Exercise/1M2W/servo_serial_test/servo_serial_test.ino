#include <Servo.h>

const int M = 10;
Servo s;

void setup(){

  s.attach(M);
  Serial.begin(9600);
    
}

void loop(){

  if(Serial.available()>0){

  int u = Serial.read();
     if(0<=u && u<=180){

      s.write(u);
      delay(15);
      
  }
}
}
