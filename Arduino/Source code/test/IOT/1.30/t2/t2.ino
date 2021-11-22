#include <LiquidCrystal.h>

LiquidCrystal LCD(4, 6, 10, 11, 12, 13);
unsigned long tp = 0;
const unsigned int d = 1000;
void setup()
{
  LCD.begin(16, 2); // 16x2사이즈의 LCD사용을 시작
  Serial.begin(115200);
}

void loop()
{

  LCD.setCursor(2,0);         // lcd 0,0좌표에서부터
  LCD.print("TIMER STRAT!");


  LCD.setCursor(5
  ,1); 
  unsigned long now = millis();
  if(now - tp >= 1000){
    tp = now;

    int T = now*0.001;
    

    int minute1 = T/60/10;
    int minute2 = T/60%10;
    int second1 = T%60/10;
    int second2 = T%60%10;

    String a = String(minute1);
    String b = String(minute2);
    String c = String(second1);
    String d = String(second2);
    
    String e = a+b+":"+c+d;
    LCD.print(e);
     
  }// lcd 0,0좌표에서부터
   

  } 
