#include <ESP8266WiFi.h>
#include <string.h>

// 네트워크 SSID (이름)
// const char* ssid = "oldcast1e";
const char* ssid = "heonseong";
// 네트워크 비밀번호
// const char* password = "dlgjstjd";
const char* password = "popopopo";

// Wi-Fi 서버 객체 생성
WiFiServer server(80);

// Wi-Fi 연결 함수
void connectToWiFi() {
  Serial.println();
  Serial.println();
  Serial.print("Wi-Fi 연결 시도: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Wi-Fi 연결 대기
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi 연결 성공!");
}

// 서버 시작 함수
void startServer() {
  // 서버 시작
  server.begin();
  Serial.println("서버 시작");

  // 서버의 IP 주소 출력
  Serial.print("서버 주소: ");
  Serial.println(WiFi.localIP());
}

// 클라이언트 요청 처리 함수
void handleClientRequest() {
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

  // 응답 전송 함수 호출
  sendResponse(client, request);

  Serial.println("클라이언트 연결 해제");
  Serial.println("");
}

// 응답 전송 함수
void sendResponse(WiFiClient client, String request) {
  String str;
  if(Serial.available()){
    // 실행하고 싶은 코드
    str = Serial.readString(); 
    // 이때 저장한 값은 1바이트 (문자)임에 주의한다.
    Serial.println(str);//문자를 출력한다.
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=utf-8"); // UTF-8 문자 인코딩 설정
  client.println("Refresh: 30"); // 5분(300초) 후에 새로고침
  client.println(""); // 중요: 응답의 빈 줄
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta charset=\"UTF-8\">"); // HTML에서도 UTF-8 설정
  client.println("<h1>[ 서울특별시 실시간 버스 정보] </h1>");
  // client.println("<p>ESP8266을 사용하여 만든 웹 서버입니다.</p>");
  client.println("<h3>어린이대공원앞.세종대학교</h3>");
  client.println("<h4>[건대 방향]</h4>");
  
  client.print("<p>"); 
  for(int i=0;i<str.length();i++){
    
    if(str[i] == '!' ){ client.print("<br>");continue;}
    client.print(str[i]);  
  }
  client.print("</p>");
  Serial.print("사용자 입력: ");Serial.println(str);

  client.println("</html>");
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Wi-Fi 연결 함수 호출
  connectToWiFi();

  // 서버 시작 함수 호출
  startServer();
}

void loop() {
  // 클라이언트 요청 처리 함수 호출
  handleClientRequest();
}
