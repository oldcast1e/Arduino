#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;  // RTC 구조체 변수 선언

// 요일 이름 저장 배열
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () 
{
  Serial.begin(115200);       // 시리얼 모니터 통신 시작 (ESP8266에 적합한 속도)
  Wire.begin(D8, D7);         // I2C 핀 설정 (D8 = SDA, D7 = SCL)

  delay(3000); // wait for console opening

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1); // RTC가 연결되지 않으면 무한 대기
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // RTC를 컴파일된 날짜와 시간으로 초기화
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop () {
    DateTime now = rtc.now();   // 현재 날짜, 시간을 RTC 모듈에서 가져옴
    
    // 현재 시간 출력
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);  // 요일 출력
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    // Unix 타임스탬프 출력
    Serial.print(" since midnight 1/1/1970 = "); 
    Serial.print(now.unixtime()); // 유닉스 타임스탬프 출력
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L); // 지난 일 수 출력
    Serial.println("d");
    
    // 현재 시간 기준 7일, 12시간, 30분, 6초 이후 시간 계산
    DateTime future (now + TimeSpan(7,12,30,6));
    
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    delay(3000); // 3초 대기
}
