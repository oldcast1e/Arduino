#include <AFMotor.h>
#include <Servo.h>

// DC 모터 제어를 위한 객체 생성
AF_DCMotor motor1(1); // 1번 모터
AF_DCMotor motor2(2); // 2번 모터

// 서보 모터 제어를 위한 객체 생성
Servo ms;

void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작
  Serial.println("Motor and Servo control ready!");

  // 모터 초기 설정
  motor1.setSpeed(200); // 1번 모터 속도 설정 (0-255)
  motor2.setSpeed(200); // 2번 모터 속도 설정 (0-255)
  motor1.run(RELEASE);  // 1번 모터 초기 상태를 RELEASE로 설정
  motor2.run(RELEASE);  // 2번 모터 초기 상태를 RELEASE로 설정

  // 서보 모터 초기 설정
  ms.attach(9);         // 서보 모터를 9번 핀에 연결
  ms.write(50);         // 서보 모터 초기 방향 설정 (50도)
}

void loop() {
  if (Serial.available()) { // 시리얼 입력이 있을 경우
    String command = Serial.readString(); // 시리얼로부터 문자열 읽기
    command.trim(); // 공백 제거
    
    if (command.equalsIgnoreCase("f")) { // 'f' 또는 'F' 입력 시
      Serial.println("Motors moving forward for 5 seconds");
      motor1.run(BACKWARD);  // 1번 모터 전진
      motor2.run(BACKWARD);  // 2번 모터 전진
      delay(500);          // 5초간 대기
      motor1.run(RELEASE);   // 1번 모터 정지
      motor2.run(RELEASE);   // 2번 모터 정지
      Serial.println("Motors stopped");
    } 
    else if (command.equalsIgnoreCase("b")) { // 'b' 또는 'B' 입력 시
      Serial.println("Motors moving backward for 5 seconds");
      motor1.run(FORWARD);  // 1번 모터 후진
      motor2.run(FORWARD);  // 2번 모터 후진
      delay(500);         // 5초간 대기
      motor1.run(RELEASE);  // 1번 모터 정지
      motor2.run(RELEASE);  // 2번 모터 정지
      Serial.println("Motors stopped");
    }
    else if (command.equalsIgnoreCase("lf")) { // 'lf' 또는 'LF' 입력 시
      Serial.println("Turning left and moving forward");
      ms.write(70);        // 서보 모터 왼쪽으로 조향 (80도)
      delay(500);         // 0.5초 대기
      motor1.run(BACKWARD);  // 1번 모터 전진
      motor2.run(BACKWARD);  // 2번 모터 전진
      delay(1000);          // 5초간 대기
      motor1.run(RELEASE);   // 1번 모터 정지
      motor2.run(RELEASE);   // 2번 모터 정지
      Serial.println("Motors stopped and steering reset");
      ms.write(50);         // 서보 모터 중앙으로 복귀
    }
    else if (command.equalsIgnoreCase("rf")) { // 'rf' 또는 'RF' 입력 시
      Serial.println("Turning right and moving forward");
      ms.write(30);        // 서보 모터 오른쪽으로 조향 (20도)
      delay(500);         // 0.5초 대기
      motor1.run(BACKWARD);  // 1번 모터 전진
      motor2.run(BACKWARD);  // 2번 모터 전진
      delay(1000);          // 10초간 대기
      motor1.run(RELEASE);   // 1번 모터 정지
      motor2.run(RELEASE);   // 2번 모터 정지
      Serial.println("Motors stopped and steering reset");
      ms.write(50);         // 서보 모터 중앙으로 복귀
    }
    else if (command.equalsIgnoreCase("lb")) { // 'lb' 또는 'LB' 입력 시
      Serial.println("Turning left and moving backward");
      ms.write(70);        // 서보 모터 왼쪽으로 조향 (80도)
      delay(1000);         // 0.5초 대기
      motor1.run(FORWARD);  // 1번 모터 후진
      motor2.run(FORWARD);  // 2번 모터 후진
      delay(1000);          // 5초간 대기
      motor1.run(RELEASE);   // 1번 모터 정지
      motor2.run(RELEASE);   // 2번 모터 정지
      Serial.println("Motors stopped and steering reset");
      ms.write(50);         // 서보 모터 중앙으로 복귀
    }
    else if (command.equalsIgnoreCase("rb")) { // 'rb' 또는 'RB' 입력 시
      Serial.println("Turning right and moving backward");
      ms.write(25);        // 서보 모터 오른쪽으로 조향 (20도)
      delay(100);         // 0.5초 대기
      motor1.run(FORWARD);  // 1번 모터 후진
      motor2.run(FORWARD);  // 2번 모터 후진
      delay(1000);          // 5초간 대기
      motor1.run(RELEASE);   // 1번 모터 정지
      motor2.run(RELEASE);   // 2번 모터 정지
      Serial.println("Motors stopped and steering reset");
      ms.write(50);         // 서보 모터 중앙으로 복귀
    }
    else {
      motor1.run(RELEASE); // 입력이 없거나 다른 입력이 들어오면 모터 정지
      motor2.run(RELEASE); 
      Serial.println("Invalid command. Motors stopped.");
    }
  }
}
