#include <DS1302.h>
#include <EEPROM.h>

const int CLK = 5;
const int DAT = 6;
const int RST = 7;

DS1302 myrtc(RST, DAT, CLK);
Time storedTime;  // EEPROM에 저장된 시간

void setup() {
    myrtc.halt(false);
    myrtc.writeProtect(false);

    Serial.begin(9600);
    Serial.println("DS1302RTC Test");
    Serial.println("---------------");

    // EEPROM에서 시간을 읽어옵니다.
    EEPROM.get(0, storedTime);

    // 저장된 시간이 없는 경우에만 시간을 입력 받습니다.
    if (storedTime.year == 0) {
        setTimeFromSerial();
    } else {
        // 저장된 시간을 출력합니다.
        printTime(storedTime);
    }
}

void loop() {
    // 시리얼 모니터에 저장된 시간을 출력합니다.
    printTime(storedTime);
    delay(1000);  // 1초마다 시간을 출력합니다.
}

// 시리얼 통신을 통해 시간을 입력받는 함수
void setTimeFromSerial() {
    Serial.println("Enter the current time (YYYY-MM-DD HH:MM:SS):");
    while (!Serial.available()) {
        // 시리얼 입력을 기다립니다.
    }

    // 시리얼 입력에서 시간을 읽어옵니다.
    String input = Serial.readString();
    int year, month, day, hour, minute, second;
    sscanf(input.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

    // 시간 정보를 Time 구조체에 저장합니다.
    storedTime.year = year;
    storedTime.mon = month;
    storedTime.date = day;
    storedTime.hour = hour;
    storedTime.min = minute;
    storedTime.sec = second;

    // EEPROM에 시간을 저장합니다.
    EEPROM.put(0, storedTime);

    Serial.println("Time is set.");
}

// 시간을 시리얼 모니터에 출력하는 함수
void printTime(Time t) {
    Serial.print(t.year);
    Serial.print("-");
    if (t.mon < 10) Serial.print("0");
    Serial.print(t.mon);
    Serial.print("-");
    if (t.date < 10) Serial.print("0");
    Serial.print(t.date);
    Serial.print(" ");
    if (t.hour < 10) Serial.print("0");
    Serial.print(t.hour);
    Serial.print(":");
    if (t.min < 10) Serial.print("0");
    Serial.print(t.min);
    Serial.print(":");
    if (t.sec < 10) Serial.print("0");
    Serial.println(t.sec);
}
