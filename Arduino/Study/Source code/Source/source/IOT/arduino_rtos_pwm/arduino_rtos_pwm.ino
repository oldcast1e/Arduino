#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define Serial Serial1

SemaphoreHandle_t xBinarySemaphoreTilt;

SemaphoreHandle_t tiltmelody_key;
SemaphoreHandle_t autocurtain_key;
SemaphoreHandle_t autofan_key;

void setup() { 
  attachInterrupt(digitalPinToInterrupt(2), vTiltInterruptHandler, RISING); 
  vSemaphoreCreateBinary( xBinarySemaphoreTilt ); 
  xSemaphoreTake( xBinarySemaphoreTilt, 0);
  
  vSemaphoreCreateBinary( tiltmelody_key ); 
  vSemaphoreCreateBinary( autocurtain_key ); 
  vSemaphoreCreateBinary( autofan_key ); 
  xSemaphoreTake( tiltmelody_key, 0);
  xSemaphoreTake( autocurtain_key, 0);
  xSemaphoreTake( autofan_key, 0);
  
  xTaskCreate(vTaskSerial, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );
  xTaskCreate(vTaskTiltMelody, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  xTaskCreate(vTaskCurtain, NULL, configMINIMAL_STACK_SIZE*2, NULL, 1, NULL ); 
  xTaskCreate(vTaskFan, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 

  vTaskStartScheduler();
  
  while(1) ;
}

void loop() {}
