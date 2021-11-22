#include <SoftwareSerial.h>

SoftwareSerial btSerial = SoftwareSerial(9, 10); 

int echo = 6;
int trig = 7;

void setup()
{
  btSerial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);

  float distanceCM = ((34000*duration)/1000000)/2;

  if (distanceCM <= 5 && distanceCM < 15) btSerial.println("do");
  else if (distanceCM <= 15 && distanceCM < 25) btSerial.println("le");
  else if (distanceCM <= 25 && distanceCM < 35) btSerial.println("mi");
  else if (distanceCM <= 35 && distanceCM < 45) btSerial.println("fa");
  else if (distanceCM <= 45 && distanceCM < 55) btSerial.println("sol");
  else  btSerial.println("out");

  delay(1000);
}
