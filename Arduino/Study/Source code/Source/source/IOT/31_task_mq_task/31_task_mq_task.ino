#include <Arduino_FreeRTOS.h>
#include <semphr.h>

QueueHandle_t xQueueTask = NULL;

void setup() { 
  Serial.begin(115200);

  xQueueTask = xQueueCreate( 16, sizeof( int) );

  xTaskCreate( t1_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
  xTaskCreate( t2_main, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );

  vTaskStartScheduler();
  
  while(true) ;
}

void t1_main( void *arg ) {
  
  int DataToSend = 0;
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
  
  while(true) {

	vTaskDelay(1000 / portTICK_PERIOD_MS);

	DataToSend ++;

	noInterrupts();
	Serial.print("t1(");
	Serial.print(DataToSend);
	Serial.print(") => ");
	interrupts();
	
	xQueueSend(xQueueTask, &DataToSend, xBlockTime);
  }
}

void t2_main( void *arg ) {  
  
  int DataToReceive = 0;
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
  
  while(true) {
  
	if(xQueueReceive(xQueueTask, &DataToReceive, xBlockTime)==pdTRUE) {
  
	  noInterrupts();
	  Serial.print("t2(");
	  Serial.print(DataToReceive);
	  Serial.print(")");
	  Serial.println();
	  interrupts();
	}    
  }
}

void loop() {}