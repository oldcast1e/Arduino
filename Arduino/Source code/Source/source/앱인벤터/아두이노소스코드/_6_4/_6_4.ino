#include "WiFiEsp.h"
#include "SoftwareSerial.h"

SoftwareSerial Serial1(6, 7);

char ssid[] = "jang";            // your network SSID (name)
char pass[] = "melab12345";        // your network password
int status = WL_IDLE_STATUS;

int ledStatusR = 0;
int ledStatusG = 0;
int ledStatusB = 0;
int cdsPin = A0;

int ledB = 2;
int ledG = 3;
int ledR = 4;
int echo = 8;
int trig = 9;

WiFiEspServer server(80);

RingBuffer buf(20);

void setup()
{
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  Serial.begin(115200); 
  Serial1.begin(9600);    
  WiFi.init(&Serial1);   

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();

  server.begin();
}


void loop()
{
  WiFiEspClient client = server.available(); 

  if (client) {                      
    Serial.println("New client");             
    buf.init();                       
    while (client.connected()) {            
      if (client.available() > 0) {        
        char c = client.read();              
        buf.push(c);                       

        if (buf.endsWith("GET /LEDR ")) {
          Serial.println("LEDR");
          ledStatusR = 1;
          digitalWrite(ledR,HIGH);
        }
        else if (buf.endsWith("GET /LEDG ")) {
          Serial.println("LEDG");
          ledStatusG = 1;
          digitalWrite(ledG,HIGH);
        }
        else if (buf.endsWith("GET /LEDB ")) {
          Serial.println("LEDB");
          ledStatusB = 1;
          digitalWrite(ledB,HIGH);
        }
        else if (buf.endsWith("GET /LEDOFF ")) {
          Serial.println("LEDOFF");
          ledStatusR = 0;
          ledStatusG = 0;
          ledStatusB = 0;
          digitalWrite(ledR,LOW);
          digitalWrite(ledG,LOW);
          digitalWrite(ledB,LOW);
        }
      }
      else
      {
        sendHttpResponse(client);
        break;
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

void sendHttpResponse(WiFiEspClient client)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  client.print("<!DOCTYPE HTML>\r\n");
  client.print("<html>\r\n");
  client.print("<h1>SmartHome</h1>\r\n");

  client.print("---------sensor----------");
  client.print("<br>\r\n");

  client.print("CDS Value: ");
  client.print(analogRead(cdsPin));
  client.print("<br>\r\n");

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);

  float distanceCM = ((34000 * duration) / 1000000) / 2;

  client.print("ULTRASONIC Value: ");
  client.print(distanceCM);
  client.print("<br>\r\n");

  client.print("--------------------------");
  client.print("<br>\r\n");

  client.print("---------status----------");
  client.print("<br>\r\n");

  client.print("LED R: ");
  if (ledStatusR == 1) client.print("ON");
  else client.print("OFF");
  client.print("<br>\r\n");

  client.print("LED G: ");
  if (ledStatusG == 1) client.print("ON");
  else client.print("OFF");
  client.print("<br>\r\n");

  client.print("LED B: ");
  if (ledStatusB == 1) client.print("ON");
  else client.print("OFF");
  client.print("<br>\r\n");

  client.print("--------------------------");
  client.print("<br>\r\n");
}
