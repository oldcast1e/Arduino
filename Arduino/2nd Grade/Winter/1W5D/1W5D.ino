#include<SoftwareSerial.h>
#include <Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
int line = 0;
void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}
void loop(){
  if (Serial.available()) {
    lcd.setCursor(0,0); lcd.clear();
    String str = Serial.readStringUntil('\n');
    int len = str.length();

    lcd.setCursor(0, line);
    for (int i = 0; (i < len && i < 16); i++) {lcd.print(str[i]);}
    if (len > 16) {//라인 변경
      lcd.setCursor(0, (line == 0) ? 1 : 0);
      //for (int i = 0; i < 16; i++) {lcd.print(" ");}lcd.setCursor(0,line);
      for (int i = 0;( i < len - 16 && i < 16); i++)lcd.print(str[16 + i]);
      
    }
    // lcd.clear();
    //line = (line == 0) ? 1 : 0;
  }
  // if(Serial.available()){
  //   String str = Serial.readStringUntil('\n');
  //   lcd.setCursor(0,line);str.trim();// lcd.clear();
  //   for (int i = 0; i < 16; i++) {lcd.print(" ");}lcd.setCursor(0,line);
  //   lcd.print(str); 
  //   line = line == 0 ? 1 : 0;
    
  //   if(line){ Serial.print("line 1: ");Serial.println(str);}
  //   else {Serial.print("line 2: ");Serial.println(str);}
  // }
}