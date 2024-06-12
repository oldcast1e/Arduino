void setup() {
  Serial.begin(115200); // 시리얼 통신 속도 설정 (보통 9600 사용)
}

void loop() {
  if (Serial.available()) { // 시리얼 모니터에 데이터가 있는지 확인
    char inputChar = Serial.read(); // 시리얼 모니터에서 한 문자 읽기
    Serial.print(inputChar); // 읽은 문자를 시리얼 모니터에 출력
  }
}
/*아두이노 포트 번호 변경*/
