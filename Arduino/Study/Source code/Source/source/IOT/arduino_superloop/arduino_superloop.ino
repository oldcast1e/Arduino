#define Serial Serial2

int blink_en = 1;
int fading_en = 1;
int blinkRGB_en = 1;
int fadingRGB_en = 1;

void setup() {
  blink_setup();
  fading_setup();
  blinkRGB_setup();
  fadingRGB_setup();
  
  serial_setup();
//  serial_1_setup();
//  serial_2_setup();
}

void loop() { 
  if(blink_en == 1) 
    blink_loop();
  if(fading_en == 1)
    fading_loop();
  if(blinkRGB_en == 1)
    blinkRGB_loop();
  if(fadingRGB_en == 1)
    fadingRGB_loop();
    
  serial_loop();
//  serial_1_loop();
//  serial_2_loop();
}
