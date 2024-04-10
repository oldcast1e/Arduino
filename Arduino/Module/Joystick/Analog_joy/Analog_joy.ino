void setup() {
  Serial.begin(9600);  
}
void loop() {
  // 입력 값을 -100~ 100 사이의 값으로 맵핑(치환)한다
  int Jox = map(analogRead(A0), 0, 1023, -100, 100);
  int Joy = map(analogRead(A1), 0, 1023, -100, 100);
  Serial.print(" Joy X : ");
  Serial.print(Jox);
  Serial.print("    Joy y : ");
  Serial.println(Joy);
  // 조이스틱의 스위치 기능에 대한 정의 
  if (digitalRead(A2)) {
    Serial.println("Off");    
  } else {
    Serial.println("On");
  }
  delay(1000);
}
