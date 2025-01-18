#include "DisplayManager.h"
#include "WeatherDataParser.h"

// 주요 클래스 인스턴스 생성
DisplayManager displayManager;
WeatherDataParser weatherDataParser;

void setup() {
    displayManager.initialize();
    Serial.begin(115200);
    displayManager.updateDisplay(weatherDataParser);
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        weatherDataParser.parseInput(input);
        displayManager.updateDisplay(weatherDataParser);
        delay(5000); // 기존 UPDATE_INTERVAL
    }
}
