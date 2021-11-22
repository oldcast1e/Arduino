#include <Arduino_FreeRTOS.h>
#include <semphr.h>

QueueHandle_t xQueueSerial = NULL;

void setup() {
  Serial.begin(115200);

  xQueueSerial = xQueueCreate( 16, sizeof( const char * ) );
  xTaskCreate( t1_serial, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );
  
  xTaskCreate( t1_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  xTaskCreate( t2_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );  

  vTaskStartScheduler();
  
  while(true) ;
}

void t1_serial( void *arg ) {

  const char * DataToReceive = NULL;
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );

  while(true) {
  
	if(xQueueReceive(xQueueSerial, &DataToReceive, xBlockTime)==pdTRUE) {
	
	  Serial.print(DataToReceive);    
	  
	}
  }  
}

void t1_main( void *arg ) {
  
  const char * DataToSend = "| \n";
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );

  while(true) {
	
	xQueueSend( xQueueSerial, &DataToSend, xBlockTime ); 
	
  }
}

void t2_main( void *arg ) {
  
  const char * DataToSend = " |\n";
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );

  while(true) {
	
	xQueueSend( xQueueSerial, &DataToSend, xBlockTime ); 
	
  }
}

void loop() {}