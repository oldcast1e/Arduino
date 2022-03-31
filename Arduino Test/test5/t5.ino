#define MAGNET 2

void setup() {
  Serial.begin(9600);
  pinMode(MAGNET,INPUT);
}

void loop() {
  if(digitalRead(MAGNET)== LOW){
    Serial.println("MAGNET ON");
    delay(1000);
  }else{
    Serial.println("MAGNET OFF");
    delay(1000);
  }
  delay(500);

}
