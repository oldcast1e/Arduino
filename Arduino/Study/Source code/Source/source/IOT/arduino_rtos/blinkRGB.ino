const int blinkRGB_buttonPin = 5;

void vTaskBlinkRed( void *pvParameters ) {
  pinMode(blinkRGB_buttonPin, INPUT);
  
  fBlinkRGB(12, 1000, blinkRGBRed_key);
}

void vTaskBlinkGreen( void *pvParameters ) {
  fBlinkRGB(8, 2000, blinkRGBGreen_key);
}

void vTaskBlinkBlue( void *pvParameters ) {
  fBlinkRGB(7, 4000, blinkRGBBlue_key);
}

void fBlinkRGB(int ledPin, long interval, SemaphoreHandle_t& key) {  
  pinMode(ledPin, OUTPUT);
  while(1) {
//    while(xSemaphoreTake( key, portMAX_DELAY) != pdTRUE) { }
    
//    int blinkRGB_buttonState = digitalRead(blinkRGB_buttonPin);
//    if(blinkRGB_buttonState == LOW) {
//      digitalWrite(ledPin, LOW);
//      xSemaphoreGive( key );
//      continue;
//    }
    
    digitalWrite(ledPin, HIGH);
    vTaskDelay( interval / portTICK_PERIOD_MS );
    digitalWrite(ledPin, LOW);
    vTaskDelay( interval / portTICK_PERIOD_MS );
//    xSemaphoreGive( key ); 
  }
}
