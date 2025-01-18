// melody.cpp
#include "melody.h"

void setup() {
    pinMode(BUZZER_PIN, OUTPUT);

    // 멜로디 두 번 반복
    for (int repeat = 0; repeat < 2; repeat++) {
        playMelody();
    }
    // 마지막 한 번 더 반복
    playMelody();
}

void loop() {
    // 프로그램 종료 후 아무 작업 없음
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