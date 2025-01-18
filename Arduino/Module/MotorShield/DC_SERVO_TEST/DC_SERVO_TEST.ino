// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h>  // Servo 라이브러리 포함

// 1번 DC 모터와 2번 DC 모터를 제어하기 위한 AF_DCMotor 객체 생성
AF_DCMotor motor1(1); // 1번 모터
AF_DCMotor motor2(2); // 2번 모터

Servo myServo;  // Servo 객체 생성

void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작 (속도: 9600bps)
  Serial.println("Motor control ready!");

  // DC 모터 초기 설정
  motor1.setSpeed(200); // 1번 모터 속도 설정 (0-255)
  motor2.setSpeed(200); // 2번 모터 속도 설정 (0-255)
  motor1.run(RELEASE);  // 1번 모터 초기 상태를 RELEASE로 설정
  motor2.run(RELEASE);  // 2번 모터 초기 상태를 RELEASE로 설정

  // 서보 모터 초기 설정
  myServo.attach(9);  // 서보 모터를 10번 핀에 연결
  myServo.write(90);   // 서보 모터를 90도로 초기화
}

void loop() {
  // 모터 제어 코드 (이전과 동일)
  if (Serial.available()) { // 시리얼 입력이 있을 경우
    char command = Serial.read(); // 시리얼로부터 문자 읽기

    if (command == 'F' || command == 'f') { // 'F' 또는 'f' 입력 시
      Serial.println("Motors moving forward for 10 seconds");
      motor1.run(BACKWARD);  // 1번 모터 전진
      motor2.run(BACKWARD);  // 2번 모터 전진
      delay(5000);          // 5초간 대기
      motor1.run(RELEASE);   // 1번 모터 정지
      motor2.run(RELEASE);   // 2번 모터 정지
      Serial.println("Motors stopped");
    } 
    else if (command == 'B' || command == 'b') { // 'B' 또는 'b' 입력 시
      Serial.println("Motors moving backward for 10 seconds");
      motor1.run(FORWARD);  // 1번 모터 후진
      motor2.run(FORWARD);  // 2번 모터 후진
      delay(5000);         // 5초간 대기
      motor1.run(RELEASE);  // 1번 모터 정지
      motor2.run(RELEASE);  // 2번 모터 정지
      Serial.println("Motors stopped");
    }
    else {
      motor1.run(RELEASE); // 입력이 없거나 다른 입력이 들어오면 모터 정지
      motor2.run(RELEASE); 
    }
  }
}
