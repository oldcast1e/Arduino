/*
 예제 225-3 직전예제에 LCD모듈(ILI9341)과 SD카드모듈을 연결해서
 버스도착정보에 관련된 정보를 LCD화면에 한글로 출력해보자!
 시리얼모니터에서 전송하는 데이터 샘플 2개..
 &cityCode=23&nodeId=ICB165000773
 &cityCode=23&nodeId=ICB166000378
 
 */
#include <ESP8266WiFi.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <SPI.h>
#include <SD.h>

// For the Adafruit shield, these are the default.
#define TFT_DC D9
#define TFT_CS D10

#define FONT16 32
#define FONT24 72
#define FONT36 128
#define FONT40 200

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
File myFile;


#ifndef STASSID
#define STASSID "~~~~~" //와이파이 검색했을때 뜨는 이름
#define STAPSK  "~~~~~" //패스워드
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "openapi.tago.go.kr";
const int httpsPort = 80;

String yourkey = "~~~~~~~";
String cityCode="23";
String nodeId="ICB166000378";

WiFiClient client;
void setup() {
  Serial.begin(115200);
  tft.begin();
  Serial.print(F("Initializing SD card..."));

  if (!SD.begin(D4)) {
    Serial.println(F("initialization failed!"));
    while (1);
  }
  Serial.println(F("initialization done."));
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  
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
    tft.fillScreen(ILI9341_BLACK);
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
  //String xml_name[] = {"남은정류장수","예상시간","정류소이름","노선번호","노선유형","차량유형"};
  String xml_data[6]; //버퍼
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
    

    hangul2utf8(0,0,F("국토교통부 버스실시간 도착정보API"),ILI9341_GREEN,16);
    
    int s = 0;
    int e = 0;
    int line_pos = 61;
    for(int j = 0;j<bus_count;j++){
      for(int i = 0;i<6;i++){
        s = data.indexOf(xml_tag_s[i],s);
        e = data.indexOf(xml_tag_e[i],s);
        String filed = data.substring(s+xml_tag_s[i].length(),e);
        //Serial.println(xml_name[i] + ":" + filed);
        xml_data[i] = filed;
       

        s = e + xml_tag_e[i].length();
      }

      //데이터를 정리를 좀 해보자..
      //"남은정류장수","예상시간","정류소이름","노선번호","노선유형","차량유형"
      //0                1         2         3         4          5
      //노선번호 남은정류장수 예상시간 노선유형 차량유형
      //   3        0         1      4        5
      if(j == 0){
        //제일 첫번째 레코드일때만 정류소이름을 프린트하겠다!
        Serial.println("정류소이름="+xml_data[2]);
        hangul2utf8(0,16,"정류소이름="+xml_data[2],ILI9341_YELLOW,16);
        //전체 버스 댓수
        hangul2utf8(0,32,"버스댓수="+String(bus_count),ILI9341_YELLOW,16);
        //컬럼헤더도 여기서 출력해보자!
        hangul2utf8(0,45,"번호",ILI9341_GREEN,16);
        hangul2utf8(60,45,"정류장",ILI9341_GREEN,16);
        hangul2utf8(110,45,"시간",ILI9341_GREEN,16);
        hangul2utf8(160,45,"노선유형",ILI9341_GREEN,16);
        hangul2utf8(240,45,"차량유형",ILI9341_GREEN,16);
      }
      //0,32
      //노선번호(60) 남은정류장수50 예상시간50, 노선유형 80 차량유형 80
      int x_pos = 0;
      Serial.println("노선번호="+xml_data[3]);
      hangul2utf8(x_pos,line_pos,xml_data[3],ILI9341_YELLOW,16);
      x_pos += 60;
      Serial.println("남은정류장수="+xml_data[0]);
      hangul2utf8(x_pos,line_pos,xml_data[0],ILI9341_WHITE,16);
      x_pos += 50;
      Serial.println("예상시간="+xml_data[1]);
      hangul2utf8(x_pos,line_pos,xml_data[1],ILI9341_WHITE,16);
      x_pos += 50;
      Serial.println("노선유형="+xml_data[4]);
      hangul2utf8(x_pos,line_pos,xml_data[4],ILI9341_WHITE,16);
      x_pos += 80;
      Serial.println("차량유형="+xml_data[5]);
      hangul2utf8(x_pos,line_pos,xml_data[5],ILI9341_WHITE,16);
      Serial.println("-----------------");
      line_pos+=16;
    }
    
  }
  Serial.println("DONE");
}


