#include <Arduino_FreeRTOS.h>
#include <semphr.h>

const char * t1_arg = "| \n";
const char * t2_arg = " |\n";

void setup() {
  Serial.begin(115200);

  xTaskCreate( t_main, NULL, configMINIMAL_STACK_SIZE, (void *)t1_arg, 1, NULL ); 
  xTaskCreate( t_main, NULL, configMINIMAL_STACK_SIZE, (void *)t2_arg, 2, NULL );

  vTaskStartScheduler();
  
  while(true) ;
}

void t_main( void *arg ) {
  const char * t_arg = (const char *)arg;
  while(true) {    
	noInterrupts();
	Serial.print(t_arg);    
	interrupts();
	
	vTaskDelay( 250 / portTICK_PERIOD_MS );  
  }
}

void loop() {}