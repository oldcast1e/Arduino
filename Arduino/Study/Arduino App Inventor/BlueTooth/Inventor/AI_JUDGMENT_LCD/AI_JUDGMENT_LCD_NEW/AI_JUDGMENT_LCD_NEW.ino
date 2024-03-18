#include<SoftwareSerial.h>

#include <Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial btS = SoftwareSerial(9,10);
void setup(){

  btS.begin(9600);
  lcd.init();
  lcd.backlight();
  
}

void loop(){

  if(btS.available()){
    String str = btS.readStringUntil('\n');
    str.trim();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(str);
  }
  
}
