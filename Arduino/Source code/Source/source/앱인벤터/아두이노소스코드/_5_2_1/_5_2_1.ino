#include <SoftwareSerial.h>

SoftwareSerial btSerial = SoftwareSerial(9, 10); 

int redLed = 6;
int greenLed = 5;
int blueLed = 3;

void setup()
{
  btSerial.begin(9600);
}

void loop()
{
  if(btSerial.available() > 0 )
  {
    String strData = btSerial.readStringUntil('\n');

    if(strData.startsWith("REDHIGH") == 1) 
    {
      analogWrite(redLed, 255);
    }
    else if(strData.startsWith("REDLOW") == 1) 
    {
      analogWrite(redLed, 100);
    }
    else if(strData.startsWith("REDOFF") == 1) 
    {
      analogWrite(redLed, 0);
    }
  }
}
