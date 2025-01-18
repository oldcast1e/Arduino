#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD 초기화 (주소: 0x27, 16×2 디스플레이)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 사용자 환경에 맞게 수정
const char* WIFI_SSID = "oldcast1e";      // 핫스팟 SSID
const char* WIFI_PASS = "popopopo";       // 핫스팟 비밀번호
const char* SERVER_IP = "118.235.92.209"; // 서버 IP
int SERVER_PORT = 12345;                  // 서버 포트

void setup() {
  // 하드웨어 시리얼 초기화
  Serial.begin(115200);
  
  // LCD 초기화
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ESP-01 INIT...");
  delay(1500);

  // AT 명령어 테스트
  sendAT("AT", 2000, "AT Test");

  // Wi-Fi 연결
  String cmd = "AT+CWJAP=\"";
  cmd += WIFI_SSID;
  cmd += "\",\"";
  cmd += WIFI_PASS;
  cmd += "\"";
  sendAT(cmd, 8000, "WiFi Connect");

  // Wi-Fi 연결 상태 디버깅 메시지
  if (checkResponse("WIFI CONNECTED")) {
    lcd.clear();
    lcd.print("WiFi: Connected");
  } else {
    lcd.clear();
    lcd.print("WiFi: Failed");
    while (true);  // 연결 실패 시 멈춤
  }
  delay(2000);

  // 단일 연결 모드 설정
  sendAT("AT+CIPMUX=0", 2000, "CIPMUX=0");

  // TCP 서버 연결
  cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += SERVER_IP;
  cmd += "\",";
  cmd += SERVER_PORT;
  sendAT(cmd, 5000, "CIPSTART");

  // 서버 연결 상태 디버깅 메시지
  if (checkResponse("CONNECT")) {
    lcd.clear();
    lcd.print("Server: Connected");
  } 
  else {
    lcd.clear();
    lcd.print("Server: Failed");
    while (true);  // 연결 실패 시 멈춤
  }
  delay(2000);

  // "hello" 데이터 전송
  String data = "hello";
  cmd = "AT+CIPSEND=";
  cmd += data.length();
  sendAT(cmd, 2000, "CIPSEND");
  
  // 데이터 전송 메시지
  lcd.clear();
  lcd.print("Sending data...");
  Serial.print(data);  // ESP-01로 데이터 전송
  delay(2000);

  // 서버 응답 확인
  readPartialResponse(2000, "Got Resp?");
  
  // 소켓 종료
  sendAT("AT+CIPCLOSE", 2000, "Close Sock");
  
  // 완료 메시지
  lcd.clear();
  lcd.print("Done! Check");
  lcd.setCursor(0, 1);
  lcd.print("Server side");
}

void loop() {
  // 반복 작업 없음
}

/***********************************************************
 * 함수: sendAT
 * - AT 명령을 ESP-01에 전송
 * - 응답을 대기하며 LCD에 진행 상태 표시
 ***********************************************************/
void sendAT(String cmd, unsigned long waitTime, const char* info) {
  lcd.clear();
  lcd.print(info);
  lcd.setCursor(0, 1);
  lcd.print("Sending..");
  
  while (Serial.available()) {
    Serial.read();  // 잔여 버퍼 비우기
  }
  Serial.println(cmd);

  unsigned long start = millis();
  while (millis() - start < waitTime) {
    if (Serial.available()) {
      Serial.read();  // 데이터 읽기 (필요 시 저장 가능)
    }
  }

  lcd.clear();
  lcd.print(info);
  lcd.setCursor(0, 1);
  lcd.print("OK or Timeout");
  delay(1000);
}

/***********************************************************
 * 함수: checkResponse
 * - 특정 문자열이 시리얼 응답에 포함되는지 확인
 ***********************************************************/
bool checkResponse(const char* expected) {
  unsigned long start = millis();
  String response = "";

  while (millis() - start < 5000) {  // 5초 대기
    if (Serial.available()) {
      char c = Serial.read();
      response += c;
    }
  }

  // 응답에 기대 문자열 포함 여부 확인
  return response.indexOf(expected) != -1;
}

/***********************************************************
 * 함수: readPartialResponse
 * - 서버 응답 일부를 LCD에 표시
 ***********************************************************/
void readPartialResponse(unsigned long waitTime, const char* title) {
  lcd.clear();
  lcd.print(title);
  lcd.setCursor(0, 1);

  unsigned long start = millis();
  char buffer[17];  // 최대 16자 + null
  byte idx = 0;

  while (millis() - start < waitTime) {
    if (Serial.available()) {
      char c = Serial.read();
      if (idx < 16) {
        buffer[idx++] = c;
      }
    }
  }
  buffer[idx] = '\0';  // 문자열 종료

  lcd.print(buffer);  // LCD에 표시
  delay(1500);
}
