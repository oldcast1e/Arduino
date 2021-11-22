#define Serial Serial2

int melody_en = 1;
int autocurtain_en = 1;
int autofan_en = 1;

void setup() {
  serial_setup();
  serial_1_setup();
  serial_2_setup();
  melody_setup();
  autocurtain_setup();
  autofan_setup();
}

void loop() {
  serial_loop();   
  serial_1_loop();     
  serial_2_loop();  
  if(melody_en == 1)
    melody_loop();
  if(autocurtain_en == 1)
    autocurtain_loop();
  if(autofan_en == 1)
    autofan_loop();
}
