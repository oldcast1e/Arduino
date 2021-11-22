void serial_setup(){
  Serial.println("\033[2J\033[H");
  Serial.begin(9600);
  Serial.println("1. Led Blink Enable/Disable");
  Serial.println("2. RGB Blink Enable/Disable");
  Serial.println("3. Led Fading Enable/Disable");
  Serial.println("4. RGB Fading Enable/Disable");

  Serial.print("Your Command:");
}
void serial_loop(){

  if(Serial.available()>0){
    char u = Serial.read();
  

  switch(u){
    case '1': blink_en = !blink_en; break;
    case '3': RGBblink_en = !RGBblink_en; break;
    case '2': fading_en = !fading_en; break;
    case '4': fadingRGB_en = !fadingRGB_en; break;
    default: break;
    
  }
}
}
