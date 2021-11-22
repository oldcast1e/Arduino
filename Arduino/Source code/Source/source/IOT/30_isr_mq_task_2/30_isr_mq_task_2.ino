#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define BUF_SIZE 16
int buf[BUF_SIZE] = {0,};
int front = 0;
int rear = 0;
int how_many = 0;
SemaphoreHandle_t button_pressed = NULL;

void setup() { 
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(2), buttonIsr, RISING);  

  button_pressed = xSemaphoreCreateCounting(BUF_SIZE, 0);

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
  
  if(how_many<BUF_SIZE) {
	buf[rear] = DataToSend;
	rear++;
	if(rear>=BUF_SIZE) rear = 0;
	how_many++;
  }  
  xSemaphoreGiveFromISR(button_pressed, &xHigherPriorityTaskWoken);

  if( xHigherPriorityTaskWoken ) {   
	taskYIELD();
  }
}

void tbutton_main( void *arg ) {

  int DataToReceive = 0;
  const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
  
  while(true) {
  
	if(xSemaphoreTake(button_pressed, xBlockTime )==pdTRUE) {
	  noInterrupts();
	  if(how_many>0) {
		DataToReceive = buf[front];
		front++;
		if(front>=BUF_SIZE) front = 0;
		how_many--;        
	  }
	  interrupts();

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