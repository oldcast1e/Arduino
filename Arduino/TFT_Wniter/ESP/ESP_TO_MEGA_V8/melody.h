// melody.h
#ifndef MELODY_H
#define MELODY_H

#include <Arduino.h>

// 핀 정의
const int BUZZER_PIN = D0;

// 음계 주파수 정의
#define NOTE_G4 392 // 솔
#define NOTE_E4 330 // 미
#define NOTE_C4 261 // 도

// 멜로디 및 지속 시간 배열 정의
const int melody[] = {
    NOTE_G4, NOTE_E4, // 솔미
    NOTE_E4, NOTE_E4, NOTE_E4, -1, // 미미미, 대기
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_C4, // 미(간격짧게)솔미도
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_C4, // 미(간격짧게)솔미도
    NOTE_G4, NOTE_E4, NOTE_E4, -1, // 솔미미(마지막 길게)
    NOTE_C4, NOTE_C4, NOTE_C4, -1, // 도도도(마지막만 1초간 유지)
    NOTE_E4, NOTE_E4, NOTE_E4, -1, // 미미미
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_C4, // 미(간격짧게)솔미도
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_C4, // 미(간격짧게)솔미도
    NOTE_G4, NOTE_E4, NOTE_E4, // 솔미미(마지막 길게)
    NOTE_C4, NOTE_C4, NOTE_C4, // 도도도(마지막만 1초간 유지)
    NOTE_G4, NOTE_G4, NOTE_E4, // 솔솔미 (마지막 1초 유지)
    NOTE_C4, NOTE_E4, -1, // 도미, 대기
    NOTE_C4, NOTE_E4, NOTE_C4, NOTE_E4, // 도미도미
    NOTE_G4, NOTE_C4, NOTE_C4, NOTE_E4, NOTE_E4, // 도도미미
    NOTE_G4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_C4, NOTE_E4, // 솔(간격짧게)솔미도미
    NOTE_G4, 
    
    -1 // 솔(2초간 유지), 2초 대기
};

const int durations[] = {
    500, 500, // 솔미
    200, 200, 200, 200, // 미미미, 대기
    200, 300, 300, 300, // 미(간격짧게)솔미도
    200, 300, 300, 300, // 미(간격짧게)솔미도
    300, 200, 1000, // 솔미미(마지막 길게)
    100, // 대기
    300, 300, 1000, // 도도도(마지막만 1초간 유지)
    300, // 대기
    300, 300, 1000, // 미미미
    300, // 대기
    200, 300, 300, 300, // 미(간격짧게)솔미도
    200, 300, 300, 300, // 미(간격짧게)솔미도
    300, 300, 1000, // 솔미미(마지막 길게)
    300, 300, 1000, // 도도도(마지막만 1초간 유지)
    300, // 대기
    300, 300, 200, // 솔솔미 (마지막 1초 유지)
    300, 300, // 도미
    250, 250, 250, 250, // 도미도미
    1000, // 솔(1초간 유지)
    200, 200, 200, 200, // 도도미미
    250, 300, 200, 300, 200, 300, 200, // 솔(간격짧게)솔미도미
    2000, // 솔(2초간 유지)

    2000 // 2초 대기
};

// 함수 선언
void playMelody();

#endif
