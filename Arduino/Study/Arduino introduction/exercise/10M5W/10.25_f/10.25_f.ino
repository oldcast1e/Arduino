#include <Servo.h>

const int SERVO = 9;
Servo servo;

void setup(){
  servo.attach(SERVO);
  servo.write(0);

  delay(1000);
  
  for(int t=0;t<=180;t++){
    servo.write(t);
    delay(30);
    
  }

servo.detach();
}

void loop() {


}
