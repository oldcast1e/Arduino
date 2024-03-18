#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "KT_GIGA_2G_5B10";
const char* passwd = "bbba3hb643";

const int HTTP_PORT = 80;
ESP8266WebServer webServer(HTTP_PORT);

uint8_t ledESP12 = D0; //16도 가능
uint8_t ledNodeMCU = D4; //2도 가능

const int LED_ON = LOW;
const int LED_OFF = HIGH;
bool ledESP12_ON = false;
bool ledNodeMCU_ON = false;

void setup() {
  Serial.begin(115200);
  pinMode(ledESP12, OUTPUT);
  pinMode(ledNodeMCU, OUTPUT);

  // 공유기에 연결하기
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);

  Serial.print("\nConnecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.print("connected!, address=");
  Serial.println(WiFi.localIP());

  // HTTP 요청 처리함수 등록하기
  webServer.on("/", handle_OnConnect);
  webServer.on("/led1on", handle_led1on);
  webServer.on("/led1off", handle_led1off);
  webServer.on("/led2on", handle_led2on);
  webServer.on("/led2off", handle_led2off);
  webServer.onNotFound(handle_NotFound);

  webServer.begin(); // 웹서버 시작하기

  Serial.print("HTTP server ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.printf("' to connect\n");
}

void loop() {
  webServer.handleClient();

  if (ledESP12_ON)
    digitalWrite(ledESP12, LED_ON);
  else
    digitalWrite(ledESP12, LED_OFF);

  if (ledNodeMCU_ON)
    digitalWrite(ledNodeMCU, LED_ON);
  else
    digitalWrite(ledNodeMCU, LED_OFF);
}

void handle_OnConnect() {
  if (ledESP12_ON) Serial.print("GPIO16 Status: ON | ");
  else Serial.print("GPIO16 Status: OFF | ");

  if (ledNodeMCU_ON) Serial.print("GPIO2 Status: ON");
  else Serial.print("GPIO2 Status: OFF");

  Serial.println();

  String html = SendHTML(ledESP12_ON, ledNodeMCU_ON);
  webServer.send(200, "text/html", html);
}

void handle_led1on() {
  ledESP12_ON = true;
  Serial.println("GPIO16 Status: ON");

  String html = SendHTML(ledESP12_ON, ledNodeMCU_ON);
  webServer.send(200, "text/html", html);
}

void handle_led1off() {
  ledESP12_ON = false;
  Serial.println("GPIO16 Status: OFF");

  String html = SendHTML(ledESP12_ON, ledNodeMCU_ON);
  webServer.send(200, "text/html", html);
}

void handle_led2on() {
  ledNodeMCU_ON = true;
  Serial.println("GPIO2 Status: ON");

  String html = SendHTML(ledESP12_ON, ledNodeMCU_ON);
  webServer.send(200, "text/html", html);
}

void handle_led2off() {
  ledNodeMCU_ON = false;
  Serial.println("GPIO2 Status: OFF");

  String html = SendHTML(ledESP12_ON, ledNodeMCU_ON);
  webServer.send(200, "text/html", html);
}

void handle_NotFound() {
  webServer.send(404, "text/plain", "Not found");
}

String SendHTML(bool led1_on, uint8_t led2_on) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" ";
  ptr += "content=\"width=device-width, ";
  ptr += "initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; ";
  ptr += "display: inline-block; margin: 0px auto; ";
  ptr += "text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;";
  ptr += "margin: 50px auto 30px;} h3 {color: #444444;";
  ptr += "margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;";
  ptr += "background-color: #1abc9c;border: none;";
  ptr += "color: white;padding: 13px 30px;";
  ptr += "text-decoration: none;font-size: 25px;";
  ptr += "margin: 0px auto 35px;cursor: pointer;";
  ptr += "border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #1abc9c;}\n";
  ptr += ".button-on:active {background-color: #16a085;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>NodeMCU Web Server</h1>\n";

  if (led1_on) {
    ptr += "<p>LED1 Status: ON</p>";
    ptr += "<a class=\"button button-off\" ";
    ptr += "href=\"/led1off\">OFF</a>\n";
  } else {
    ptr += "<p>LED1 Status: OFF</p>";
    ptr += "<a class=\"button button-on\" ";
    ptr += "href=\"/led1on\">ON</a>\n";
  }

  if (led2_on) {
    ptr += "<p>LED2 Status: ON</p>";
    ptr += "<a class=\"button button-off\" ";
    ptr += "href=\"/led2off\">OFF</a>\n";
  } else {
    ptr += "<p>LED2 Status: OFF</p>";
    ptr += "<a class=\"button button-on\" ";
    ptr += "href=\"/led2on\">ON</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";

  return ptr;
}
