/**
<<<<<<< HEAD
  모터 제어 테스트 코드
*/
void armup() {
  Serial.print("#9P2500#13P500\r\n");
}

void armdown() {
  Serial.print("#9P1500#13P1500\r\n");
}
void formset(){
  Serial.print("#1P1500#2P1500#3P1500#4P1500#5P1500#9P1500#10P1500#11P1500#12P1500#13P1500#14P1500#16P1500#17P1500#18P1500#19P1500#20P1500#\r\n");

=======
모터 제어 테스트 코드
 */
void formset(){
  Serial.print("#1P1500#2P1500#3P1500#4P1500#5P1500#9P1500#10P1500#11P1500#12P1500#13P1500#14P1500#16P1500#17P1500#18P1500#19P1500#20P1500#\r\n");
>>>>>>> 5994196011667d743f67296c827588d9ab8422d8
}

void setup() {
  // pinMode(13, OUTPUT);
  Serial.begin(9600);
  formset();
  
  armup();
  delay(3000);
  armdown();
}



void move(){
//
  Serial.print("#13P1000T500\r\n");
  delay(1000);
  Serial.print("#13P1500T500\r\n");
  delay(1000);

}

void setup() {
  // pinMode(13, OUTPUT);
  Serial.begin(9600);
  formset(); delay(1000);

  armup();delay(3000);
  armdown();
}

void loop() {

}
