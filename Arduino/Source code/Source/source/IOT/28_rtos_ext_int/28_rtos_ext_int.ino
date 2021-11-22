#include <Arduino_FreeRTOS.h>
#include <semphr.h>

void setup() {
  Serial.begin(115200);
  
  attachInterrupt(digitalPinToInterrupt(2), buttonIsr, RISING); 
  
  xTaskCreate( tbutton_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL ); 
  
  vTaskStartScheduler();
  
  while(true) ;
}

void  buttonIsr( void ) {
	
  noInterrupts();
  Serial.print(" >\n");
  interrupts(); 
  
}

void tbutton_main( void *arg ) { 
 
  while(true) {  
  
	noInterrupts();
	Serial.print("| \n"); 
	interrupts();
	
	vTaskDelay( 100 / portTICK_PERIOD_MS );
	
  }
}

void loop() {}