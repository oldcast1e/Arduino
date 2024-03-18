int fading_ledPin = 11;

void vTaskFading( void *pvParameters ) {

  while(1) {
    while(xSemaphoreTake( fadingButton_event, portMAX_DELAY ) != pdTRUE) { }
    
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      while(xSemaphoreTake( fading_key, portMAX_DELAY ) != pdTRUE) { } 
      analogWrite(fading_ledPin, fadeValue);
      vTaskDelay(30 / portTICK_PERIOD_MS);
      xSemaphoreGive( fading_key );
    }

    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      while(xSemaphoreTake( fading_key, portMAX_DELAY ) != pdTRUE) { } 
      analogWrite(fading_ledPin, fadeValue);
      vTaskDelay(30 / portTICK_PERIOD_MS);
      xSemaphoreGive( fading_key );
    }
  }
}

void vFadingButtonIsr ( void ) { 
  xSemaphoreGiveFromISR( fadingButton_event, NULL );
}
