int blinkRGB_ledPin[3] = {12,7,8};
int blinkRGB_ledState[3] = {LOW,LOW,LOW};
long blinkRGB_previousMillis[3] = {0,};
long blinkRGB_interval[3] = {1000,2000,3000};

const int blinkRGB_buttonPin = 5;
int blinkRGB_buttonState = 0;

void blinkRGB_setup() {
  for(int i=0;i<3;i++)
    pinMode(blinkRGB_ledPin[i], OUTPUT);  
  pinMode(blinkRGB_buttonPin, INPUT);
}

void blinkRGB_loop() {
//  blinkRGB_buttonState = digitalRead(blinkRGB_buttonPin);
//  if(blinkRGB_buttonState == LOW) {
//    for(int i=0;i<3;i++)
//      digitalWrite(blinkRGB_ledPin[i], LOW);
//    return;
//  }
  
  unsigned long currentMillis = millis();
  
  for(int i=0;i<3;i++) {
    if(currentMillis - blinkRGB_previousMillis[i] >= blinkRGB_interval[i]) {
      blinkRGB_previousMillis[i] = currentMillis;

      if(blinkRGB_ledState[i] == LOW) 
        blinkRGB_ledState[i] = HIGH;
      else
        blinkRGB_ledState[i] = LOW;
        
      digitalWrite(blinkRGB_ledPin[i], blinkRGB_ledState[i]);
    }
  }
}
