void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop() {
  if (Serial.available() > 0)
  {
    char sData = Serial.read();
    if (sData == 'a')
    {
      digitalWrite(8, HIGH);
    }
    else if (sData == 'b')
    {
      digitalWrite(8, LOW);
    }
  }
}
