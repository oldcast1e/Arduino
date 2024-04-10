#include <IRremote.h>
 
int RECV_PIN = 11; // 11 for UNO

IRrecv irrecv(RECV_PIN);
decode_results results;

// 프로그램 시작 - 초기화 작업
void setup()
{
 Serial.begin(9600); // 시리얼 통신 초기화
 Serial.println("Arduino Examples - IR Receive Module");
 Serial.println(" https://docs.whiteat.com/?p=1296");
 irrecv.enableIRIn(); // Start the receiver 
}

void loop()
{
 if (irrecv.decode(&results)) {
 Serial.println(results.value, HEX);
 irrecv.resume(); // Receive the next value
 }
 delay(100);
}
