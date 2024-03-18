#include <Servo.h>

const int M = 10;
Servo s;

void setup(){

  s.attach(M);
  s.write(0);
  }

void loop(){


  for(int c=0;c<=180;c++){
    s.write(c);
    delay(4);
  }
  for(int c=180;c>=0;c--){
    s.write(c);
    delay(4);
  }
  
}
