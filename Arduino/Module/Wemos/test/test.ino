void setup() {
 Serial.begin(112500);
 pinMode(2, OUTPUT);
 vTaskDelay(1000 / portTICK_PERIOD_MS);
 xTaskCreate(task1,"task1", 2048, NULL,1,NULL);
 xTaskCreate(task2,"task2", 2048, NULL,1,NULL); 
}
void loop() {
 vTaskDelay(1000 / portTICK_PERIOD_MS);
}
void task1( void * parameter )
{
  while(1) {
   Serial.println("Hello World!");
   vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void task2( void * parameter)
{
  while(1) {
     digitalWrite(2, HIGH);
     vTaskDelay(500 / portTICK_PERIOD_MS);
     digitalWrite(2, LOW);
     vTaskDelay(500 / portTICK_PERIOD_MS);
  } 
}