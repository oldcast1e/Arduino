#include <Wire.h>
#include <EEPROM.h>

const int ledPin = 13; // LED 핀 설정
unsigned long previousMillis = 0; // 이전 시간 저장
const long interval = 1000; // 1초 간격으로 시간 출력하기

int year, month, day, hour, minute, second, dayOfWeek; // 시간 및 요일 변수 선언
bool timeSet = false; // 시간이 설정되었는지 여부

void setup() {
  Serial.begin(9600); // 시리얼 통신 시작
  pinMode(ledPin, OUTPUT); // LED 핀을 출력으로 설정

  // 초기 시간 설정
  if (!timeSet) {
    if (readTimeFromEEPROM()) { // 외부 EEPROM에서 시간을 읽어옴
      timeSet = true; // 시간 설정됨 표시
    } else {
      setTimeManually(); // 시간 수동 설정
    }
  }
}

void loop() {
  unsigned long currentMillis = millis(); // 현재 시간 가져오기
  
  if (currentMillis - previousMillis >= interval) { // 시간 간격이 지났는지 확인
    previousMillis = currentMillis; // 시간 업데이트
    updateSecond(); // 1초마다 시간 업데이트 함수 호출
    dayOfWeek = getDayOfWeek(year, month, day); // 요일 정보 업데이트
    printTime(); // 시간 출력 함수 호출
    saveTimeToEEPROM(); // 시간과 요일을 EEPROM에 저장
  }
}

bool readTimeFromEEPROM() {
  if (EEPROM.read(0) == 1) { // EEPROM에 시간이 저장되어 있는지 확인
    year = EEPROM.read(1);
    month = EEPROM.read(2);
    day = EEPROM.read(3);
    hour = EEPROM.read(4);
    minute = EEPROM.read(5);
    second = EEPROM.read(6);
    dayOfWeek = EEPROM.read(7); // 요일 정보도 읽어옴
    return true;
  }
  return false;
}

void setTimeManually() {
  Serial.println("Enter the current date and time (YYYY/MM/DD HH:MM:SS):");
  while (!Serial.available()) {} // 사용자 입력이 있을 때까지 대기
  readTime(); // 시간 읽기 함수 호출
  Serial.println("Time set.");
  EEPROM.write(0, 1); // EEPROM에 시간이 설정되었음을 표시
  EEPROM.write(1, year);
  EEPROM.write(2, month);
  EEPROM.write(3, day);
  EEPROM.write(4, hour);
  EEPROM.write(5, minute);
  EEPROM.write(6, second);
  // 요일 정보도 저장
  EEPROM.write(7, getDayOfWeek(year, month, day)); 
  // EEPROM.commit(); // EEPROM에 저장된 값을 영구적으로 저장
}

void readTime() {
  year = Serial.parseInt();
  while (Serial.read() != '/') {}
  month = Serial.parseInt();
  while (Serial.read() != '/') {}
  day = Serial.parseInt();
  while (Serial.read() != ' ') {}
  hour = Serial.parseInt();
  while (Serial.read() != ':') {}
  minute = Serial.parseInt();
  while (Serial.read() != ':') {}
  second = Serial.parseInt();
}

void updateSecond() {
  second++; // 초 증가
  if (second >= 60) { // 60초가 되면
    second = 0; // 0초로 초기화
    minute++; // 분 증가
    if (minute >= 60) { // 60분이 되면
      minute = 0; // 0분으로 초기화
      hour++; // 시 증가
      if (hour >= 24) { // 24시가 되면
        hour = 0; // 0시로 초기화
        day++; // 일 증가
        // 달마다 일수가 다를 수 있으므로 해당 달의 마지막 날을 체크하여 일을 증가시킴
        if (day > daysInMonth(year, month)) {
          day = 1; // 다음 달로 넘어가기 위해 일을 1로 설정
          month++; // 달 증가
          if (month > 12) { // 12월을 넘어가면
            month = 1; // 1월로 초기화
            year++; // 년도 증가
          }
        }
      }
    }
  }
}

void printTime() {
//   Serial.print("Current time: ");
    // printDay();
 Serial.print(year);
 Serial.print("/");
 if (month < 10) Serial.print("0");
 Serial.print(month);
 Serial.print("/");
 if (day < 10) Serial.print("0");
 Serial.print(day);Serial.print(" ");
  Serial.print(dayOfWeek);
  Serial.print(" ");
  if (hour < 10) Serial.print("0");
  Serial.print(hour);
  Serial.print(":");
  if (minute < 10) Serial.print("0");
  Serial.print(minute);
  Serial.print(":");
  if (second < 10) Serial.print("0");
  Serial.println(second);
}

void printDay() {
  const char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  // 요일 정보는 이미 업데이트되어 있으므로 그대로 사용
//   Serial.print(days[dayOfWeek]);
}

int daysInMonth(int year, int month) {
  int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
    days[1] = 29; // 윤년인 경우 2월의 일 수 변경
  }
  return days[month - 1]; // 인덱스는 0부터 시작하므로 1을 빼줌
}

int getDayOfWeek(int year, int month, int day) {
  int t = (14 - month) / 12;
  int y = year - t;
  int m = month + 12 * t - 2;
  int d = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
  return d;
}

void saveTimeToEEPROM() {
  EEPROM.write(0, 1); // EEPROM에 시간이 설정되었음을 표시
  EEPROM.write(1, year);
  EEPROM.write(2, month);
  EEPROM.write(3, day);
  EEPROM.write(4, hour);
  EEPROM.write(5, minute);
  EEPROM.write(6, second);
  // 요일 정보도 저장
  EEPROM.write(7, getDayOfWeek(year, month, day)); 
  // EEPROM.commit(); // EEPROM에 저장된 값을 영구적으로 저장
  //getDayOfWeek(year, month, day); // 요일 정보 업데이트
}
