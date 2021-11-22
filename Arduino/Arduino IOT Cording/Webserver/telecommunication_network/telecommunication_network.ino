#include <ESP8266WiFi.h>

const char* ssid = "NEXT";  // Enter SSID here
const char* password = "12345678"; 

const int TELNET_PORT = 23;
const int MAX_SRV_CLIENTS = 2;
WiFiServer telnetServer(TELNET_PORT);
WiFiClient telnetClients[MAX_SRV_CLIENTS];

void setup() {
  Serial.begin(115200);

  // 공유기에 연결하기
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.print("\nConnecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print('.');
  delay(500);
  }
  Serial.println();  
  Serial.print("connected!, address=");
  Serial.println(WiFi.localIP());

  // 텔넷 서버 시작하기
  telnetServer.begin();
  telnetServer.setNoDelay(true);

  Serial.print("Telent server ready! Use 'telnet ");
  Serial.print(WiFi.localIP());
  Serial.printf(" %d' to connect\n", TELNET_PORT);
  
  Serial.flush(); Serial.swap();
}

void loop() {
  
  // 새로운 접속 요청 텔넷 클라이언트 확인하기
  if (telnetServer.hasClient()) {
  int i;
  for (i = 0; i < MAX_SRV_CLIENTS; i++) {
    if(!telnetClients[i]) {
    telnetClients[i] = telnetServer.available();

    Serial.flush(); Serial.swap();        
    Serial.print("\nNew client: index ");
    Serial.println(i);        
    Serial.flush(); Serial.swap();
    
    break;
    }      
  } 

  if(i==MAX_SRV_CLIENTS) {
    telnetServer.available().println("I'm busy");
  }
  }

  // 텔넷 데이터 도착 확인하기
  for(int i = 0; i < MAX_SRV_CLIENTS; i++) {
  if(telnetClients[i].available()>0)
    Serial.write(telnetClients[i].read());
    Serial.flush();
  }

  // 시리얼 데이터 도착 확인하기
  if(Serial.available()>0) {
  uint8_t data = Serial.read();
  for(int i = 0; i < MAX_SRV_CLIENTS; i++) {   
    telnetClients[i].write(data);
    telnetClients[i].flush();
  }
  }
}
