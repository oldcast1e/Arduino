#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 

int piezoPin = 8; // 부저의 ⊕극을 오렌지 보드 8번에 연결 
int tempo = 200; // duration 옵션 값 설정 
int notes[25] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C }; 

void setup() {
  // put your setup code here, to run once:
  pinMode(piezoPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 7; i++){ 
    tone (piezoPin, notes[ i ], tempo); 
    delay (600); 
  } delay(700); // 멜로디 중간에 짧게 멈추는 용도 
  for (int i = 7; i < 12; i++) { 
    tone (piezoPin, notes[ i ], tempo); 
    delay(600); 
  }  delay(700); // 멜로디 중간에 짧게 멈추는 용도 
  for (int i = 12; i < 18; i++) { 
    tone (piezoPin, notes[ i ], tempo); 
    delay (600); 
  }delay(700); // 멜로디 중간에 짧게 멈추는 용도
  for (int i = 18; i < 25; i++){ 
    tone (piezoPin, notes[ i ], tempo); 
    delay(600); 
  } //delay(700);

}
