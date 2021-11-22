#include <LiquidCrystal.h>

LiquidCrystal LCD(4, 6, 10, 11, 12, 13);

void setup()
{
  LCD.begin(16, 2); // 16x2사이즈의 LCD사용을 시작
  Serial.begin(115200);
}

void loop()
{

  LCD.setCursor(0,0);         // lcd 0,0좌표에서부터
  LCD.print("your sentence:");

  if(Serial.available()){
  int u = Serial.read();


  LCD.setCursor(0,1);         // lcd 0,0좌표에서부터
  LCD.print(u); 

   return;
  }
  
  
  
         
  
  
}
