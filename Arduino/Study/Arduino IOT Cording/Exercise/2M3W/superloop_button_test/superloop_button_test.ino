const int b = 3;
void setup(){

  Serial.begin(115200);
  pinMode(b,INPUT);
}
void loop(){
  int n = digitalRead(b);
  Serial.println(n);
  delay(1000);
  
}
