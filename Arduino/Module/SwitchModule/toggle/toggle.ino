int yellow = 7; // 노란색 LED 핀
int white = 6;  // 흰색 LED 핀
int button = 4; // 버튼 핀

bool yellowState = HIGH; // 노란색 LED 상태 (초기 OFF)
bool whiteState = LOW;   // 흰색 LED 상태 (초기 OFF)

unsigned long lastDebounceTime = 0; // 디바운싱을 위한 시간
unsigned long debounceDelay = 100;  // 디바운싱 시간 (100ms)

bool lastButtonState = HIGH; // 버튼의 이전 상태
bool currentButtonState = HIGH; // 버튼의 현재 상태

void setup() {
  Serial.begin(9600);
  pinMode(white, OUTPUT); // 흰색 LED 출력 모드 설정
  pinMode(yellow, OUTPUT); // 노란색 LED 출력 모드 설정
  pinMode(button, INPUT); // 버튼 입력 모드 설정
  
  digitalWrite(yellow, HIGH); // 노란색 LED 초기 상태 (ON)
  digitalWrite(white, LOW);  // 흰색 LED 초기 상태 (OFF)
}

void loop() {
  // 버튼 상태 읽기
  int reading = digitalRead(button);
  
  // 디바운싱 처리
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // 마지막 상태 변경 시간 기록
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // 버튼 상태가 안정적이면 상태 업데이트
    if (reading == LOW && currentButtonState == HIGH) {
      yellowState = !yellowState;
      whiteState = !whiteState;

      // LED 상태를 적용
      digitalWrite(yellow, yellowState ? HIGH : LOW);
      digitalWrite(white, whiteState ? HIGH : LOW);
    }
    currentButtonState = reading; // 현재 버튼 상태 업데이트
  }

  lastButtonState = reading; // 버튼의 이전 상태 기록

  // 디버깅용 버튼 상태 출력
  Serial.println(reading);
  delay(50); // 상태를 확인하기 위한 딜레이
}
