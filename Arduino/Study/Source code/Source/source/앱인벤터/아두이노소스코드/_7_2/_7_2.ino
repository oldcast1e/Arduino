#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial btSerial(9, 10);

int ledR = 4;
int ledY = 3;
int ledB = 2;

void setup()
{
  btSerial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop()
{
  if (btSerial.available())
  {
    String strData = btSerial.readStringUntil('\n');
    strData.trim();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(strData);
    if (strData.indexOf("driver") >= 0 )
    {
      digitalWrite(ledR, LOW);
      digitalWrite(ledY, LOW);
      digitalWrite(ledB, HIGH);
    }
    else if (strData.indexOf("switch") >= 0 )
    {
      digitalWrite(ledR, LOW);
      digitalWrite(ledY, HIGH);
      digitalWrite(ledB, LOW);
    }
    else if (strData.indexOf("led") >= 0 )
    {
      digitalWrite(ledR, HIGH);
      digitalWrite(ledY, LOW);
      digitalWrite(ledB, LOW);
    }
  }
}
