#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9,10);

LiquidCrystal LCD(4, 6, 8, 11, 12, 13); //블루투스 땜에 위치 이동

void setup()
{
  LCD.begin(16, 2); // 16x2사이즈의 LCD사용을 시작
  Serial.begin(9600);
  btS.begin(9600);
  
}

void loop()
{

  LCD.setCursor(0,0);         // lcd 0,0좌표에서부터
  LCD.print("AI DECISION:");

  if(btS.available()){
  String str = btS.readString();                   //read()가 아닌 readString()으로 읽기
                                                 //왜? 웬만한 교과서에는 read()로 한 문자만 읽어오는 것만 설명하는지 모르겠음
  str = str.substring(0, str.length()-1);
  LCD.setCursor(0,1);         // lcd 0,0좌표에서부터
  LCD.print(str); 

   return;
  }
}
