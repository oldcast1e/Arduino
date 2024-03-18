int LED = 13; //3번 핀을 LED 변수로 정의한다.

void setup() {
  pinMode(LED, OUTPUT); // 변수의 입출력 정의!!
}

void loop() {
  for(int i=0;i<255;i++){//0부터 255까지 반복 -> 서서히 밝아짐
      analogWrite(LED,i);//LED를 i만큼 아날로그 출력
        delay(5);//5밀리초 기다리기
    }
  for(int i=255;i>=0;i--){//255부터 0까지 반복 -> 서서히 어두워짐
      analogWrite(LED,i);
        delay(5);
    }
  
}
