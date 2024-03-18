int photosensor_Pin = A2;    
int photosensor_ledPin[3] = {12,7,8}; 
int photosensor_Value = 0; 

long photosensor_previousMillis = 0;
long photosensor_interval = 1000;

void photosensor_setup() {
  for(int i=0;i<3;i++)  
    pinMode(photosensor_ledPin[i], OUTPUT);
}

void photosensor_loop() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - photosensor_previousMillis >= photosensor_interval) { 
    photosensor_previousMillis = currentMillis;   

    photosensor_Value = analogRead(photosensor_Pin);
    Serial.print("photosensor value = " );
    Serial.println(photosensor_Value);
    
    if(photosensor_Value < 100) 
      for(int i=0;i<3;i++) 
        digitalWrite(photosensor_ledPin[i], HIGH);
    else
      for(int i=0;i<3;i++)
        digitalWrite(photosensor_ledPin[i], LOW);    
  }
}
