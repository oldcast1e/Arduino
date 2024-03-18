#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define BUF_SIZE 16
int buf[BUF_SIZE] = {0,};
int front = 0;
int rear = 0;
int how_many = 0;
SemaphoreHandle_t data_ready = NULL;

void setup() { 
  Serial.begin(115200);

  data_ready = xSemaphoreCreateCounting(BUF_SIZE, 0);

  xTaskCreate( t1_main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
  xTaskCreate( t2_main, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );

  vTaskStartScheduler();
  
  while(true) ;
}

void t1_main( void *arg ) {
  
  int DataToSend = 0;
  
  while(true) {

	vTaskDelay(1000 / portTICK_PERIOD_MS);

	DataToSend ++;

	noInterrupts();
	Serial.print("t1(");
	Serial.print(DataToSend);
	Serial.print(") => ");
	interrupts();

	noInterrupts();
	if(how_many<BUF_SIZE) {
	  buf[rear] = DataToSend;
	  rear++;
	  if(rear>=BUF_SIZE) rear = 0;
	  how_many++;
	}
	interrupts();  
	xSemaphoreGive(data_ready);
  }
}

void t2_main( void *arg ) {  
  
  int DataToReceive = 0;
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
  
  while(true) {
  
	if(xSemaphoreTake(data_ready, xBlockTime )==pdTRUE) {
	  noInterrupts();
	  if(how_many>0) {
		DataToReceive = buf[front];
		front++;
		if(front>=BUF_SIZE) front = 0;
		how_many--;        
	  }
	  interrupts();
  
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