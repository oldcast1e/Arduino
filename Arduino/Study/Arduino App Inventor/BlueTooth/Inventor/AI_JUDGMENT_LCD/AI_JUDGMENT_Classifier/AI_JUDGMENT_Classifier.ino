#include<SoftwareSerial.h>

#include <Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial btS = SoftwareSerial(9,10);

const int L[3] = {2,3,4};

void setup(){

  btS.begin(9600);
  lcd.init();
  lcd.backlight();

  for(int n =0; n<=2; n++){
  pinMode(L[n],OUTPUT);
  }

  digitalWrite(L[0],HIGH);
  delay(1000);
  digitalWrite(L[0],LOW);
}

void loop(){

  if(btS.available()){
    String str = btS.readStringUntil('\n');
    str.trim();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(str);

    if(str.indexOf("driver")>=0){
      digitalWrite(L[0],LOW);
      digitalWrite(L[1],LOW);
      digitalWrite(L[2],HIGH);
      
    }
    else if(str.indexOf("switch")>=0){
      digitalWrite(L[0],LOW);
      digitalWrite(L[1],HIGH);
      digitalWrite(L[2],LOW);
      
    }

    else if (str.indexOf("led")>=0){
      digitalWrite(L[0],HIGH);
      digitalWrite(L[1],LOW);
      digitalWrite(L[2],LOW);
      
    }
  }
  
}
