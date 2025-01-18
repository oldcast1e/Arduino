// 핀 번호 정의
const int speakerPin = 3;

// 각 음계의 주파수 (도레미파솔라시도)
const int notes[] = {
  262, // 도 (C4)
  294, // 레 (D4)
  330, // 미 (E4)
  349, // 파 (F4)
  392, // 솔 (G4)
  440, // 라 (A4)
  494  // 시 (B4)
};

// 음표 지속 시간
const int noteDuration = 500; // 500ms

void setup() {
  // 스피커 핀 설정
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 7; i++) {
    playTone(notes[i], noteDuration);
    delay(100); // 음 사이의 간격 (100ms)
  }
  delay(1000); // 전체 멜로디 끝난 후 대기 (1초)
}

void playTone(int frequency, int duration) {
  int period = 1000000 / frequency; // 주기 계산 (마이크로초 단위)
  int pulse = period / 2;          // 절반 주기 (하이/로우 비율)
  long cycles = (long)frequency * duration / 1000; // 전체 주기 수

  for (long i = 0; i < cycles; i++) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(pulse);
  }
}
