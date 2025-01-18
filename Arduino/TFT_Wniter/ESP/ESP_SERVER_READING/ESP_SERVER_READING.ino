#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Wi-Fi 설정
// const char* ssid = "oldcast1e"; // Wi-Fi SSID
const char* ssid = "1606_2G"; // Wi-Fi SSID
// const char* password = "popopopo"; // Wi-Fi 비밀번호
const char* password = "a12345678"; // Wi-Fi 비밀번호

// Python 서버 주소 및 포트
const char* serverHost = "192.168.1.5"; // http:// 제외한 서버 IP
// const char* serverHost = "192.168.1.9"; // http:// 제외한 서버 IP
const int serverPort = 8080; // Python 서버 포트

void setup() {
  Serial.begin(115200);
  delay(10);

  // Wi-Fi 연결 설정
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to Wi-Fi. IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client;

  // Python 서버에 연결 시도
  if (!client.connect(serverHost, serverPort)) {
    Serial.println("Connection to server failed! Trying again...");
    delay(5000);
    return;
  } else {
    Serial.println("Connected to server.");
  }

  // Python 서버로 요청 전송
  client.println("GET / HTTP/1.1");
  client.println("Host: " + String(serverHost));
  client.println("Connection: close");
  client.println();

  // Python 서버로부터 응답 읽기
  String response = "";
  while (client.connected() || client.available()) {
    if (client.available()) {
      char c = client.read();
      response += c;
    }
  }

  // 응답 출력
  Serial.println("Response from server:");
  Serial.println(response);

  // 연결 종료
  client.stop();
  Serial.println("Disconnected from server.");

  delay(10000); // 10초마다 서버에 재요청
}

