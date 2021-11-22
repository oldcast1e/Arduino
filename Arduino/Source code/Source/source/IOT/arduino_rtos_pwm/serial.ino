void showMenu() {
  Serial.println("\033[2J\033[H");
  Serial.println("1. Tilt Melody Enable/Disable");
  Serial.println("2. Auto Curtain Enable/Disable");
  Serial.println("3. Auto Fan Enable/Disable");
}

int tiltmelody_en = 0;
int autocurtain_en = 0;
int autofan_en = 0;

void vTaskSerial( void *pvParameters ) {
  Serial.begin(9600);

  showMenu();
  
  while(1) {
    if (Serial.available() > 0) {
      int userCmd = Serial.read();
  
      switch(userCmd) {
        case '1': 
          tiltmelody_en = !tiltmelody_en;
          if(tiltmelody_en==1) 
            xSemaphoreGive( tiltmelody_key );
          else if(tiltmelody_en==0) 
            while(xSemaphoreTake( tiltmelody_key, portMAX_DELAY)!=pdTRUE) { }    
          break;
        case '2': 
          autocurtain_en = !autocurtain_en;
          if(autocurtain_en==1) 
            xSemaphoreGive( autocurtain_key );
          else if(autocurtain_en==0) 
            while(xSemaphoreTake( autocurtain_key, portMAX_DELAY)!=pdTRUE) { }
          break; 
        case '3': 
          autofan_en = !autofan_en;
          if(autofan_en==1) 
            xSemaphoreGive( autofan_key );
          else if(autofan_en==0) 
            while(xSemaphoreTake( autofan_key, portMAX_DELAY)!=pdTRUE) { }
          break;
        default: break;
      }
    }
    
    vTaskDelay( 100 / portTICK_PERIOD_MS );    
  }
}
