#include<TimerOne.h>

const int B= 10;

void setup() {
 
Timer1.initialize();
Timer1.pwm(B,0);

Timer1.setPwmDuty(B,512);

Timer1.setPeriod(1000000/262);
delay(3000);


Timer1.setPwmDuty(B,0);
}
void loop() {


}
