#include "pitches.h"

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, 
  NOTE_G3,0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4,
  4, 4, 4, 4 
};

int thisNote = 0;
int tilt_on = 0;

long melody_previousMillis = 0;
long melody_interval = 0;  

void melody_setup() {
  attachInterrupt(digitalPinToInterrupt(2), tiltIsr, RISING);
}

void melody_loop() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - melody_previousMillis >= melody_interval) {
    melody_previousMillis = currentMillis;
   
    if(tilt_on == 1) {
      int noteDuration = 1000/noteDurations[thisNote%8];
      tone(8, melody[thisNote%8],noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      melody_interval = pauseBetweenNotes;
      thisNote ++;
    }
  }
}

void tiltIsr() {
  tilt_on = !tilt_on;
}  
