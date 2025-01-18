// 아두이노 메가에서 Serial3을 사용하여 HC-06과 통신
void setup() {
  // 시리얼 모니터와의 통신 속도 설정
  Serial.begin(9600);
  
  // HC-06과의 통신 속도 설정 (Serial3 사용)
  Serial3.begin(9600);
}

void loop() {
  // 시리얼 모니터에서 데이터가 들어오면
  if (Serial.available()) {
    // 시리얼 모니터에서 받은 데이터를 읽어서
    String input = Serial.readString();
    
    // 블루투스 모듈로 전송
    Serial3.print(input);
  }

  // 블루투스 모듈에서 데이터가 들어오면
  if (Serial3.available()) {
    // 블루투스 모듈에서 받은 데이터를 읽어서
    String receivedData = Serial3.readString();
    
    // ">>"를 붙여 시리얼 모니터에 출력
    Serial.print(">>");
    Serial.print(receivedData);
  }
}
