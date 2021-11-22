#include <SoftwareSerial.h>
#include <AFMotor.h>     

AF_DCMotor motor_1(1); 
AF_DCMotor motor_4(4);

SoftwareSerial BTSerial(9, 10);

void setup() {
  motor_1.setSpeed(0); 
  motor_1.run(RELEASE);
  motor_4.setSpeed(0);
  motor_4.run(RELEASE);

  BTSerial.begin(9600);
}

void loop() {
    if (BTSerial.available()){
      char val = BTSerial.read();
      if(val == 'f')        go_motor(170);
      else if(val == 'b')   back_motor(170);
      else if(val == 'r')   right_motor(150);
      else if(val == 'l')   left_motor(150);
      else if(val == 's')   stop_motor();
      else                  stop_motor();
    }
}

void go_motor(uint8_t speedSet) {
  motor_1.setSpeed(speedSet);
  motor_4.setSpeed(speedSet);
  motor_1.run(FORWARD);
  motor_4.run(FORWARD);
}

void back_motor(uint8_t speedSet) {
  motor_1.setSpeed(speedSet);
  motor_4.setSpeed(speedSet);
  motor_1.run(BACKWARD);
  motor_4.run(BACKWARD);
}

void right_motor(uint8_t speedSet) {
  motor_1.setSpeed(speedSet);
  motor_4.setSpeed(speedSet);
  motor_1.run(FORWARD);
  motor_4.run(BACKWARD);
}

void left_motor(uint8_t speedSet) {
  motor_1.setSpeed(speedSet);
  motor_4.setSpeed(speedSet);
  motor_1.run(BACKWARD);
  motor_4.run(FORWARD);
}


void stop_motor() {
  motor_1.run(RELEASE);
  motor_4.run(RELEASE);
}
