void vTaskBlink( void *pvParameters ) {
  
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
  
  pinMode(13, OUTPUT);

  while(true) {
    if(xSemaphoreTake( blink_key, xBlockTime) == pdTRUE) {
  
      digitalWrite(13, HIGH);
      vTaskDelay( 1000 / portTICK_PERIOD_MS );
      digitalWrite(13, LOW);
      vTaskDelay( 1000 / portTICK_PERIOD_MS );  
    
      xSemaphoreGive( blink_key ); 
    }
  }
}
