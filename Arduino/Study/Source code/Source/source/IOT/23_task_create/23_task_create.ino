#include <Arduino_FreeRTOS.h>
#include <semphr.h>

void setup() {
  Serial.begin(115200);

  xTaskCreate( t1_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  xTaskCreate( t2_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );

  vTaskStartScheduler();
  
  while(true) ;
}

void t1_main( void *arg ) {
	
  while(true) {    
	
	Serial.print("| \n");    
	
  }
}

void t2_main( void *arg ) {
	
  while(true) {    
	
	Serial.print(" |\n");
	
  }
}

void loop() {}