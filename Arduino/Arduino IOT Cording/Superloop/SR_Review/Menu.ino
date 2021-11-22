int supkey[4] = {0};
void menu_setup(){
  Serial.begin(9600);
  Serial.println("\033[2J\033[H");
  Serial.println("1. LED blink Enable/Disable");
  Serial.println("2. LED fading Enable/Disable");
  Serial.println("3. RGB blink Enable/Disable");
  Serial.println("4. RGB fading Enable/Disable");
  
}

void menu_loop(){

  if(Serial.available()){
    char u = Serial.read();
    if(u=='1')supkey[0] = !supkey[0];
    else if(u=='2')supkey[1] = !supkey[1];
    else if(u=='3')supkey[2] = !supkey[2];
    else if(u=='4')supkey[3] = !supkey[3];   
  }
  if(supkey[0] == 1) blink_loop();
  if(supkey[1] == 1) fading_loop();
  if(supkey[2] == 1) RGB_loop();
  if(supkey[3] == 1) RGB_fading_loop();
  
}
