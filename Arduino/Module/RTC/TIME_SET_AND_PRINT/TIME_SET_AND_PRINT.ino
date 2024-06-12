#include <DS1302.h>

const int CLK = 5;
const int DAT = 6;
const int RST = 7;

DS1302 myrtc(RST, DAT, CLK);

unsigned long previousMillis = 0;  // 이전 시간을 저장할 변수
const long interval = 1000;        // 출력 간격 (1초)

void setup() {
    myrtc.halt(false);
    myrtc.writeProtect(false);

    Serial.begin(9600);
    Serial.println("DS1302RTC Test");
    Serial.println("---------------");

    myrtc.setDOW(MONDAY);
    myrtc.setTime(14, 30, 20);
    myrtc.setDate(2020, 4, 13);
}

void loop() {
    unsigned long currentMillis = millis();  // 현재 시간을 가져옴

    if (currentMillis - previousMillis >= interval) {  // 출력 간격이 지났는지 확인
        previousMillis = currentMillis;  // 현재 시간을 이전 시간으로 업데이트

        // DS1302 RTC 모듈에서 현재 시간을 가져옴
        Time t = myrtc.getTime();

        // 시리얼 모니터에 날짜와 시간 출력 (년-월-일 시간)
        Serial.print(t.year);
        Serial.print("-");
        if (t.mon < 10) Serial.print("0");  // 월이 한 자리 수일 때 앞에 0을 추가
        Serial.print(t.mon);
        Serial.print("-");
        if (t.date < 10) Serial.print("0");  // 일이 한 자리 수일 때 앞에 0을 추가
        Serial.print(t.date);
        Serial.print(" ");
        if (t.hour < 10) Serial.print("0");  // 시간이 한 자리 수일 때 앞에 0을 추가
        Serial.print(t.hour);
        Serial.print(":");
        if (t.min < 10) Serial.print("0");  // 분이 한 자리 수일 때 앞에 0을 추가
        Serial.print(t.min);
        Serial.print(":");
        if (t.sec < 10) Serial.print("0");  // 초가 한 자리 수일 때 앞에 0을 추가
        Serial.println(t.sec);
    }
}
