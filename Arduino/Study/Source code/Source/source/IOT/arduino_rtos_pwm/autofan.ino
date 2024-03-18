const int analogInPin = A1;
const int fanOutPin = 6;
int tSensorValue = 0; 
int outputValue = 0; 

void vTaskFan( void *pvParameters ) {
  while(1) {
    while(xSemaphoreTake( autofan_key, portMAX_DELAY )!=pdTRUE) { }  

    tSensorValue = analogRead(analogInPin);
    outputValue = map(tSensorValue, 0, 1023, 0, 255);
    analogWrite(fanOutPin, outputValue);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    xSemaphoreGive( autofan_key );
  }
}
