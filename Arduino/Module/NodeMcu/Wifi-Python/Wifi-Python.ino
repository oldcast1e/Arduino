#include <ESP8266WiFi.h>

const char* ssid = "heonseong";
const char* password = "popopopo";
//http://
//172.20.10.5

WiFiClient client;
IPAddress serverIP(172, 20, 10, 5); // 서버의 IP 주소
const int serverPort = 80; // 서버의 포트 번호

String receivedData = ""; // 입력된 데이터를 저장할 변수

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // 시리얼 입력 처리
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') { // 줄바꿈 문자가 입력되면
      sendDataToServer(); // 서버에 데이터 전송
    } else {
      receivedData += c; // 문자열 버퍼에 문자 추가
    }
  }
}

void sendDataToServer() {
  Serial.print("Data received: ");
  Serial.println(receivedData);

  if (!client.connected()) { // 클라이언트가 연결되어 있지 않으면
    if (client.connect(serverIP, serverPort)) { // 서버에 연결 시도
      client.println(receivedData); // 데이터를 서버로 전송
      Serial.println("Data sent to server");
    } else {
      Serial.println("Failed to connect to server");
    }
  }

  receivedData = ""; // 입력된 데이터 초기화
}
