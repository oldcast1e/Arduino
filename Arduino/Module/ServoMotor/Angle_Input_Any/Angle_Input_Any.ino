#include <Servo.h>

Servo ms;

void setup() {
    Serial.begin(115200);  // 시리얼 통신 시작 (속도: 115200bps)
    ms.attach(9);          // 서보 모터를 9번 핀에 연결
    ms.write(50);          // 서보 모터를 90도로 초기화

    /*
    RC CAR의 기본 조향 값 : 50
    왼쪽: 80
    오른쪽 : 20
    */
}

void loop() {
    if (Serial.available() > 0) {
        int angle = Serial.parseInt();  // 시리얼로부터 정수 값 읽기

        if (angle >= 0 && angle <= 179) {
            ms.write(angle);    // 입력된 각도로 서보 모터 동작
            delay(1000);        // 1초 대기
        }
        
        while (Serial.available() > 0) { // 시리얼 버퍼 비우기
            Serial.read();
        }
    }
}
