#include <SoftwareSerial.h>

SoftwareSerial btSerial = SoftwareSerial(9, 10);

int sw1 = 7;
int sw2 = 6;
int sw3 = 5;

void setup()
{
  btSerial.begin(9600);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
}

void loop()
{
  if (swInput1(sw1) == 1)
  {
    btSerial.println("sw1");
  }
  else if (swInput2(sw2) == 1)
  {
    btSerial.println("sw2");
  }
  else if (swInput3(sw3) == 1)
  {
    btSerial.println("sw3");
  }
}

int swInput1(int inPin)
{
  static int oldSw = 1;
  static int newSw = 1;
  newSw = digitalRead(inPin);
  if (oldSw != newSw)
  {
    oldSw = newSw;
    if (newSw == 0)
    {
      delay(200);
      return 1;
    }
  }
  return 0;
}

int swInput2(int inPin)
{
  static int oldSw = 1;
  static int newSw = 1;
  newSw = digitalRead(inPin);
  if (oldSw != newSw)
  {
    oldSw = newSw;
    if (newSw == 0)
    {
      delay(200);
      return 1;
    }
  }
  return 0;
}

int swInput3(int inPin)
{
  static int oldSw = 1;
  static int newSw = 1;
  newSw = digitalRead(inPin);
  if (oldSw != newSw)
  {
    oldSw = newSw;
    if (newSw == 0)
    {
      delay(200);
      return 1;
    }
  }
  return 0;
}
