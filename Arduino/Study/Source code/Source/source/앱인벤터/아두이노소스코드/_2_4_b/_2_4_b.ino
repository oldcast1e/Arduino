#include <SoftwareSerial.h>

SoftwareSerial btSerial = SoftwareSerial(9, 10);

void setup()
{
  btSerial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop()
{
  if (btSerial.available() > 0 )
  {
    char sData = btSerial.read();
    if (sData == 'a')
    {
      btSerial.println("LED ON");
      digitalWrite(8, HIGH);
    }
    else if (sData == 'b')
    {
      btSerial.println("LED OFF");
      digitalWrite(8, LOW);
    }
  }
}
