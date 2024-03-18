// 적외선 장애물 감지 센서는 적외선을 이용해서 앞에 장애물이 있는지 확인하는 센서입니다.
// 적외선 장애물 감지 센서는 디지털 3번 핀으로 설정합니다.
int infrared  = 12;
// LED는 디지털 6번핀으로 설정합니다.
int led = 13;

// 실행시 가장 먼저 호출되는 함수이며, 최초 1회만 실행됩니다.
// 변수를 선언하거나 초기화를 위한 코드를 포함합니다.
void setup() {
  // 적외선 장애물 감지 센서 핀을 INPUT으로 설정합니다.
  pinMode(infrared, INPUT);
  // LED 핀을 OUTPUT으로 설정합니다.
  pinMode(led, OUTPUT);

  // 적외선 장애물 감지 센서의 상태를 확인하기 위하여 시리얼 통신의 속도를 설정합니다.
  Serial.begin(9600);
}

// setup() 함수가 호출된 이후, loop() 함수가 호출되며,
// 블록 안의 코드를 무한히 반복 실행됩니다.
void loop() {
  // 적외선 감지 센서 부터 센서값을 읽습니다.
  // 감지되면 0, 감지되지 않으면 1이 나옵니다.
  int state = digitalRead(infrared);

  // 측정된 센서값을 시리얼 모니터에 출력합니다.
  Serial.print("Infrared = ");
  Serial.println(state);

  delay(1000);
  // 측정된 센서값이 0(감지)면 아래 블록을 실행합니다.
  if(state == 0){
    // LED를 켜지도록 합니다.
    digitalWrite(led, HIGH);
    // 경보 메세지를 시리얼 모니터에 출력합니다.
    Serial.println("Warning");
  }

  /// 측정된 센서값이 0 이외(감지되지 않음) 이면 아래 블록을 실행합니다.
  else{
    // LED를 꺼지도록 합니다.
    digitalWrite(led, LOW);
    // 안전 메세지를 시리얼 모니터에 출력합니다.
    Serial.println("Safe");
  }
}