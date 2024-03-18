#include <Servo.h>

Servo myservo;
int potpin = A0;
int val;

void vTaskCurtain( void *pvParameters ) {

  myservo.attach(9);

  while(1) {
    while(xSemaphoreTake( autocurtain_key, portMAX_DELAY )!=pdTRUE) { } 

    val = analogRead(potpin);
    val = map(val, 0, 1023, 0, 180);
    myservo.write(val);
    vTaskDelay(15 / portTICK_PERIOD_MS);

    xSemaphoreGive( autocurtain_key );
  }
}
