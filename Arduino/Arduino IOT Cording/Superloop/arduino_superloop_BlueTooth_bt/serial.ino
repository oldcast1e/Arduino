void showMenu(){
  Serial.println("\033[2J\033[H");
  Serial.println("1. Led Blink Enable/Disable");
  Serial.println("2. RGB Blink Enable/Disable");
  Serial.println("3. Led Fading Enable/Disable");
  Serial.println("4. RGB Fading Enable/Disable");

  Serial.print("Your Command:");
}

void serial_setup(){
  Serial.begin(115200);

  showMenu();
}
void serial_loop(){

  
}
