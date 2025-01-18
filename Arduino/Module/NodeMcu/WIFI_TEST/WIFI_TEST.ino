#include <ESP8266WiFi.h>

// const char* ssid = "heonseong";     // 네트워크 SSID (이름)
// const char* password = "popopopo"; // 네트워크 비밀번호

const char* ssid = "oldcast1e";
const char* password = "dlgjstjd";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Wi-Fi 연결 시작
  Serial.println();
  Serial.println();
  Serial.print("Wi-Fi 연결 시도: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi 연결 성공!");

  // 서버 시작
  server.begin();
  Serial.println("서버 시작");
}

void loop() {
  // 클라이언트 대기
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // 클라이언트가 연결되면 출력
  Serial.println("새로운 클라이언트 연결");
  
  // 클라이언트 요청 읽기
  while(!client.available()){
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // 응답 전송
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // 중요: 응답의 빈 줄
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1>Hello World!</h1>");
  client.println("<p>ESP8266을 사용하여 만든 웹 서버입니다.</p>");
  client.println("</html>");

  delay(1);
  Serial.println("클라이언트 연결 해제");
  Serial.println("");
}
