#include<TimerOne.h>

const int B= 10;
const int m[] = {262,294,330,349,393,440,494,523};


void setup() {
 
Timer1.initialize();
Timer1.pwm(B,0);

Timer1.setPwmDuty(B,100);

for(int t =0; t<=7; t++){
Timer1.setPeriod(1000000/m[t]);
delay(500);

}

Timer1.setPwmDuty(B,0);
}
void loop() {


}
