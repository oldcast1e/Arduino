#include <TimerOne.h>
const int L = 10;

void setup(){

  Timer1.initialize();

  Timer1.pwm(L,0);
  Timer1.setPeriod(100);
for(int t =0; t<=1023; t++){
  Timer1.setPwmDuty(L,t);
  delay(4);
}
for(int t=1023; 0<=t; t--){
  Timer1.setPwmDuty(L,t);
  delay(4);
}  
}

void loop(){
  
}
