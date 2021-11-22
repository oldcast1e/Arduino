#define Serial Serial2

int potentiometer_en = 0;
int tmp36sensor_en = 0;
int photosensor_en = 0;
int distancesensor_en = 0;

void setup() {
  serial_setup();
//  serial_1_setup();  
//  serial_2_setup();
  potentiometer_setup();
  tmp36sensor_setup();
  photosensor_setup();
  distancesensor_setup();
}

void loop() {
  serial_loop();
//  serial_1_loop();
//  serial_2_loop();
  if(potentiometer_en == 1) 
    potentiometer_loop();
  if(tmp36sensor_en == 1) 
    tmp36sensor_loop();
  if(photosensor_en == 1) 
    photosensor_loop();
  if(distancesensor_en == 1) 
    distancesensor_loop();
}