void draw_hangul(int x,int y, String utf8code,uint16_t color,int font_size){
  
  int font_array_count = 0;
  String direct;

  if(font_size == 16) {font_array_count=2;direct=F("nock16/");}
  else if(font_size == 24) {font_array_count=3;direct=F("nock24/");}
  else if(font_size == 32) {font_array_count=4;direct=F("nock32/");}
  else if(font_size == 40) {font_array_count=5;direct=F("nock40/");}

  //파일불러오기
  myFile = SD.open(direct+utf8code+F(".txt"));
  String output;
  if (myFile) {
    while (myFile.available()) {
      output += String((char)myFile.read());
    }
    //Serial.println(output);
    myFile.close();
  } else {
    Serial.println("NO FILE");
    return;
  }

  if(x+font_size > tft.width()){
    x=0;
    y+=font_size;
  }
  int count = 1;
  //4개가 1line
  for(int i =0;i<output.length();i+=2){
    //Serial.println();
    //Serial.println(i);
    byte value = shex2hex(output[i], output[i+1]);

    for(int j =0;j<8;j++){
        byte temp = (128>>j);
        if((value & temp) == temp){
          //해당 bit가 1인것!
              tft.drawPixel(x,y,color);
              //Serial.print("1");
          }else{
              //Serial.print("0");
          }
          x++;
    }

   if(count % font_array_count ==0){
    //한라인구분
    //Serial.println();
    if(i == output.length()-2){
      y++;
      y-=font_size;
      
    }else{
      y++;
      x-=font_size;
    }
    //Serial.print("(");
    //Serial.print(i);
    //Serial.print(",");
    //Serial.print(x);
    //Serial.print(",");
    //Serial.print(y);
    //Serial.println(")");
   }
    count++;
  }//for
  tft.setCursor(x, y);
}

void draw_hangul2(int x,int y, byte hexcode[],uint16_t color,int font_size){
  int font_array_count;
  int loop_size = font_size*font_size/8;
  if(font_size == 16) {font_array_count=2;}
  else if(font_size == 24) {font_array_count=3;}
  else if(font_size == 32) {font_array_count=4;}
  else if(font_size == 40) {font_array_count=5;}
  int count = 1;
  //4개가 1line
  for(int i =0;i<loop_size;i++){
    //Serial.println();
    //Serial.println(i);
    byte value = hexcode[i];

    for(int j =0;j<8;j++){
        byte temp = (128>>j);
        if((value & temp) == temp){
          //해당 bit가 1인것!
              tft.drawPixel(x,y,color);
              //Serial.print("1");
          }else{
              //Serial.print("0");
          }
          x++;
    }

   if(count % font_array_count ==0){
    //한라인구분
    //Serial.println();
    if(i == loop_size-2){
      y++;
      y-=font_size;
      
    }else{
      y++;
      x-=font_size;
    }
    //Serial.print("(");
    //Serial.print(i);
    //Serial.print(",");
    //Serial.print(x);
    //Serial.print(",");
    //Serial.print(y);
    //Serial.println(")");
   }
    count++;
  }//for
}

byte shex2hex(char data1, char data2){
//3F
//숫자는 -'0' 하면 숫자로된다
//a~f 는 -'a'+10 하면 숫자로된다
  byte output;

  int a,b;
  if(data1 >= '0' && data1 <= '9'){
   a = data1-'0';
  }else if(data1 >= 'a' && data1 <= 'f'){
   a = data1-'a'+10;
  }else if(data1 >= 'A' && data1 <= 'F'){
   a = data1-'A'+10; 
  }
  if(data2 >= '0' && data2 <= '9'){
   b = data2-'0';
  }else if(data2 >= 'a' && data2 <= 'f'){
   b = data2-'a'+10;
  }else if(data2 >= 'A' && data2 <= 'F'){
   b = data2-'A'+10; 
  }

  return a*16+b;

}

void hangul2utf8(int x,int y, String text,uint16_t color,int fontsize){
  tft.setTextColor(color); 
  if(fontsize == 16) tft.setTextSize(2);
  if(fontsize == 24) tft.setTextSize(3);
  
  tft.setCursor(x, y);
  for(int i = 0;i<text.length();){
    if(text[i] >128){
      //한글
      //Serial.println("한글");
      String output = String(text[i]&0xFF,HEX);
      output += String(text[i+1]&0xFF,HEX);
      output += String(text[i+2]&0xFF,HEX);
      i+=3;
      //Serial.println(output);
      //이전 커서값을 가져와야한다..
      
      draw_hangul(tft.getCursorX(),tft.getCursorY(),output,color,fontsize);

    }else{
      //ascii
      //Serial.println("아스키");
      //Serial.println(text[i]);
       tft.print(text[i]);
      i++;
    }

  }
}

void set_hangul(String hangul,int font_size,byte data[]){
  String output;
  if(hangul[0] >128){
    //한글
    //Serial.println("한글");
    output = String(hangul[0]&0xFF,HEX);
    output += String(hangul[1]&0xFF,HEX);
    output += String(hangul[2]&0xFF,HEX);
  }else{
    //한글이 아닙니다~!
    return;
  }
  String direct;
  if(font_size == 16) {direct=F("nock16/");}
  else if(font_size == 24) {direct=F("nock24/");}
  else if(font_size == 32) {direct=F("nock32/");}
  else if(font_size == 40) {direct=F("nock40/");}
  //Serial.println(hangul);
  //Serial.println(direct+output+".txt");
  myFile = SD.open(direct+output+F(".txt"));

  int count = 0;
  char temp[2];
  if (myFile) {
    while (myFile.available()) {
      //data += String((char)myFile.read());
      myFile.readBytes(temp,2);
      data[count] = shex2hex(temp[0],temp[1]);
      count++;
    }
    //Serial.println(output);
    myFile.close();
  } else {
    Serial.println("NO FILE");
    return;
  }

}
