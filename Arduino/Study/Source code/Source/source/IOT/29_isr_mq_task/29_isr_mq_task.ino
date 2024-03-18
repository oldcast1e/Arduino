#include <Arduino_FreeRTOS.h>
#include <semphr.h>

QueueHandle_t xQueueButton = NULL;

void setup() { 
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(2), buttonIsr, RISING);  

  xQueueButton = xQueueCreate( 16, sizeof( int ) );

  xTaskCreate(tbutton_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);   

  vTaskStartScheduler();
  
  while(true) ;
}

void  buttonIsr( void ) {
  
  static int DevRegister = 0;  
  int DataToSend = 0;
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  DevRegister ++;
  
  DataToSend = DevRegister;
  
  Serial.print("isr(");
  Serial.print(DataToSend);
  Serial.print(") => ");
  
  xQueueSendFromISR(xQueueButton, &DataToSend, &xHigherPriorityTaskWoken); 

  if( xHigherPriorityTaskWoken ) {   
	taskYIELD();
  }
}

void tbutton_main( void *arg ) {

  int DataToReceive = 0;
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
  
  while(true) {
  
	  if(xQueueReceive(xQueueButton, &DataToReceive, xBlockTime)==pdTRUE) {

		noInterrupts();
		Serial.print("tbutton(");
		Serial.print(DataToReceive);
		Serial.print(")");
		Serial.println();
		interrupts();
	  }   
  }
}

void loop() {}