#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

const char* ssid = "iptime";
//const char* passwd = "21011898";

const int HTTP_PORT = 80;
ESP8266WebServer webServer(HTTP_PORT);

uint8_t ledesp = D0;
uint8_t ledmcu = D4;

int LED_ON = LOW;
int LED_OFF = HIGH;

bool ledespC = false;
bool ledmcuC = false;

void setup(){

  Serial.begin(9600);
  pinMode(ledesp,OUTPUT);
  pinMode(ledmcu,OUTPUT);

  WiFi.mode(WIFI_STA);
//  WiFi.begin1(ssid,passwd);
  WiFi.begin(ssid);

  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(500);
  }

  Serial.println();
  Serial.print("connected!, adress=");
  Serial.println(WiFi.localIP());

  webServer.on("/",handle_OnConnect);
  webServer.on("/led1on",handle_led1on);
  webServer.on("/led1off",handle_led1off);
  webServer.on("/led2on",handle_led2on);
  webServer.on("/led2off",handle_led2off);
  webServer.onNotFound(handle_NotFound);

  webServer.begin();

  Serial.print("HTTP server ready! Use 'https://");
  Serial.print(WiFi.localIP());
  Serial.println(" ' to connect\n");
}

void loop(){

  webServer.handleClient();

  if(ledespC)
    digitalWrite(ledesp,LED_ON);
  else
    digitalWrite(ledesp,LED_OFF);

  if(ledmcuC)
    digitalWrite(ledmcu,LED_ON);
  else
    digitalWrite(ledmcu,LED_OFF);
}

void handle_OnConnect(){

  if(ledespC) Serial.print("GPIO16 Status: ON | ");
  else Serial.print("GPIO16 Status: OFF | ");

  if(ledmcuC) Serial.print("GPIO2 Status: ON | ");
  else Serial.print("GPIO2 Status: OFF | ");

  Serial.println();

  String html = SendHTML(ledespC,ledmcuC);
  webServer.send(200,"text/html",html);
}

void handle_led1on(){
  ledespC = true;
  Serial.println("GPIO16 Status: ON");

  String html = SendHTML(ledespC,ledmcuC);
  webServer.send(200,"text/html",html);
}

void handle_led1off(){
  ledespC = false;
  Serial.println("GPIO16 Status: ON");

  String html = SendHTML(ledespC,ledmcuC);
  webServer.send(200,"text/html",html);
}
void handle_led2on(){
  ledespC = true;
  Serial.println("GPIO2 Status: ON");

  String html = SendHTML(ledespC,ledmcuC);
  webServer.send(200,"text/html",html);
}

void handle_led2off(){
  ledespC = false;
  Serial.println("GPIO2 Status: ON");

  String html = SendHTML(ledespC,ledmcuC);
  webServer.send(200,"text/html",html);

}
void handle_NotFound(){
  webServer.send(404,"text/plain","Not found");
}

String SendHTML(bool led1_on, uint8_t led2_on){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" ";
  ptr +="content=\"width=device-width, ";
  ptr +="initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; ";
  ptr +="display: inline-block; margin: 0px auto; ";
  ptr +="text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;";
  ptr +="margin: 50px auto 30px;} h3 {color: #444444;";
  ptr +="margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;";
  ptr +="background-color: #1abc9c;border: none;";
  ptr +="color: white;padding: 13px 30px;";
  ptr +="text-decoration: none;font-size: 25px;";
  ptr +="margin: 0px auto 35px;cursor: pointer;";
  ptr +="border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>NodeMCU Web Server</h1>\n";
  
  if(led1_on) {
  ptr +="<p>LED1 Status: ON</p>";
  ptr +="<a class=\"button button-off\" ";
  ptr +="href=\"/led1off\">OFF</a>\n";
  } else {
  ptr +="<p>LED1 Status: OFF</p>";
  ptr +="<a class=\"button button-on\" ";
  ptr +="href=\"/led1on\">ON</a>\n";
  }

  if(led2_on) {
  ptr +="<p>LED2 Status: ON</p>";
  ptr +="<a class=\"button button-off\" ";
  ptr +="href=\"/led2off\">OFF</a>\n";
  } else {
  ptr +="<p>LED2 Status: OFF</p>";
  ptr +="<a class=\"button button-on\" ";
  ptr +="href=\"/led2on\">ON</a>\n";
  }

  ptr +="</body>\n";
  ptr +="</html>\n";
  
  return ptr;
}






  
