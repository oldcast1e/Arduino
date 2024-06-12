#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wi-Fi 네트워크 SSID와 비밀번호 설정
const char* ssid = "oldcast1e";
// const char* ssid = "heonseong";
const char* password = "dlgjstjd";
// const char* password = "popopopo";

// 서버 주소 설정
const char* serverName = "http://192.168.0.4:5001";

WiFiClient client;

void setup() {
  // 시리얼 통신 초기화
  Serial.begin(115200);
  
  // Wi-Fi 연결
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Wi-Fi가 연결된 상태에서만 서버에 요청
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // 서버에 요청 설정
    http.begin(client, serverName);
    
    // GET 요청 보내기
    int httpCode = http.GET();
    
    // 응답 코드가 200(성공)일 경우 응답 데이터 읽기
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println("Server response:");
        Serial.println(payload);
      }
    } else {
      Serial.printf("GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    // 요청 종료
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  
  // 다음 요청을 위해 10초 대기
  delay(10000);
}
