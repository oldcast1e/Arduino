#include <SoftwareSerial.h>

// SoftwareSerial 설정 (GPIO 14: RX, GPIO 12: TX)
SoftwareSerial espSerial(14, 12);

unsigned long previousMillis = 0;
const unsigned long interval = 5000; // 5초마다 메시지 전송

void setup() {
  Serial.begin(115200);     // Serial 모니터 초기화
  espSerial.begin(115200);  // SoftwareSerial 초기화 (Mega와 통신)
  Serial.println("ESP8266 SoftwareSerial Communication Initialized");
}

void loop() {
  // 5초마다 "Hello World!" 전송
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    espSerial.println("Hello World!"); // Mega로 메시지 전송
    Serial.println("Sent: Hello World!"); // Serial 모니터에 전송 확인
  }

  // Mega에서 받은 데이터를 Serial 모니터에 출력
  if (espSerial.available()) {
    String received = espSerial.readStringUntil('\n'); // 수신 데이터 읽기
    Serial.print("Received from Mega: ");
    Serial.println(received);
  }
}
