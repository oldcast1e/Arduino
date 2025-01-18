#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "RTClib.h"
#include "melody.h" // 멜로디 데이터 헤더 포함

// 핀 설정
#define BUZZER_PIN D0  // 부저 핀
#define RX_PIN 14      // 시리얼 Rx (GPIO14, D5)
#define TX_PIN 12      // 시리얼 Tx (GPIO12, D6)
#define SDA_PIN D8     // RTC SDA 핀
#define SCL_PIN D7     // RTC SCL 핀

// Wi-Fi 설정
const char* ssid = "1606_2G";
const char* password = "a12345678";

// const char* ssid = "oldcast1e";
// const char* password = "popopopo";

// Python 서버 주소 및 포트
// const char* serverHost = "192.168.1.8";
const char* serverHost = "192.168.1.7";
const int serverPort = 8080;

// RTC 모듈 초기화
RTC_DS3231 rtc;

// 알람 시간 저장
int alarmHour = -1;
int alarmMinute = -1;
bool alarmSet = false;

// 소프트웨어 시리얼 초기화
SoftwareSerial swSer(RX_PIN, TX_PIN);

// 서버 응답에서 본문 추출
String extractData(String serverResponse) {
    int startIndex = serverResponse.indexOf("\r\n\r\n") + 4;
    if (startIndex >= 4 && startIndex < serverResponse.length()) {
        return serverResponse.substring(startIndex);
    }
    return "";
}

// Wi-Fi 연결 설정
void connectWiFi() {
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
}

// 현재 시간 가져오기
String getCurrentTime() {
    DateTime now = rtc.now();
    String timeString = String(now.year(), DEC) + "." +
                        String(now.month(), DEC) + "." +
                        String(now.day(), DEC) + " " +
                        String(now.hour(), DEC) + ":" +
                        (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
    return timeString;
}

// 서버와 통신하여 데이터 가져오기
String communicateWithServer() {
    WiFiClient client;
    if (!client.connect(serverHost, serverPort)) {
        Serial.println("Connection to server failed!");
        return "";
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
        Serial.println("Extracted data: " + data);
    } else {
        Serial.println("Failed to extract server data.");
    }
    return data;
}

void sendDataToMega(String data) {
    String currentTime = getCurrentTime();
    currentTime.replace(" ", "_"); // 날짜와 시간의 공백을 '_'로 대체

    String message = currentTime + "_" + data;
    for (int i = 0; i < message.length(); i++) {
        swSer.write(message[i]);
        delay(2); // 문자 전송 후 대기 시간 증가
    }
    swSer.write('\n'); // 종료 문자로 '\n'만 추가
    // Serial.println(currentTime + " Send Success!");
    Serial.println("Data sent to Mega: ");
    Serial.println(data);  // 디버깅용 출력
}




// 알람 시간 설정
void setAlarmTime() {
    Serial.println("현재 날짜 : " + getCurrentTime());
    Serial.println("알람 시간 : ");
    while (!Serial.available()) delay(100);
    String alarmTime = Serial.readStringUntil('\n');
    alarmTime.trim();

    if (alarmTime.length() == 5 && alarmTime[2] == ':' && alarmTime.substring(0, 2).toInt() >= 0 && alarmTime.substring(0, 2).toInt() < 24 && alarmTime.substring(3).toInt() >= 0 && alarmTime.substring(3).toInt() < 60) {
        alarmHour = alarmTime.substring(0, 2).toInt();
        alarmMinute = alarmTime.substring(3).toInt();
        alarmSet = true;
        Serial.println("Alarm set for: " + alarmTime);
    } else {
        Serial.println("Invalid alarm time. Try again.");
        setAlarmTime();
    }
}

// 알람 확인 및 트리거
void checkAlarm(DateTime now) {
    if (alarmSet && now.hour() == alarmHour && now.minute() == alarmMinute) {
        Serial.println("Alarm Triggered!");
        for (int i = 0; i < 3; i++) {
            playMelody();
            delay(30000); // 30초 대기
        }
        // 알람을 다음 날로 설정
        DateTime tomorrow = now + TimeSpan(1, 0, 0, 0);
        alarmHour = tomorrow.hour();
        alarmMinute = tomorrow.minute();
        Serial.println("Alarm reset for tomorrow at the same time.");
    }
}

// 멜로디 재생
void playMelody() {
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        if (melody[i] == -1) {
            delay(durations[i]);
        } else {
            tone(BUZZER_PIN, melody[i], durations[i]);
            delay(durations[i]);
            delay(50);
        }
    }
}

void setup() {
    Serial.begin(9600);
    swSer.begin(9600);
    Wire.begin(SDA_PIN, SCL_PIN); // RTC 핀 설정
    pinMode(BUZZER_PIN, OUTPUT);

    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    if (rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    connectWiFi();
    setAlarmTime();
}

void loop() {
    DateTime now = rtc.now();
    checkAlarm(now);

    // 시리얼 모니터에서 명령 읽기
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n'); // 시리얼 모니터에서 입력
        command.trim();
        
        if (command.equalsIgnoreCase("reset")) {
            setAlarmTime(); // 알람 시간 재설정
        } else if (command.length() > 0) {
            sendDataToMega(command); // 입력 데이터를 Mega로 전송
        }
    }

    // 서버 데이터 가져오기 및 Mega로 전송
    String serverData = communicateWithServer();
    if (!serverData.isEmpty()) {
        sendDataToMega(serverData);
    }

    delay(60000); // 기존 대기 시간 유지
}

