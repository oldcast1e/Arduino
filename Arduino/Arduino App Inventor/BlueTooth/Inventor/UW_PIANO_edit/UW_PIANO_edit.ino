#include <SoftwareSerial.h>
SoftwareSerial btS = SoftwareSerial(9, 10);

int E = 6;
int T = 7;

void setup() {
  btS.begin(9600);
  pinMode(E, INPUT);
  pinMode(T, OUTPUT);
}

void loop() {

  digitalWrite(T, HIGH);
  delayMicroseconds(10);
  digitalWrite(T, LOW);

  unsigned long D = pulseIn(E, HIGH);

  float d = ((34000 * D) / 1000000) / 2;

  if (d <= 5 && 15 < d) btS.println("do");
  else if (d <= 15 && 25 < d) btS.println("re");
  else if (d <= 25 && 35 < d) btS.println("mi");
  else if (d <= 35 && 45 < d) btS.println("fa");
  else if (d <= 45 && 55 < d) btS.println("sol");
  else if (d <= 55 && 65 < d) btS.println("ra");
  else if (d <= 65 && 75 < d) btS.println("si");
  else if (d <= 75 && 85 < d) btS.println("Do");
  else btS.println("OUT");

  delay(1000);
}
