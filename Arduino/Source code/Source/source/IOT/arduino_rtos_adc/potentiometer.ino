const int pot_analogInPin = A0;
const int pot_analogOutPin = 11;

int pot_sensorValue = 0; 
int pot_outputValue = 0;

void vTaskPotentiometer( void *pvParameters ) {
  
  while(1) {
    while(xSemaphoreTake( potentiometer_key, portMAX_DELAY)!=pdTRUE) { }

    pot_sensorValue = analogRead(pot_analogInPin);
    pot_outputValue = map(pot_sensorValue, 0, 1023, 0, 255);
    analogWrite(pot_analogOutPin, pot_outputValue);    

    vTaskDelay(2 / portTICK_PERIOD_MS);
    
    xSemaphoreGive( potentiometer_key );
  }
}
