int ledPin = 11;

void setup() {  
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);           
  digitalWrite(13, LOW); 
  delay(1000);  

  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
	analogWrite(ledPin, fadeValue);
	delay(30);
  }
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
	analogWrite(ledPin, fadeValue);
	delay(30);
  }  
}