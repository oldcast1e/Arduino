#include <IRremote.h>
 
IRsend irsend;

// 프로그램 시작 - 초기화 작업
void setup()
{
 Serial.begin(9600); // 시리얼 통신 초기화
 Serial.println("Arduino Examples - IR Send Module");
 Serial.println(" https://docs.whiteat.com/?p=1294"); 
}

int i= 10;
void loop() 
{
 irsend.sendNEC(i++,32); delay(1000);
 irsend.sendNEC(i++,32); delay(1000);
 irsend.sendNEC(i++,32); delay(1000);
 irsend.sendNEC(i++,32); delay(1000); 
}
