#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "yeokyoung";
const char* password = "dobudobu";

const char* apiEndpoint = "http://api.gbis.go.kr";
const char* apiKey = "reLDcB4o3fLJ6nMp3f0BDtErKR23ShF4BScYgMco2cOAHGniys0ZEBNeYKEs9g98uLD8leyOZOC8juTCYgcMDA%3D%3D";

const char* sejongUniStopId = "05251";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  connectToWiFi();
}

void loop() {
  displaySejongUniBusInfo(); // 세종대학교 버스 도착 정보 표시
  delay(60000); // 1분마다 업데이트
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

String sendGetRequest(String url) {
  HTTPClient http;
  http.begin(client, url);
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

String getSejongUniBusInfo() {
  String url = String(apiEndpoint) + "/bus/arrivals?stopId=" + String(sejongUniStopId) + "&serviceKey=" + String(apiKey);
  return sendGetRequest(url);
}

void displaySejongUniBusInfo() {
  String sejongUniInfo = getSejongUniBusInfo();
  Serial.println("세종대학교 버스 도착 정보:");
  Serial.println(sejongUniInfo);
}
