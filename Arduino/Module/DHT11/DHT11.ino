#include <DHT.h>

// DHT 센서 타입과 핀 번호 설정
#define DHTPIN 22     // DHT 센서를 연결한 디지털 핀
#define DHTTYPE DHT11 // DHT 센서 타입 (DHT11, DHT22, DHT21 중 하나)

// DHT 객체 초기화
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // 시리얼 통신 초기화
  dht.begin();        // DHT 센서 초기화
  Serial.println("DHT 센서 테스트 시작");
}

void loop() {
  delay(2000); // 센서 읽기 간격 (2초)

  // 온도와 습도 데이터 읽기
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // 센서 오류 확인
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT 센서 데이터를 읽을 수 없습니다!");
    return;
  }

  // 결과 출력
  Serial.print("현재 온도: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("현재 습도: ");
  Serial.print(humidity);
  Serial.println(" %");
}
