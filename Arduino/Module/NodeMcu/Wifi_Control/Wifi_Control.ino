#include <ESP8266WiFi.h>
 
#define PIN_LED D1
 
const char* ssid = "U+Net5158";
const char* password = "1J1B95D@DC";
 
WiFiServer server(80);
 
void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
  Serial.println("Server started");
}
 
void loop() {
  WiFiClient client = server.available();
  if(!client) return;
  
  Serial.println("새로운 클라이언트");
  client.setTimeout(5000);
  
  String request = client.readStringUntil('\r');
  Serial.println("request: ");
  Serial.println(request);
 
  if(request.indexOf("/ledoff") != -1) {
    digitalWrite(PIN_LED, LOW);
  }
  else if(request.indexOf("/ledon") != -1) {
    digitalWrite(PIN_LED, HIGH);
  }
  else {
    Serial.println("invalid request");
    digitalWrite(PIN_LED, digitalRead(PIN_LED));
  }
 
  while(client.available()) {
    client.read();
  }
 
  client.print("HTTP/1.1 200 OK");
  client.print("Content-Type: text/html\r\n\r\n");
  client.print("<!DOCTYPE HTML>");
  client.print("<html>");
  client.print("<head>"); 
  client.print("<meta&nbsp;charset=\"UTF-8\">");
  client.print("<title>LED CONTROL</title>");
  client.print("</head>");
  client.print("<body>");
  client.print("<h2>HANIUM LED Control Page</h2>");
  client.print("<a href='/ledon'>LED ON</a>");
  client.print("<br>");
  client.print("<a href='/ledoff'>LED OFF</a>");
  client.print("<br>");
  client.print("LED Status : ");
  client.print((digitalRead(PIN_LED)) ? "ON" : "OFF");
  client.print("</body>");
  client.print("</html>");
 
  Serial.println("클라이언트 연결 해제");
}