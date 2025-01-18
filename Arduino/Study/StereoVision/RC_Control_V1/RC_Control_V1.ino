#include <AFMotor.h>
#include <Servo.h>

// 연결 리스트의 노드 구조체 정의
struct Node {
  String direction;  // 방향 (좌우 조향 상태)
  int movementDistance;  // 이동 거리
  int objectDistance;  // 객체 간의 거리
  Node* next;  // 다음 노드를 가리키는 포인터
};

// 연결 리스트 클래스 정의
class LinkedList {
public:
  Node* head;  // 리스트의 헤드 노드

  LinkedList() {
    head = NULL;  // 리스트 초기화
  }

  // 리스트에 노드를 추가하는 함수
  void append(String direction, int movementDistance, int objectDistance) {
    Node* newNode = new Node();
    newNode->direction = direction;
    newNode->movementDistance = movementDistance;
    newNode->objectDistance = objectDistance;
    newNode->next = NULL;

    if (head == NULL) {
      head = newNode;  // 첫 번째 노드로 설정
    } else {
      Node* temp = head;
      while (temp->next != NULL) {
        temp = temp->next;  // 리스트의 끝으로 이동
      }
      temp->next = newNode;  // 새로운 노드를 리스트 끝에 추가
    }
  }

  // 리스트에서 최단 거리를 가진 노드를 찾는 함수
  Node* findMinDistance() {
    if (head == NULL) return NULL;  // 리스트가 비어 있으면 NULL 반환
    Node* minNode = head;
    Node* temp = head->next;

    while (temp != NULL) {
      if (temp->objectDistance < minNode->objectDistance) {
        minNode = temp;  // 최단 거리를 가진 노드를 찾음
      }
      temp = temp->next;
    }
    return minNode;
  }
};

// DC 모터 제어를 위한 객체 생성
AF_DCMotor motor1(1); // 1번 모터
AF_DCMotor motor2(2); // 2번 모터

// 서보 모터 제어를 위한 객체 생성
Servo ms;

LinkedList directionList;  // 연결 리스트 초기화
int speed = 100;           // 모터 초기 속도 설정

void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작
  Serial.println("RC Control ready!");  // 초기화 메시지 출력

  // 모터 초기 설정
  motor1.setSpeed(speed);  // 모터 속도 설정
  motor2.setSpeed(speed); 
  motor1.run(RELEASE);  // 모터 정지 상태로 설정
  motor2.run(RELEASE);  

  // 서보 모터 초기 설정
  ms.attach(9);         // 서보 모터를 9번 핀에 연결
  ms.write(50);         // 서보 모터를 중앙(50도)으로 설정
}

void loop() {
  if (Serial.available()) {  // 시리얼 입력이 있을 경우
    String command = Serial.readString();  // 시리얼로부터 문자열 읽기
    command.trim();  // 공백 제거

    if (command.equalsIgnoreCase("find")) {  // 파이썬으로부터 'find' 명령을 받으면
      Serial.println("Find command received, scanning area...");

      // 우측으로 조향하여 이동
      ms.write(25);  // 오른쪽 45도 조향
      delay(500);  // 서보 모터 조향 시간 대기

      motor1.run(BACKWARD);  // 모터 전진
      motor2.run(BACKWARD);
      delay(2000);  // 2초간 이동
      motor1.run(RELEASE);  // 모터 정지
      motor2.run(RELEASE);
      Serial.println("check");  // 파이썬으로 'check' 신호 전송

      int distanceRight = waitAndGetDistance();  // 파이썬으로부터 거리를 받아옴
      directionList.append("right", 45, distanceRight);  // 연결 리스트에 저장

      // 원점으로 복귀
      ms.write(50);  // 서보 모터를 중앙으로 복귀
      delay(500);  // 중앙으로 돌아올 시간 대기

      // 좌측으로 조향하여 이동
      ms.write(75);  // 왼쪽 45도 조향
      delay(500);  // 서보 모터 조향 시간 대기

      motor1.run(BACKWARD);  // 모터 전진
      motor2.run(BACKWARD);
      delay(2000);  // 2초간 이동
      motor1.run(RELEASE);  // 모터 정지
      motor2.run(RELEASE);
      Serial.println("check");  // 파이썬으로 'check' 신호 전송

      int distanceLeft = waitAndGetDistance();  // 파이썬으로부터 거리를 받아옴
      directionList.append("left", 45, distanceLeft);  // 연결 리스트에 저장

      // 원점으로 복귀
      ms.write(50);  // 서보 모터를 중앙으로 복귀
      delay(500);  // 중앙으로 돌아올 시간 대기

      Node* minNode = directionList.findMinDistance();  // 최단 거리 노드 찾기
      if (minNode != NULL) {
        moveToDirection(minNode->direction);  // 최단 거리 방향으로 이동
        motor1.setSpeed(200);  // 이동 시 속도를 200으로 설정
        motor2.setSpeed(200);
        Serial.println("ready");  // 파이썬에 'ready' 신호 전송
      }
    } else if (command.equalsIgnoreCase("arrive")) {  // 파이썬으로부터 'arrive' 명령을 받으면
      Serial.println("Arrived at destination.");
      motor1.run(RELEASE);  // 모터 정지
      motor2.run(RELEASE);
      delay(500);
      Serial.println("waiting for next command...");  // 다음 명령 대기 중
    } else {
      motor1.run(RELEASE);  // 유효하지 않은 명령이 들어오면 모터 정지
      motor2.run(RELEASE);
      Serial.println("Invalid command. Motors stopped.");  // 유효하지 않은 명령임을 출력
    }
  }
}

// 최단 거리 방향으로 이동하는 함수
void moveToDirection(String direction) {
  if (direction.equals("right")) {
    ms.write(25);  // 오른쪽 조향
  } else if (direction.equals("left")) {
    ms.write(75);  // 왼쪽 조향
  }
  
  motor1.run(BACKWARD);  // 모터 전진
  motor2.run(BACKWARD);
  delay(2000);  // 2초간 이동
  motor1.run(RELEASE);  // 모터 정지
  motor2.run(RELEASE);
}

// 파이썬으로부터 거리를 받아오는 함수
int waitAndGetDistance() {
  while (!Serial.available()) {}  // 파이썬으로부터 데이터를 기다림
  String distanceStr = Serial.readString();  // 데이터를 문자열로 읽기
  distanceStr.trim();  // 문자열의 공백 제거
  return distanceStr.toInt();  // 문자열을 정수로 변환하여 반환
}
