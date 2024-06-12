#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

// 와이파이 네트워크 정보
const char* ssid = "yeokyoung";
const char* password = "dobudobu";

// 서울 버스 정보 API 엔드포인트 및 API 키
const char* apiEndpoint = "http://ws.bus.go.kr/api/rest/stationinfo/";
// const char* apiKey = "YOUR_API_KEY";  // 여기에 서울 버스 도착 정보 API의 API 키를 입력하세요
const char* apiKey = "reLDcB4o3fLJ6nMp3f0BDtErKR23ShF4BScYgMco2cOAHGniys0ZEBNeYKEs9g98uLD8leyOZOC8juTCYgcMDA%3D%3D";  // 여기에 서울 버스 도착 정보 API의 API 키를 입력하세요

// 정류소명
const char* stationName = "어린이대공원앞.세종대학교";

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

// 정류소 정보를 가져오는 함수
String getStationInfo() {
  String url = String(apiEndpoint) + "getStationByName?serviceKey=" + String(apiKey) + "&stSrch=" + String(stationName);
  return sendGetRequest(url);
}

// 버스 도착 정보를 가져오는 함수
String getBusInfo(String arsId) {
  String url = String(apiEndpoint) + "getStationByUidItem?serviceKey=" + String(apiKey) + "&arsId=" + arsId;
  return sendGetRequest(url);
}

// OLED 디스플레이에 버스 도착 정보를 출력하는 함수
void displayBusInfo() {
  String stationInfoResponse = getStationInfo();  // 정류소 정보 가져오기
  String arsId = "";  // ARS ID
  // ARS ID 추출
  if (stationInfoResponse.length() > 0) {
    int index = stationInfoResponse.indexOf("<arsId>") + 7;
    arsId = stationInfoResponse.substring(index, stationInfoResponse.indexOf("</arsId>", index));
  }
  String busInfo = getBusInfo(arsId);  // 버스 도착 정보 가져오기
  Serial.println("어린이대공원앞.세종대학교:");
  Serial.println(busInfo);
}
