#include "pitches.h"

int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, 
  NOTE_G3,0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4,
  4, 4, 4, 4 
};

void vTaskTiltMelody( void *pvParameters ) {
  while(1) {
    while(xSemaphoreTake( tiltmelody_key, portMAX_DELAY)!=pdTRUE) { }
    
    while(xSemaphoreTake( xBinarySemaphoreTilt, portMAX_DELAY )!=pdTRUE) { }

    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000/noteDurations[thisNote];
      tone(8, melody[thisNote],noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      vTaskDelay(pauseBetweenNotes / portTICK_PERIOD_MS);
      noTone(8);
     }
     vTaskDelay(500 / portTICK_PERIOD_MS);
     
     xSemaphoreGive( tiltmelody_key ); 
  }
}

void vTiltInterruptHandler( void ) {
  xSemaphoreGiveFromISR( xBinarySemaphoreTilt, NULL );
}
