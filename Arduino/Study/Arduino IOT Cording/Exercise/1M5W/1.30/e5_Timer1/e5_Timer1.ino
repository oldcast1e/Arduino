#include <TimerOne.h>
const int L = 2;

void tF(){
  digitalWrite(L,digitalRead(L)^1); 
  Serial.println(digitalRead(L)^1);
}

void setup(){
  pinMode(L,OUTPUT);

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(tF);

  Serial.begin(115200);
}

void loop(){
  
}
