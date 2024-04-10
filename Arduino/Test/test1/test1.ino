int led = 13;
void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  
}

void loop(){
  if (Serial.available() > 0) { // 시리얼 버퍼에 데이터가 있는지 확인
    String str = Serial.readString(); // 시리얼 버퍼에서 문자열 읽기
    Serial.println("Received: " + str); // 입력받은 문자열 출력
  }
  digitalWrite(led,HIGH); delay(100);
  digitalWrite(led,LOW); delay(100);
}
