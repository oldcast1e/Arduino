#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "U+Net5158";
const char* password = "1J1B95D@DC";

const char* host = "ws.bus.go.kr";
const int httpsPort = 443;

const char* apiKey = "nyVvF841UBPdCn%2BvugXzKE1EEwkhTBIhjhaXOQgC%2FAlD2F0YongS3tfgXgIxbW5lmlkuJ6Szjamn18IPVNMpXA%3D%3D";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClientSecure client;

  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  // Send HTTP request
  client.print(String("GET /api/rest/arrive/getArrInfoByRouteAll HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" +
               "Authorization: " + apiKey + "\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println("request sent");

  // Wait for response
  while (!client.available()) {
    delay(100);
  }

  // Read response
  String response = "";
  while (client.available()) {
    char c = client.read();
    response += c;
  }

  Serial.println("response received:");
  Serial.println(response);

  Serial.println("closing connection");
}
