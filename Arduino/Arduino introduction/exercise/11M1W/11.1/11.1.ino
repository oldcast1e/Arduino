#include <TimerOne.h>

const int L = 10;

void setup() {

  Timer1.initialize();

  Timer1.pwm(L,0);
  Timer1.setPeriod(500000);

  Timer1.setPwmDuty(L,300);
  

}

void loop() {
  
}
