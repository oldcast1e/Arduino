#include <ESP8266WiFi.h>

//wifi 연결코드
//그리고 추가사항으로 인터넷 연결 끊어지면 다시연결

//wifi
const char* ssid = "oldcast1e"; //wifi 이름 수정해주세요
const char* password = "dlgjstjd"; //비밀번호 수정해주세요


void setup() {

  Serial.begin(115200); //전송속도

  Wifi_connect(); //와이파이 연결
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status() != WL_CONNECTED){ //연결이 이상할시에
    Serial.println("try reconnect");
    Wifi_connect();
  }

    delay(5000);
}

void Wifi_connect() {
  
  Serial.println("---------------------------------------");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // WIFI연결 시작
  while (WiFi.status() != WL_CONNECTED) {
    // 네트워크의 연결 상태, 8개의 리턴값
    // STATUS와 WL_CONNECTED 값이 같은지를 통해 제대로 연결이 되있는지를 확인할 수 있다
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wifi connected!");
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());
}
