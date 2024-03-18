#include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9, 10);


void setup() {
  // put your setup code here, to run once:
  btS.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (btS.available() > 0) {

    char u = btS.read();
    if (u == 'a') {

      btS.println("LED on");
      digitalWrite(2, HIGH);
    }

    else if (u == 'b') {

      btS.println("LED off");
      digitalWrite(2, LOW);
    }
  }
}
