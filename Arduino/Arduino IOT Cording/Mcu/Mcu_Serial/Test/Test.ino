#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

char *ssid = "heonseong"; // wifi 이름
char *password = "F=k*q1q2/r^2"; // 해당 wifi 패스워드

ESP8266WebServer server(80);

void handleRoot(){
  server.send(200, "text/plain", "Hello from esp8266!");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.print("Connecting to \'");
  Serial.print(ssid);
  Serial.println("\'");

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("Server IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
