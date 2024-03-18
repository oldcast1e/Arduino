#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define Serial Serial2

SemaphoreHandle_t blink_key;
SemaphoreHandle_t fading_key;
SemaphoreHandle_t blinkRGBRed_key;
SemaphoreHandle_t blinkRGBGreen_key;
SemaphoreHandle_t blinkRGBBlue_key;
SemaphoreHandle_t fadingRGBRed_key;
SemaphoreHandle_t fadingRGBGreen_key;
SemaphoreHandle_t fadingRGBBlue_key;
SemaphoreHandle_t fadingButton_event;
SemaphoreHandle_t fadingRGBButton_event;

void setup() {
  attachInterrupt(digitalPinToInterrupt(2), vFadingButtonIsr, RISING);
  attachInterrupt(digitalPinToInterrupt(3), vFadingRGBButtonIsr, RISING);
       
  vSemaphoreCreateBinary(blink_key); 
  vSemaphoreCreateBinary(fading_key); 
  vSemaphoreCreateBinary(blinkRGBRed_key); 
  vSemaphoreCreateBinary(blinkRGBGreen_key);
  vSemaphoreCreateBinary(blinkRGBBlue_key);
  vSemaphoreCreateBinary(fadingRGBRed_key); 
  vSemaphoreCreateBinary(fadingRGBGreen_key);  
  vSemaphoreCreateBinary(fadingRGBBlue_key);
  vSemaphoreCreateBinary( fadingButton_event );
  xSemaphoreTake( fadingButton_event, 0 );
  vSemaphoreCreateBinary( fadingRGBButton_event );
  xSemaphoreTake( fadingRGBButton_event, 0 );   
  
  xTaskCreate(vTaskBlink, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  xTaskCreate(vTaskFading, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
  xTaskCreate(vTaskBlinkRed, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
  xTaskCreate(vTaskBlinkGreen, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  xTaskCreate(vTaskBlinkBlue, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
  xTaskCreate( vTaskFadingRed, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
  xTaskCreate( vTaskFadingGreen, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  xTaskCreate( vTaskFadingBlue, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );    
  xTaskCreate( vTaskSerial, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL ); 

  vTaskStartScheduler();
  
  while(1) ;
}

void loop() {}
