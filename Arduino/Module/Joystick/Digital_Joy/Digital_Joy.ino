void setup() {
  Serial.begin(9600);  
  pinMode(SW,INPUT);
}
void loop() {
  // 입력 값을 -100~ 100 사이의 값으로 맵핑(치환)한다
  int Jox = map(analogRead(A0), 0, 1023, -100, 100);
  int Joy = map(analogRead(A1), 0, 1023, -100, 100);
  Serial.print(" Joy X : ");
  Serial.print(Jox);
  Serial.print("    Joy y : ");
  Serial.println(Joy);
  // 조이스틱 SW에서는 눌렀을때 0 ,  떼었을 때 1 이 출력되나,
  // 반대가 되도록 '!'로 반전을 시켰음
  Serial.println(!digitalRead(SW)); //  
  delay(300);
}
