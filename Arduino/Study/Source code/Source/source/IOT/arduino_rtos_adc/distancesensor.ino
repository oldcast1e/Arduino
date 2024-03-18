const int distancesensor_analogInPin = A3;  
const int distancesensor_analogOutPin[3] = {10,9,6}; 

int distancesensor_sensorValue = 0;        
int distancesensor_outputValue = 0;

void vTaskDistancesensor( void *pvParameters ) {

  while(1) {
    while(xSemaphoreTake( distancesensor_key, portMAX_DELAY) != pdTRUE) { }
    
    distancesensor_sensorValue = analogRead(distancesensor_analogInPin);
    distancesensor_outputValue = map(distancesensor_sensorValue, 0, 1023, 0, 255);

    for(int i=0;i<3;i++)
      analogWrite(distancesensor_analogOutPin[i], distancesensor_outputValue); 
    
    vTaskDelay(2 / portTICK_PERIOD_MS);
    
    xSemaphoreGive( distancesensor_key );
  }
}
