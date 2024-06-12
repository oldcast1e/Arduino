#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

// 와이파이 네트워크 정보
const char* ssid = "yeokyoung";
const char* password = "dobudobu";

// 서울 버스 정보 API 엔드포인트 및 API 키
const char* apiEndpoint = "http://ws.bus.go.kr/api/rest/stationinfo/";
const char* apiKey = "nyVvF841UBPdCn%2BvugXzKE1EEwkhTBIhjhaXOQgC%2FAlD2F0YongS3tfgXgIxbW5lmlkuJ6Szjamn18IPVNMpXA%3D%3D";  // 여기에 서울 버스 도착 정보 API의 API 키를 입력하세요

// 정류소 고유번호
const char* stationId = "05251";

WiFiClient client;  // WiFiClient 객체 생성

void setup() {
  Serial.begin(115200);
  connectToWiFi();  // 와이파이 연결 설정
}

void loop() {
  displayBusInfo();  // 버스 도착 정보 표시
  delay(60000); // 1분마다 업데이트
}

// 와이파이에 연결하는 함수
void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);  // 와이파이 연결 시도
  while (WiFi.status() != WL_CONNECTED) {  // 연결될 때까지 대기
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

// HTTP GET 요청을 보내는 함수
String sendGetRequest(String url) {
  HTTPClient http;
  http.begin(client, url);  // WiFiClient를 사용하여 HTTP 요청 보냄
  int httpResponseCode = http.GET();
  String response = "";
  if (httpResponseCode > 0) {
    response = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return response;
}

// 정류소를 경유하는 노선 목록을 가져오는 함수
String getRouteByStationList() {
  String url = String(apiEndpoint) + "getStationByUid?serviceKey=" + String(apiKey) + "&arsId=" + String(stationId);
  return sendGetRequest(url);
}

// 각 항목을 추출하고 출력하는 함수
void extractAndDisplayInfo(String html) {
  int index = 0;
  while (true) {
    index = html.indexOf("<busRouteNm>", index);
    if (index == -1) break;
    int endTagIndex = html.indexOf("</busRouteNm>", index);
    String busRouteNm = html.substring(index + 12, endTagIndex);
    Serial.println("버스 번호: " + busRouteNm);
    // 각 항목을 출력
    index = endTagIndex;
    index = html.indexOf("<term>", index);
    if (index == -1) break;
    endTagIndex = html.indexOf("</term>", index);
    String term = html.substring(index + 6, endTagIndex);
    Serial.println("배차 간격: " + term);
    index = endTagIndex;
    index = html.indexOf("<stBegin>", index);
    if (index == -1) break;
    endTagIndex = html.indexOf("</stBegin>", index);
    String stBegin = html.substring(index + 9, endTagIndex);
    Serial.println("기점: " + stBegin);
    index = endTagIndex;
    index = html.indexOf("<stEnd>", index);
    if (index == -1) break;
    endTagIndex = html.indexOf("</stEnd>", index);
    String stEnd = html.substring(index + 7, endTagIndex);
    Serial.println("종점: " + stEnd);
    index = endTagIndex;
    index = html.indexOf("<nextBus>", index);
    if (index == -1) break;
    endTagIndex = html.indexOf("</nextBus>", index);
    String nextBus = html.substring(index + 9, endTagIndex);
    Serial.println("다음도착버스 시간: " + nextBus);
    index = endTagIndex;
    Serial.println();
  }
}

// OLED 디스플레이에 노선 목록을 출력하는 함수
void displayBusInfo() {
  String routeList = getRouteByStationList();  // 정류소를 경유하는 노선 목록 가져오기
  Serial.println("노선 목록:");
  Serial.println(routeList);
  
  // 각 항목을 추출하여 출력
  extractAndDisplayInfo(routeList);
}
