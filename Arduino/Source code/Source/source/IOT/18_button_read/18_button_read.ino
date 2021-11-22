const int buttonPin = 4; 
const int ledPin =  13; 

int buttonState = LOW; 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
	digitalWrite(ledPin, HIGH);
  } else {
	digitalWrite(ledPin, LOW);
  }
}