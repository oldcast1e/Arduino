int cds = A0;
// LED를 디지털 3핀으로 설정합니다.
int led = 13;

// 실행시 가장 먼저 호출되는 함수이며, 최초 1회만 실행됩니다.
// 변수를 선언하거나 초기화를 위한 코드를 포함합니다.
void setup() {
	// 조도센서의 동작 상태를 확인하기 위하여 시리얼 통신을 설정합니다. (전송속도 9600bps)
	// 메뉴 Tool -> Serial Monitor 클릭
	Serial.begin(9600);
	// LED 핀을 OUTPUT으로 설정합니다.
	pinMode(3, OUTPUT);
}

// setup() 함수가 호출된 이후, loop() 함수가 호출되며,
// 블록 안의 코드를 무한히 반복 실행됩니다.
void loop() {
	// 조도센서로 부터 측정된 밝기 값을 읽습니다.
	// 조도센서로 부터 입력되어지는 전압의 크기 (0~5V)에 따라 0~1023 범위의 값으로 변환되어 반환합니다.
	int cdsValue = analogRead(cds);

	// 측정된 밝기 값를 시리얼 모니터에 출력합니다.
	Serial.print("cds =  ");
	Serial.println(cdsValue);

	// 조도센서로 부터 측정된 밝기 값이 50보다 크다면, 아래의 블록을 실행합니다.
    // 기준 밝기 값은 주변환경에 따라 조절해 주세요.
	if (cdsValue < 150) {
		digitalWrite(led, HIGH);
		Serial.println("LED ON (cdsValue < 150)");
	}
	// 조도센서로 부터 측정된 밝기 값이 50보다 작면, 아래의 블록을 실행합니다.
	else {
		// LED가 연결된 핀의 로직레벨을 LOW (0V)로 설정하여, LED가 꺼지도록 합니다.
		digitalWrite(led, LOW);
		// LED상태를 시리얼 모니터에 출력합니다.
		Serial.println("LED OFF (cdsValue > 150)");
	}
	delay(1000);
}