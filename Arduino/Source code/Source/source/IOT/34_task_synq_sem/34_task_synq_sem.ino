#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t println_key = NULL;

void setup() {
  Serial.begin(115200);

  vSemaphoreCreateBinary( println_key );

  xTaskCreate( t1_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  xTaskCreate( t2_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );

  vTaskStartScheduler();
  
  while(true) ;
}

void t1_main( void *arg ) {
  
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
  
  while(true) {
	
	if(xSemaphoreTake( println_key, xBlockTime )==pdTRUE) {
	  
	  Serial.print("| \n");
	  
	  xSemaphoreGive( println_key );
	}
  }
}

void t2_main( void *arg ) {
  
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
  
  while(true) {
	
	if(xSemaphoreTake( println_key, xBlockTime )==pdTRUE) {
	  
	  Serial.print(" |\n");
	  
	  xSemaphoreGive( println_key );
	}
  }
}

void loop() {}