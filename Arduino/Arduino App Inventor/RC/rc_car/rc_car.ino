#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor m1 = (1); //전(왼)
AF_DCMotor m2 = (2); // 후(왼)
AF_DCMotor m3 = (3); //후(오)
AF_DCMotor m4 = (4); //전(오)

SoftwareSerial btS = SoftwareSerial(9, 10);

void setup() {

  m1.setSpeed(0);
  m1.run(RELEASE);
  m2.setSpeed(0);
  m2.run(RELEASE);
  m3.setSpeed(0);
  m3.run(RELEASE);
  m4.setSpeed(0);
  m4.run(RELEASE);

  btS.begin(9600);
}

void loop() {

  if (btS.available()) {
    char u = btS.read();
    if (u == 'f')gm(170);
    else if (u == 'b')bm(170);
    else if (u == 'r')rm(150);
    else if (u == 'l')lm(150);
    else if (u == 's')sm();
    else sm();
  }

}

void gm(uint8_t S) {
  m1.setSpeed(S);
  m2.setSpeed(S);
  m3.setSpeed(S);
  m4.setSpeed(S);

  m1.run(FORWARD);
  m2.run(FORWARD);
  m3.run(FORWARD);
  m4.run(FORWARD);

}

void bm(uint8_t S) {
  m1.setSpeed(S);
  m2.setSpeed(S);
  m3.setSpeed(S);
  m4.setSpeed(S);

  m1.run(BACKWARD);
  m2.run(BACKWARD);
  m3.run(BACKWARD);
  m4.run(BACKWARD);

}

void rm(uint8_t S) {
  m1.setSpeed(S);
  m2.setSpeed(0);
  m3.setSpeed(0);
  m4.setSpeed(S);

  m1.run(FORWARD);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(BACKWARD);

}

void lm(uint8_t S) {
  m1.setSpeed(S);
  m2.setSpeed(0);
  m3.setSpeed(0);
  m4.setSpeed(S);

  m1.run(BACKWARD);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(FORWARD);

}

void sm() {

  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);

}
