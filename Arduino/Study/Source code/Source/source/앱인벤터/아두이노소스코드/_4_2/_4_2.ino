#include <SoftwareSerial.h>

SoftwareSerial btSerial = SoftwareSerial(9, 10);

int swPin = 7;

void setup()
{
  btSerial.begin(9600);
  pinMode(swPin, INPUT);
}

void loop()
{
  int switchState = digitalRead(swPin);

  if (switchState == 1)
  {
    btSerial.println("sw On");
  }
  else if (switchState == 0)
  {
    btSerial.println("sw Off");
  }
  delay(300);
}
