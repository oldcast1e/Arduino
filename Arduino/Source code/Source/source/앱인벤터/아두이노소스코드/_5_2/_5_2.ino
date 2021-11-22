#include <SoftwareSerial.h>

SoftwareSerial btSerial = SoftwareSerial(9, 10); 

int redLed = 6;
int greenLed = 5;
int blueLed = 3;

void setup()
{
  btSerial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void loop()
{
  if(btSerial.available() > 0 )
  {
    String strData = btSerial.readStringUntil('\n');

    if(strData.startsWith("REDON") == 1) 
    {
      digitalWrite(redLed, HIGH);
    }
    else if(strData.startsWith("REDOFF") == 1) 
    {
      digitalWrite(redLed, LOW);
    }
    else if(strData.startsWith("GREENON") == 1) 
    {
      digitalWrite(greenLed, HIGH);
    }
    else if(strData.startsWith("GREENOFF") == 1) 
    {
      digitalWrite(greenLed, LOW);
    }
    else if(strData.startsWith("BLUEON") == 1) 
    {
      digitalWrite(blueLed, HIGH);
    }
    else if(strData.startsWith("BLUEOFF") == 1) 
    {
      digitalWrite(blueLed, LOW);
    }
  }
}
