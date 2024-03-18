#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial btSerial(9, 10);

void setup()
{
  btSerial.begin(9600);
  lcd.init();
  lcd.init();
  lcd.backlight();
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
  }
}
