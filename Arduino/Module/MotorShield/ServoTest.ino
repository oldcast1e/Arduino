#include <AFMotor.h>
#include <Servo.h>  // 아두이노 기본 Servo 라이브러리 포함

// Adafruit Motor Shield로 DC 모터 제어 (예제)
// AF_DCMotor motor(4);

// 서보 모터 제어
Servo myServo;

void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작
  Serial.println("Motor test!");

  // DC 모터 설정
  // motor.setSpeed(200);
  // motor.run(RELEASE);

  // 서보 모터 설정 (Adafruit Motor Shield의 SER1 핀에 연결됨)
  myServo.attach(10);  // SER1에 해당하는 핀 번호는 9번입니다.
  myServo.write(179);  // 서보 모터를 90도로 초기화
}

void loop() {
  // 추가 동작 없음 (필요시 여기서 서보나 DC 모터 제어 가능)
}
