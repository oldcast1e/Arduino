#include <SoftwareSerial.h> 

SoftwareSerial btSerial = SoftwareSerial(9, 10);

void setup()
{
  Serial.begin(9600);
  btSerial.begin(9600);
}

void loop()
{
  if (btSerial.available() > 0)
  {
    Serial.write(btSerial.read());
  }
  if (Serial.available() > 0)
  {
    btSerial.write(Serial.read());
  }
}
