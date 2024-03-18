void showMenu() {
  Serial.print("1. Potentiomter Led Brightness Enable/Disable\n\r");
  Serial.print("2. Tmperature sensor Led Blink Enable/Disable\n\r");
  Serial.print("3. Photo Sensor RGB Led On/Off Enable/Disable\n\r");
  Serial.print("4. Distance Sensor RGB Led Brighness Enable/Disable\n\r");
}

int potentiometer_en = 1;
int tmp36sensor_en = 1;
int photosensor_en = 1;
int distancesensor_en = 1;

void vTaskSerial( void *pvParameters ) {
  Serial.begin(9600);

  showMenu();
  
  while(1) {
    if (Serial.available() > 0) {
      int userCmd = Serial.read();
  
      switch(userCmd) {
        case '1': 
          potentiometer_en = !potentiometer_en;    
          if(potentiometer_en==1) 
            xSemaphoreGive( potentiometer_key );
          else if(potentiometer_en==0) 
            while(xSemaphoreTake( potentiometer_key, portMAX_DELAY) != pdTRUE) { }
          break;
        case '2': 
          tmp36sensor_en = !tmp36sensor_en;    
          if(tmp36sensor_en==1) 
            xSemaphoreGive( tmp36sensor_key );
          else if(tmp36sensor_en==0) 
            while(xSemaphoreTake( tmp36sensor_key, portMAX_DELAY) != pdTRUE) { }
          break; 
        case '3': 
          photosensor_en = !photosensor_en;   
          if(photosensor_en==1) 
            xSemaphoreGive( photosensor_key );
          else if(photosensor_en==0) 
            while(xSemaphoreTake( photosensor_key, portMAX_DELAY) != pdTRUE) { }
          break;  
        case '4': 
          distancesensor_en = !distancesensor_en;    
          if(distancesensor_en==1) 
            xSemaphoreGive(distancesensor_key );
          else if(distancesensor_en==0) 
            while(xSemaphoreTake( distancesensor_key, portMAX_DELAY) !=pdTRUE) { }
          break;
        default: break;
      }
    }
    
    vTaskDelay( 100 / portTICK_PERIOD_MS );    
  }
}
