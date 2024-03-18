// #define SOUND A0 //OUT 핀 설정(디지털신호 받는 핀)
float SOUND = A1;
int LED = 13;
void setup() {
    Serial.begin(9600);
    pinMode(SOUND, INPUT);
    pinMode(LED,OUTPUT);
}
void loop() {

  float val = analogRead(SOUND);
  // Serial.print("Sound Level: ");
  Serial.println(val);
  delay(1000);
}
