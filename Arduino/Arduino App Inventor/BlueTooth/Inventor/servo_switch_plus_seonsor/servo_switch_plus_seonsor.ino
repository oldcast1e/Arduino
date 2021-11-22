#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial btS = SoftwareSerial(2, 3); 
Servo ms;

int E = 10;
int T = 9;

int st = LOW;

void setup() {

  ms.attach(6);
  btS.begin(9600);
  ms.write(90);

  pinMode(E, INPUT);
  pinMode(T, OUTPUT);

  Serial.begin(9600);

}

void loop() {

  if (btS.available()) {

    int u = btS.read();

    if (u == '1') {
      ms.write(72);
    }
    if (u == '0') {
      ms.write(115);
    }
    if (u == '3') {
      ms.write(90);
    }
  }

  digitalWrite(T, LOW);
  delayMicroseconds(2);

  digitalWrite(T, HIGH);
  delayMicroseconds(10);

  digitalWrite(T, LOW);

  unsigned long D = pulseIn(E, HIGH);
  long d = (D / 2) / 29.1;

  delay(100);
  if (d < 70 || 80 < d) {
    delay(1000);
    st = (st == LOW) ? HIGH : LOW;
    if (st == LOW) {
      ms.write(115);
    }
    else if (st == HIGH) {
      ms.write(72);

    }
    Serial.println(d);
  }

}
