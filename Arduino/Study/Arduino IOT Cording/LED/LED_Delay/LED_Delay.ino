const int LED1 = 7;//R
const int LED2 = 5;//B

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED1,HIGH);
  delay(1000);
  digitalWrite(LED1,LOW);
  delay(1000);

  for(int i=0;i<256;i++){
    analogWrite(LED2,i);
    delay(10);
  }
  for(int i=255;i>=0;i--){
    analogWrite(LED2,i);
    delay(10);
  }
  
}
