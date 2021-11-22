#include <Servo.h>

const int s= 9;
Servo servo;

void setup() {
 servo.attach(s);

 servo.write(0);

 for(int t =0; t <=5; t++){
  servo.write(0);
  delay(1000);
  servo.write(180);
  delay(1000);
 }
 servo.detach();
}

void loop() {
  // put your main code here, to run repeatedly:

}
