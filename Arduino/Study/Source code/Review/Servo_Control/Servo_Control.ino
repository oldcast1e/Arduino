#include <Servo.h>

const int servo = 10;
int angle[3] = {};
int A, cnt = 1, rst = 0;
Servo sv;

void setup() {
  Serial.begin(115200);
  sv.attach(10);
  Serial.println("Servo Motor is Availalbe!");
  sv.write(0);

}
void loop() {

  if (Serial.available()) {
    if (cnt == 1) {
      rst = 0;
      A = Serial.read();
      if (A == 10) cnt = 5;
      else {
        rst += (A - 48) * 100;
        cnt = 2;
        Serial.print("<INPUT A1>");
        Serial.println((A - 48));
      }

    }
    if (cnt == 2) {
      A = Serial.read();
      if (A == 10) {
        cnt = 4;
        rst /= 10;
      }
      else {
        rst += (A - 48) * 10;
        cnt = 3;
        Serial.print("<INPUT A2>");
        Serial.println((A - 48));
      }

    }
    if (cnt == 3) {
      A = Serial.read();
      if (A == 10) {
        cnt = 4;
        rst /= 10;
      }
      else {
        rst += (A - 48);
        cnt = 4;
        Serial.print("<INPUT A3>");
        Serial.println((A - 48));
      }

    }
    if (cnt == 4) {
      if ((rst < 0 || rst > 180) && (A != 10)) {
        Serial.println("Please Check Your Angle");
        Serial.print("INPUT: ");
        Serial.println(rst);
      }
      else {
        Serial.println("Operating...");
        Serial.print("The number you entered:");
        Serial.println(rst);
        sv.write(rst);
        delay(1000);
      }
      cnt = 1;
    }
    else if (cnt == 5) cnt = 1;

  }

}
