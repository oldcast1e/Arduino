#include <AFMotor.h>

// DC 모터 제어를 위한 객체 생성
AF_DCMotor motor1(1); // 1번 모터
AF_DCMotor motor2(2); // 2번 모터

void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작
  Serial.println("Motor control ready!");

  // 모터 초기 설정
  motor1.run(RELEASE);  // 1번 모터 초기 상태를 RELEASE로 설정
  motor2.run(RELEASE);  // 2번 모터 초기 상태를 RELEASE로 설정
}

void loop() {
  if (Serial.available()) { // 시리얼 입력이 있을 경우
    String input = Serial.readString(); // 시리얼로부터 문자열 읽기
    input.trim(); // 공백 제거
    int totalDistance = input.toInt(); // 문자열을 정수로 변환
    
    if (totalDistance > 0) { // 유효한 거리가 입력되었을 경우
      Serial.print("Motors moving forward for ");
      Serial.print(totalDistance);
      Serial.println(" cm");

      // 초기화 단계: 모터 속도 초기화
      motor1.setSpeed(200); // 초기 속도 설정
      motor2.setSpeed(200);
      
      int segments = totalDistance / 10;  // 10cm 단위로 나누기
      int remainingDistance = totalDistance % 10; // 10cm 단위로 나누고 남은 거리

      // 80% 거리까지 이동 (감속 없이)
      int normalSegments = segments * 0.8; // 80% 거리까지의 세그먼트 수
      int slowSegments = segments - normalSegments; // 남은 20% 거리의 세그먼트 수

      for (int i = 0; i < normalSegments; i++) {
        motor1.run(BACKWARD);  
        motor2.run(BACKWARD);  
        
        delay(500); // 각 10cm 이동 (0.5초)
        
        motor1.run(RELEASE);   
        motor2.run(RELEASE);   
        delay(50); // 0.05초 대기
      }
      
      // 감속 단계: 남은 20% 거리 이동
      motor1.setSpeed(100); // 감속된 속도로 설정
      motor2.setSpeed(100);
      for (int i = 0; i < slowSegments; i++) {
        motor1.run(BACKWARD);  
        motor2.run(BACKWARD);  
        
        delay(500); // 각 10cm 이동 (0.5초)
        
        motor1.run(RELEASE);   
        motor2.run(RELEASE);   
        delay(50); // 0.05초 대기
      }
      
      // 남은 거리 이동
      if (remainingDistance > 0) {
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        float timeToMove = (remainingDistance / 10.0) * 500.0; // 남은 거리 이동 시간 계산
        delay(timeToMove);
        motor1.run(RELEASE);   // 모터 정지
        motor2.run(RELEASE);
      }
      
      Serial.println("Motors stopped");
    } else {
      Serial.println("Invalid input. Please enter a positive integer.");
    }
  }
}
