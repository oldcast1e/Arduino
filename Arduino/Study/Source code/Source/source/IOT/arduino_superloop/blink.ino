int blink_ledState = LOW;
long blink_previousMillis = 0;
long blink_interval = 1000;

const int blink_buttonPin = 4;
int blink_buttonState = 0;

void blink_setup() {
  pinMode(13, OUTPUT);
  pinMode(blink_buttonPin, INPUT);
}

void blink_loop() {
//  blink_buttonState = digitalRead(blink_buttonPin);
//  if(blink_buttonState == LOW) {
//    digitalWrite(13, LOW);
//    return;
//  }

  unsigned long currentMillis = millis();
  
  if(currentMillis - blink_previousMillis >= blink_interval) {
    blink_previousMillis = currentMillis;

    if(blink_ledState == LOW) 
      blink_ledState = HIGH;
    else
      blink_ledState = LOW;
      
    digitalWrite(13, blink_ledState);
  }
}
