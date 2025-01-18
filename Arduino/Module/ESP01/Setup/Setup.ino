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

  // Wi-Fi 연결 시작
  lcd.clear();
  lcd.print("Connecting WiFi");
  delay(1000);

  // Wi-Fi 연결 명령어
  String cmd = "AT+CWJAP=\"";
  cmd += WIFI_SSID;
  cmd += "\",\"";
  cmd += WIFI_PASS;
  cmd += "\"";
  sendAT(cmd, 10000, "Connecting");

  // Wi-Fi 연결 상태 확인
  if (waitForResponse("WIFI CONNECTED", 10000)) {
    lcd.clear();
    lcd.print("WiFi: Connected");
  } else if (waitForResponse("FAIL", 10000)) {
    lcd.clear();
    lcd.print("WiFi: Failed");
    delay(2000);
    while (true);  // 실패 시 멈춤
  } else {
    lcd.clear();
    lcd.print("WiFi: Timeout");
    delay(2000);
    while (true);  // 타임아웃 시 멈춤
  }

  delay(2000);

  // 단일 연결 모드 설정
  sendAT("AT+CIPMUX=0", 2000, "CIPMUX=0");

  // TCP 서버 연결
  cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += SERVER_IP;
  cmd += "\",";
  cmd += SERVER_PORT;
  sendAT(cmd, 5000, "Connecting Server");

  // 서버 연결 상태 확인
  if (waitForResponse("CONNECT", 5000)) {
    lcd.clear();
    lcd.print("Server: Connected");
  } else {
    lcd.clear();
    lcd.print("Server: Failed");
    while (true);  // 실패 시 멈춤
  }
}

void loop() {
  // 반복 작업 없음
}

/***********************************************************
 * 함수: sendAT
 * - AT 명령을 ESP-01에 전송
 * - 진행 상태를 LCD에 표시
 ***********************************************************/
void sendAT(String cmd, unsigned long waitTime, const char* info) {
  lcd.clear();
  lcd.print(info);
  lcd.setCursor(0, 1);
  lcd.print("Sending..");
  
  // 잔여 데이터 비우기
  while (Serial.available()) {
    Serial.read();
  }
  Serial.println(cmd);

  unsigned long start = millis();
  while (millis() - start < waitTime) {
    if (Serial.available()) {
      Serial.read();  // 데이터를 읽지만 사용하지 않음
    }
  }

  lcd.clear();
  lcd.print(info);
  lcd.setCursor(0, 1);
  lcd.print("Done");
  delay(1000);
}

/***********************************************************
 * 함수: waitForResponse
 * - 특정 문자열이 시리얼 응답에 포함되는지 대기하며 확인
 ***********************************************************/
bool waitForResponse(const char* expected, unsigned long timeout) {
  unsigned long start = millis();
  String response = "";

  while (millis() - start < timeout) {
    if (Serial.available()) {
      char c = Serial.read();
      response += c;

      // 기대하는 응답 문자열 확인
      if (response.indexOf(expected) != -1) {
        return true;
      }
    }
  }
  return false;  // 시간 초과
}
