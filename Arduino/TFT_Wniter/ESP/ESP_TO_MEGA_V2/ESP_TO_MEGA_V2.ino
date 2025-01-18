#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "RTClib.h"
#include "melody.h"

// Wi-Fi 설정
const char* ssid = "1606_2G";
const char* password = "a12345678";

// Python 서버 주소 및 포트
const char* serverHost = "192.168.1.9"; // Python 서버의 실제 IP 주소
const int serverPort = 8080;

RTC_DS3231 rtc; // RTC 구조체 변수 선언
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

String alarmTime = "";
bool alarmSet = false;

// 서버 응답에서 본문 추출
String extractData(String serverResponse) {
    int startIndex = serverResponse.indexOf("\r\n\r\n") + 4; // HTTP 헤더 끝의 인덱스
    if (startIndex >= 4 && startIndex < serverResponse.length()) {
        return serverResponse.substring(startIndex);
    }
    return "";
}

void setup() {
    Serial.begin(115200);
    Wire.begin(D8, D7); // RTC I2C 핀 설정

    // RTC 초기화
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    if (rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    // Wi-Fi 연결
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi. IP: " + WiFi.localIP().toString());

    // 현재 시간 출력
    DateTime now = rtc.now();
    Serial.print("Now Time : ");
    Serial.print(now.year(), DEC);
    Serial.print(".");
    Serial.print(now.month(), DEC);
    Serial.print(".");
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(":");
    Serial.println(now.minute(), DEC);

    // 알람 시간 입력
    while (!alarmSet) {
        Serial.println("Set Alarm Time (HH:MM) or type 'reset': ");
        while (Serial.available() == 0) {
            delay(100);
        }
        alarmTime = Serial.readStringUntil('\n');
        alarmTime.trim();

        if (alarmTime.equalsIgnoreCase("reset")) {
            alarmSet = false;
            Serial.println("Alarm reset. Please set a new alarm time.");
            continue;
        }

        if (!validateAlarmTime(alarmTime)) {
            Serial.println("Invalid alarm time. Please enter a valid time in HH:MM format.");
            alarmSet = false;
            continue;
        }

        Serial.println("Alarm set for: " + alarmTime);
        alarmSet = true;
    }
}

void loop() {
    DateTime now = rtc.now();
    String currentTime = String(now.year(), DEC) + "." +
                         String(now.month(), DEC) + "." +
                         String(now.day(), DEC) + "." +
                         String(now.hour(), DEC) + ":" +
                         (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);

    if (alarmSet && currentTime.endsWith(alarmTime)) {
        for (int i = 0; i < 3; i++) {
            playMelody();
            delay(30000); // 30초 대기
        }
        alarmSet = false; // 알람 초기화
    }

    // 서버와 통신하여 문자열 출력
    communicateWithServer(currentTime);
    delay(1000);
}

void communicateWithServer(String currentTime) {
    WiFiClient client;
    if (!client.connect(serverHost, serverPort)) {
        Serial.println("Connection to server failed!");
        return;
    }

    client.println("GET / HTTP/1.1");
    client.println("Host: " + String(serverHost));
    client.println("Connection: close");
    client.println();

    String response = "";
    while (client.connected() || client.available()) {
        if (client.available()) {
            char c = client.read();
            response += c;
        }
    }
    client.stop();

    String data = extractData(response);
    if (!data.isEmpty()) {
        Serial.println(currentTime + "_" + data);
    } else {
        Serial.println("Failed to extract server data.");
    }
}

bool validateAlarmTime(String time) {
    if (time.length() != 5 || time[2] != ':') return false;
    int hour = time.substring(0, 2).toInt();
    int minute = time.substring(3).toInt();
    return hour >= 0 && hour < 24 && minute >= 0 && minute < 60;
}

void playMelody() {
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        if (melody[i] == -1) {
            delay(durations[i]);
        } else {
            tone(BUZZER_PIN, melody[i], durations[i]);
            delay(durations[i]);
            delay(50); // 음과 음 사이 간격
        }
    }
}
