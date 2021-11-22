void setup() {
 
Serial.begin(115200);



}

void loop() {

if(Serial.available()){

  
  int us = Serial.read(); // 마이크로초를 입력하세요
  
  
  Serial.print("단위환산_초:");
  Serial.println(us);

  Serial.print("단위환산_주기:");
  Serial.println(us);

  
}

}
