#include <TimerOne.h>
const int LED = 7;

void lf(){

  digitalWrite(LED,digitalRead(LED)^1);
}
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(lf);

}

void loop() {
  // put your main code here, to run repeatedly:

}
