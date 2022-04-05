/**
블루투스 통신 테스트 코드
 */
#include <SoftwareSerial.h>
SoftwareSerial btSerial = SoftwareSerial(2,3);

void setup(){
  Serial.begin(9600);
  btSerial.begin(9600);
}

void loop(){
    if(Serial.available()) btSerial.write(Serial.read());
    if(btSerial.available()) Serial.write(btSerial.read());
}
