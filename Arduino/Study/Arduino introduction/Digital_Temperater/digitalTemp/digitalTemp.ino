#include <LiquidCrystal.h>

LiquidCrystal lcd(4,6,10,11,12,13);

int T = A0;

void setup() {

lcd.begin(16,2);

lcd.setCursor(0,0);
lcd.print("HanCom CQ TEMP");
  
}

void loop() {

float v,TC;
v= analogRead(T)*5.0;
v /=1024.0;

lcd.setCursor(0,1);
lcd.print(v);

lcd.setCursor(4,1);
lcd.print("V");

lcd.setCursor(10,1);
TC =(v-0.5)*100;

lcd.print(TC);

lcd.setCursor(15,1);
lcd.print("c");

delay(500);

}
