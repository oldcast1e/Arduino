/**
모터 제어 테스트 코드
 */
void basic_stand(){
  Serial.print("#1P1500#2P1500#3P1500#4P1500#5P1500#9P1500#10P550#11P1500#12P2500#13P1500#14P1500#16P1500#17P1500#18P1500#19P1500#20P1500#\r\n");
}
void arm_up(){
  Serial.print("#9P2500#13P500\r\n");
  //9번 모터와 13번 모터를 최대치로 변경
}
void arm_down(){Serial.print("#9P1500#13P1500\r\n");}

void move(){
//
  Serial.print("#13P1000T500\r\n");
  delay(1000);
  Serial.print("#13P1500T500\r\n");
  delay(1000);

}

void arm_swing(){
  Serial.print("#10P2100#12P500\r\n");
  //두 팔을 회전 시킴
  /**
  [오른쪽] S10 : 2100
  [왼쪽] S12: 500
   */
}

void arm_power(){
  /**
  두 팔을 들어 팔 운동을 하고 내려 놓는 동작
   */
  arm_up();delay(1000);

  arm_swing();delay(3000);
  
  basic_stand();
}

void setup() {
  Serial.begin(9600);
  basic_stand(); delay(1000);
  //기본 자세 설정
  //-------------------------------

  arm_power();


}

void loop() {

}
