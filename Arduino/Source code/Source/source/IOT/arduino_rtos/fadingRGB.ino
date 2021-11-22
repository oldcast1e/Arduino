void vTaskFadingRed( void *pvParameters ) {
  fFadingRGB(10, 30, fadingRGBRed_key);
}

void vTaskFadingGreen( void *pvParameters ) {
  fFadingRGB(9, 60, fadingRGBGreen_key);
}

void vTaskFadingBlue( void *pvParameters ) {
  fFadingRGB(6, 90, fadingRGBBlue_key);
}

void fFadingRGB(int ledPin, long interval, SemaphoreHandle_t& key) {  
  while(1) {
    while(xSemaphoreTake( fadingRGBButton_event, portMAX_DELAY ) != pdTRUE) { }
    
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      while(xSemaphoreTake( key, portMAX_DELAY ) != pdTRUE) { } 
      analogWrite(ledPin, fadeValue);
      vTaskDelay(interval / portTICK_PERIOD_MS);
      xSemaphoreGive( key );
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      while(xSemaphoreTake( key, portMAX_DELAY ) != pdTRUE) { } 
      analogWrite(ledPin, fadeValue);
      vTaskDelay(interval / portTICK_PERIOD_MS);
      xSemaphoreGive( key );
    }
  }
}

void vFadingRGBButtonIsr( void ) { 
  xSemaphoreGiveFromISR( fadingRGBButton_event, NULL);
}
