#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// SoftwareSerial 핀 설정
SoftwareSerial gpsSerial(3, 2); // RX, TX

// TinyGPS++ 객체 생성
TinyGPSPlus gps;

void setup() {
  // 시리얼 모니터와 GPS 시리얼 설정
  Serial.begin(9600);
  gpsSerial.begin(9600);

  Serial.println("GPS 모듈 초기화 중...");
}

void loop() {
  // GPS 모듈에서 데이터 읽기
  while (gpsSerial.available() > 0) {
    char data = gpsSerial.read();
    gps.encode(data);

    if (gps.location.isUpdated()) {
      // 위도와 경도를 시리얼 모니터에 출력
      Serial.print("위도: ");
      Serial.print(gps.location.lat(), 6);
      Serial.print("\t경도: ");
      Serial.println(gps.location.lng(), 6);
    }
  }
}
