int fading_ledPin = 11;
long fading_previousMillis = 0;
long fading_interval = 30;
int fadeValue = 0;
int fadeDir = 1;

int buttonToggle = 0;

void fading_setup() {
  attachInterrupt(digitalPinToInterrupt(2), buttonIsr, RISING);  
}

void buttonIsr() {
  buttonToggle = !buttonToggle;
}

void fading_loop() {
//  if(buttonToggle==0) {
//    analogWrite(fading_ledPin, 0);
//    return;
//  }
  
  unsigned long currentMillis = millis();
  
  if(currentMillis - fading_previousMillis >= fading_interval) {
    fading_previousMillis = currentMillis; 

    if(fadeDir == 1) { 
      if(fadeValue <= 255) {        
        fadeValue += 5;
        if(fadeValue > 255) {          
          fadeValue = 255;
          fadeDir = 0;
        }  
      }
    } else { 
      if(fadeValue >= 0) {
        fadeValue -= 5;
        if(fadeValue < 0) {
          fadeValue = 0;
          fadeDir = 1;          
        }
      }
    }
    analogWrite(fading_ledPin, fadeValue);        
  }
}
