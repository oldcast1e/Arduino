
int tmp36sensorPin = A1; 
int tmp36ledPin = 13;    
int tmp36sensorValue = 0;

void vTaskTmp36sensor( void *pvParameters ) {
 
  pinMode(tmp36ledPin, OUTPUT);

  while(1) {
    while(xSemaphoreTake( tmp36sensor_key, portMAX_DELAY) != pdTRUE) { }
    
    tmp36sensorValue = analogRead(tmp36sensorPin);
    
    digitalWrite(tmp36ledPin, HIGH);    
    vTaskDelay(tmp36sensorValue / portTICK_PERIOD_MS);
   
    digitalWrite(tmp36ledPin, LOW);  
    vTaskDelay(tmp36sensorValue / portTICK_PERIOD_MS);
    
    xSemaphoreGive( tmp36sensor_key );
  }
}
