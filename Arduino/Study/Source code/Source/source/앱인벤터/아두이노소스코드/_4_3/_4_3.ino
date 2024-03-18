#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial btSerial = SoftwareSerial(9, 10);

Servo myservo;

void setup()
{
  myservo.attach(6); 
  btSerial.begin(9600); 
}

void loop()
{
  if (btSerial.available() > 0)
  {
    int btData = btSerial.read();

    if (btData >= 0 && btData <= 180)  
    {
      myservo.write(btData);
      delay(15);
    }
  }
}
