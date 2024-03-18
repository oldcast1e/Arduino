#include <TimerOne.h>
 
void setup() {
  pinMode(13, OUTPUT);    
  
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt( timerIsr ); 
}
 
void loop() {}
 
void timerIsr() {
	digitalWrite( 13, digitalRead( 13 ) ^ 1 );
}