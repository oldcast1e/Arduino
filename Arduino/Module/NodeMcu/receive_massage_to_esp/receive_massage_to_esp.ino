// Arduino Mega Serial1 통신 코드

unsigned long previousMillis = 0;
const unsigned long interval = 5000; // 5초마다 메시지 전송

void setup() {
  Serial.begin(115200);    // Serial 모니터 초기화
  Serial1.begin(115200);   // Serial1 초기화 (ESP8266과 통신)
  Serial.println("Arduino Mega Serial1 Communication Initialized");
}

void loop() {
  // 5초마다 "Hello World!" 전송
  unsigned long currentMillis = millis();
  // if (currentMillis - previousMillis >= interval) {
  //   previousMillis = currentMillis;
  //   Serial1.println("Hello World!"); // ESP8266으로 메시지 전송
  //   Serial.println("Sent: Hello World!"); // Serial 모니터에 전송 확인
  // }

  // ESP8266에서 받은 데이터를 Serial 모니터에 출력
  if (Serial1.available()) {
    String received = Serial1.readStringUntil('\n'); // 수신 데이터 읽기
    Serial.print("Received from ESP8266: ");
    Serial.println(received);
  }
}
