int photosensor_Pin = A2;    
int photosensor_ledPin[3] = {12,8,7};      
int photosensor_Value = 0;  

void vTaskPhotosensor( void *pvParameters ) {
 
  for(int i=0;i<3;i++)  
    pinMode(photosensor_ledPin[i], OUTPUT);

  while(1) {
    while(xSemaphoreTake( photosensor_key, portMAX_DELAY) != pdTRUE) { }
    
    photosensor_Value = analogRead(photosensor_Pin); 
 
    if(photosensor_Value < 100) 
      for(int i=0;i<3;i++) 
        digitalWrite(photosensor_ledPin[i], HIGH);
    else
      for(int i=0;i<3;i++)
        digitalWrite(photosensor_ledPin[i], LOW);
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    xSemaphoreGive( photosensor_key );
  }
}
