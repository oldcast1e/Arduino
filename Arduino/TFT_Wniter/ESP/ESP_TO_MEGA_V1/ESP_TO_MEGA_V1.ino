#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "RTClib.h"
#include "melody.h"

// Wi-Fi 설정
const char* ssid = "oldcast1e";
const char* password = "popopopo";

// Python 서버 주소 및 포트
const char* serverHost = "172.20.17.62"; // Python 서버의 실제 IP 주소
const int serverPort = 8080;

RTC_DS3231 rtc;  // RTC 구조체 변수 선언
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

String alarmTime = "";
bool alarmSet = false;
unsigned long lastRequestTime = 0;

void setup() {
    Serial.begin(115200);
    Wire.begin(D8, D7);
    pinMode(BUZZER_PIN, OUTPUT);

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

    // 알람 시간 입력
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

    while (!alarmSet) {
        Serial.println("Alarm Rest : Enter \"Reset\"");
        Serial.println("Set Alarm Time (HH:MM): ");
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

    // 알람 시간 확인
    String currentTime = String(now.hour(), DEC) + ":" + (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
    if (alarmSet && currentTime.equals(alarmTime)) {
        for (int i = 0; i < 3; i++) {
            playMelody();
            delay(30000); // 30초 간격
        }
        alarmSet = false; // 알람 종료 후 초기화
    }

    // I2C 통신으로 데이터 전송
    Wire.beginTransmission(8); // 아두이노 메가 I2C 주소
    String message = "Current time: " + currentTime;
    Wire.write(message.c_str(), message.length());
    Wire.endTransmission();

    // Python 서버 통신
    communicateWithServer();

    delay(1000); // 1초 대기
}

bool validateAlarmTime(String time) {
    if (time.length() != 5 || time[2] != ':') return false;
    int hour = time.substring(0, 2).toInt();
    int minute = time.substring(3).toInt();
    return hour >= 0 && hour < 24 && minute >= 0 && minute < 60;
}

void communicateWithServer() {
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

    Serial.println("Response from server: ");
    Serial.println(response);
    client.stop();
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