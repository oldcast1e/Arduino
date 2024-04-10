#include<IRremote.h>
IRsend irsend; //IRremote의 송신 객체 설정
void setup (){
}
void loop(){
  for (int i= 0; i<3; i++) {//의 값이 0부터 2가 될때까지 반복
    irsend.sendSony(0xa90, 12); //16진수인 A90 적외선 신호 내보냄 delay(40): //0.04초간 대기
  }
  delay (1000);
}
