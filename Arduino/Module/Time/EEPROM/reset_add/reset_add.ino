#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
      }
      Serial.println("EEPROM이 초기화되었습니다.");
}

void loop() {
  if (Serial.available()) {
    // 시리얼 모니터로부터 입력 받기
    String input = Serial.readStringUntil('\n');
    
    // 입력값이 'reset'인 경우 EEPROM 초기화
    if (input.equals("reset")) {
      for (int i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
      }
      Serial.println("EEPROM이 초기화되었습니다.");
    } 
    // 다른 경우 입력값을 EEPROM에 저장
    else {
      for (int i = 0; i < input.length(); i++) {
        EEPROM.write(i, input[i]);
      }
      EEPROM.write(input.length(), '\0'); // 문자열 끝에 NULL 문자 추가
      Serial.println("입력값이 EEPROM에 저장되었습니다.");
    }
  }
}
