#define Serial Serial1
int blink_en = 0;
int RGBblink_en = 0;
int fading_en = 0;
int fadingRGB_en = 0;


void setup(){
  
  blink_setup();
  fading_setup();
  RGBblink_setup();
  fadingRGB_setup();

  serial_setup();
}

void loop(){

  if (blink_en == 1)
    blink_loop();
    
  if (fading_en == 1)
    fading_loop();
    
  if (RGBblink_en == 1)
    RGBblink_loop();
    
  if (fadingRGB_en == 1)
    fadingRGB_loop();

  serial_loop();
}
