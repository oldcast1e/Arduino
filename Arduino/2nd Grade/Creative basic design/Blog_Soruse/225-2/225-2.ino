/*
 예제 225-2 직전예제에 유저가 시리얼모니터에 입력한 지역번호와 정류소ID를 기반으로 정보를 출력해보시오!
 시리얼모니터로 전송하는 데이터의 포맷예시
 &cityCode=23&nodeId=ICB166000378
 &cityCode=지역코드&nodeId=정류소ID
 
 */
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "heonseong" //와이파이 검색했을때 뜨는 이름
#define STAPSK  "popopopo" //패스워드
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "openapi.tago.go.kr";
const int httpsPort = 80;

String yourkey = "nyVvF841UBPdCn%2BvugXzKE1EEwkhTBIhjhaXOQgC%2FAlD2F0YongS3tfgXgIxbW5lmlkuJ6Szjamn18IPVNMpXA%3D%3D";
String cityCode="23";
String nodeId="ICB166000378";

WiFiClient client;
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  
  Serial.print("connecting to ");
  Serial.println(host);

  
}

void loop() {
  if(Serial.available()){
    //유저가 시리얼통신으로 뭔가 날린값이 존재한다면~
    String userdata = Serial.readStringUntil(0x0d); //CR
    get_bus(userdata);
  }
}

void get_bus(String query){
  //클라이언트와 서버와 커넥트
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/openapi/service/ArvlInfoInqireService/getSttnAcctoArvlPrearngeInfoList?serviceKey="+yourkey + query;

  //사물인터넷보드에서 RSS서버로 보내는 요청!
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  //서버로부터 응답이 있을때까지 대기하겠다..
  //언제까지 기다려야하나요..?
  //timeout!
  unsigned long t = millis(); //생존시간
  while(1){
    if(client.available()) break;
    if(millis() - t > 10000) break;
  }

  //<arrprevstationcnt>4</arrprevstationcnt> :남은정류장수
  //<arrtime>401</arrtime> :예상시간
  //<nodenm>미산초등학교</nodenm> :정류소이름
  //<routeno>2</routeno> :버스번호
  //<routetp>간선버스</routetp> 
  //<vehicletp>일반차량</vehicletp>

  String xml_tag_s[] = {"<arrprevstationcnt>","<arrtime>","<nodenm>","<routeno>","<routetp>","<vehicletp>"};
  String xml_tag_e[] = {"</arrprevstationcnt>","</arrtime>","</nodenm>","</routeno>","</routetp>","</vehicletp>"};
  String xml_name[] = {"남은정류장수","예상시간","정류소이름","노선번호","노선유형","차량유형"};
  //응답이 날라오는 부분!
  Serial.println("request sent");

  while(client.available()){
    String data = client.readStringUntil('\n'); //readline();
    if(data.indexOf("<?xml") == -1) continue;
    //파싱을 해보자~

    //반환된 버스의 갯수가 몇대인지를 일단 알아야겠다
    //<totalCount>6</totalCount>
    int bus_count = data.substring(data.indexOf("<totalCount>")+12,data.indexOf("</totalCount>")).toInt();
    Serial.print("bus_count=");
    Serial.println(bus_count);
    

    int s = 0;
    int e = 0;
    for(int j = 0;j<bus_count;j++){
      for(int i = 0;i<6;i++){
        s = data.indexOf(xml_tag_s[i],s);
        e = data.indexOf(xml_tag_e[i],s);
        String filed = data.substring(s+xml_tag_s[i].length(),e);
        Serial.println(xml_name[i] + ":" + filed);

        s = e + xml_tag_e[i].length();
      }
      Serial.println("-----------------");
    }
    
  }
  Serial.println("DONE");
}
