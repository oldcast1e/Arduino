# include <TimerOne.h>


const int m = 9;


const int Sp = 20000;
const int Sm= (1024/20)*0.7;
const int SM = (1024/20)*2.3;

void setup() {

  Timer1.initialize();
  Timer1.pwm(m,0);

  Timer1.setPeriod(Sp);
  Timer1.setPwmDuty(m,Sm);
  delay(1000);

  for( int a =Sm; a<= SM;a++){
  Timer1.setPwmDuty(m,a);
  delay(30);
  
    
  }
Timer1.disablePwm(m);
}

void loop() {

}
