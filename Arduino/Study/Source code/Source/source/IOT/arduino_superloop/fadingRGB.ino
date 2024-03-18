int fadingRGB_ledPin[3] = {10,6,9};
long fadingRGB_previousMillis[3] = {0,0,0};
long fadingRGB_interval[3] = {30,60,120};
int fadeRGBValue[3] = {0,0,0};
int fadeRGBDir[3] = {1,1,1};

int fadeRGBbuttonToggle = 0;

void fadingRGB_setup() { 
  attachInterrupt(digitalPinToInterrupt(3), fadeRGBbuttonIsr, RISING);  
}

void fadeRGBbuttonIsr() {
  fadeRGBbuttonToggle = !fadeRGBbuttonToggle;
}

void fadingRGB_loop() {  
//  if(fadeRGBbuttonToggle==0) {
//    for(int i=0;i<3;i++)
//      analogWrite(fadingRGB_ledPin[i], 0);
//    return;
//  }
  
  unsigned long currentMillis = millis();
  
  for(int i=0;i<3;i++) {
    if(currentMillis - fadingRGB_previousMillis[i] >= fadingRGB_interval[i]) {
      fadingRGB_previousMillis[i] = currentMillis;   

      if(fadeRGBDir[i] == 1) {
        if(fadeRGBValue[i] <= 255) {
          fadeRGBValue[i] += 5;
          if(fadeRGBValue[i] > 255) {
            fadeRGBValue[i] = 255; 
            fadeRGBDir[i] = 0;
          }  
        }
      } else {
        if(fadeRGBValue[i] >= 0) {
          fadeRGBValue[i] -= 5;
          if(fadeRGBValue[i] < 0) {
            fadeRGBValue[i] = 0;
            fadeRGBDir[i] = 1;
          }
        }
      }
      analogWrite(fadingRGB_ledPin[i], fadeRGBValue[i]);        
    }
  }
}
