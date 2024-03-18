#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Hello!!");
  lcd.setCursor(2, 1);
  lcd.print("App Inventor");
}


void loop()
{
}
