#include <TimerOne.h>
 
void setup() { 
  Serial.begin(115200); 

  Timer1.initialize(1000); 
  Timer1.attachInterrupt( timerIsr ); 
}
 
void loop() {
  Serial.println ("| ");
}

void timerIsr() {
  Serial.println (" ]");  
}