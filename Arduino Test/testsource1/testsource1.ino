/**
  모터 제어 테스트 코드
*/
void setup() {
  // pinMode(13, OUTPUT);
  Serial.begin(9600);
  armup();
  delay(3000);
  armdown();
}

void armup() {
  Serial.print("#9P2500#13P500\r\n");
}

void armdown() {
  Serial.print("#9P1500#13P1500\r\n");
}

void move() {
  //
  Serial.print("#13P1000T500\r\n");
  delay(1000);
  Serial.print("#13P1500T500\r\n");
  delay(1000);

}

void loop() {


}
