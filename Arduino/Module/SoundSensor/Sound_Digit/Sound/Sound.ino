#define SOUND 2 //OUT 핀 설정(디지털신호 받는 핀)
int LED = 13;
void setup() {
    Serial.begin(9600);
    pinMode(SOUND, INPUT);
    pinMode(LED,OUTPUT);
}
void loop() {

  if (digitalRead(SOUND) == HIGH) {
        Serial.println("SOUND ON");
        digitalWrite(LED,HIGH);
        // for(int i=0;i<256;i++){analogWrite(LED,i); delay(30);}
        
  }
  else {
    // for(int i=255;i>=0;i--){analogWrite(LED,i); delay(30);}
    Serial.println("Muted");
    digitalWrite(LED,LOW);
  }
  delay(1000);
}
