void setup(){

  Serial.begin(115200);
  blink_setup();
//  fading_setup();
}

void loop(){

  blink_loop();
//  fading_loop();
}
