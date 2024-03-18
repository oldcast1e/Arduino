#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define Serial Serial1

SemaphoreHandle_t potentiometer_key = NULL;
SemaphoreHandle_t tmp36sensor_key = NULL;
SemaphoreHandle_t photosensor_key = NULL;
SemaphoreHandle_t distancesensor_key = NULL;

void setup() {
  vSemaphoreCreateBinary( potentiometer_key ); 
  vSemaphoreCreateBinary( tmp36sensor_key ); 
  vSemaphoreCreateBinary( photosensor_key ); 
  vSemaphoreCreateBinary( distancesensor_key ); 
  
  xTaskCreate(vTaskSerial, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL ); 
  xTaskCreate(vTaskPotentiometer, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
  xTaskCreate(vTaskTmp36sensor, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  xTaskCreate(vTaskPhotosensor, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  xTaskCreate(vTaskDistancesensor, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 

  vTaskStartScheduler();
  
  while(1) ;
}

void loop() {}
