#include <SoftwareSerial.h>

SoftwareSerial btSerial = SoftwareSerial(9, 10);

int redLedPin = 7;
int yellowLedPin = 6;
int greenLedPin = 5;
int blueLedPin = 4;

void setup()
{
  btSerial.begin(9600);

  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void loop()
{
  if (btSerial.available() > 0)
  {
    char btData = btSerial.read();

    if (btData == 'r')
    {
      digitalWrite(redLedPin, HIGH);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(blueLedPin, LOW);
    }
    else if (btData == 'y')
    {
      digitalWrite(redLedPin, LOW);
      digitalWrite(yellowLedPin, HIGH);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(blueLedPin, LOW);
    }
    else if (btData == 'g')
    {
      digitalWrite(redLedPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(blueLedPin, LOW);
    }
    else if (btData == 'b')
    {
      digitalWrite(redLedPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(blueLedPin, HIGH);
    }
    else if (btData == 'o')
    {
      digitalWrite(redLedPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(blueLedPin, LOW);
    }
  }
}
