#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9,10);

LiquidCrystal LCD(4, 6, 8, 11, 12, 13); //블루투스 땜에 위치 이동

void setup()
{
  LCD.begin(16, 2); // 16x2사이즈의 LCD사용을 시작
  Serial.begin(9600);
  btS.begin(9600);
  LCD.setCursor(0,0);       
  LCD.print("AI DECISION:");
  
}

void loop()
{

  if(btS.available()){
  String str = btS.readStringUntil('\n');  
                  
  LCD.clear();
  
  LCD.setCursor(0,0);       
  LCD.print("AI DECISION:");
  LCD.setCursor(0,1);
  LCD.print(str); 

   return;
  }
}
