void showMenu() {
  Serial.println("\033[2J\033[H");
  Serial.print("1. Led Blink Enable/Disable\n\r");
  Serial.print("2. Led Fading Enable/Disable\n\r");
  Serial.print("3. RGB Led Blink Enable/Disable\n\r");
  Serial.print("4. RGB Led Fading Enable/Disable\n\r");
}

int blink_en = 1;
int fading_en = 1;
int blinkRGB_en = 1;
int fadingRGB_en = 1;

void vTaskSerial( void *pvParameters ) { 
  Serial.begin(115200);

  showMenu();

  while(1) { 
    if (Serial.available() > 0) {
      int userCmd = Serial.read();
  
      switch(userCmd) {
        case '1': 
          blink_en = !blink_en;
          if(blink_en==1) xSemaphoreGive(blink_key);
          else if(blink_en==0) while(xSemaphoreTake(blink_key, portMAX_DELAY)!=pdTRUE) {}
          break;
        case '2': fading_en = !fading_en; 
          if(fading_en==1) 
            xSemaphoreGive( fading_key );
          else if(fading_en==0) 
            while(xSemaphoreTake( fading_key, portMAX_DELAY) != pdTRUE) { }
          break;
        case '3': blinkRGB_en = !blinkRGB_en;
          if(blinkRGB_en==1) {
            xSemaphoreGive( blinkRGBRed_key ); 
            xSemaphoreGive( blinkRGBGreen_key );
            xSemaphoreGive( blinkRGBBlue_key );
          } else if(blinkRGB_en==0) {
            while(xSemaphoreTake( blinkRGBRed_key, portMAX_DELAY) != pdTRUE) { }
            while(xSemaphoreTake( blinkRGBGreen_key, portMAX_DELAY) != pdTRUE) { }
            while(xSemaphoreTake( blinkRGBBlue_key, portMAX_DELAY) != pdTRUE) { }
          }
          break;
        case '4': fadingRGB_en = !fadingRGB_en;          
          if(fadingRGB_en==1) {
            xSemaphoreGive( fadingRGBRed_key ); 
            xSemaphoreGive( fadingRGBGreen_key );
            xSemaphoreGive( fadingRGBBlue_key );
          } else if(fadingRGB_en ==0) {
            while(xSemaphoreTake( fadingRGBRed_key, portMAX_DELAY) != pdTRUE) { }
            while(xSemaphoreTake( fadingRGBGreen_key, portMAX_DELAY) != pdTRUE) { }
            while(xSemaphoreTake( fadingRGBBlue_key, portMAX_DELAY) != pdTRUE) { }
          }
          break;
        default: break;
      }
    }
    
    vTaskDelay( 100 / portTICK_PERIOD_MS );
  }
}
