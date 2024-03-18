void showMenu() {
  Serial.println("\033[2J\033[H");
  Serial.println("1. Tilt Melody Enable/Disable");
  Serial.println("2. Auto Curtain Enable/Disable");
  Serial.println("3. Auto Fan Enable/Disable");
}

void serial_setup() {  
  Serial.begin(115200);
 
  showMenu();
}

void serial_loop() {
  if (Serial.available() > 0) {
    int userCmd = Serial.read();

    switch(userCmd) {
      case '1': melody_en = !melody_en;        break;
      case '2': autocurtain_en = !autocurtain_en;  break;
      case '3': autofan_en = !autofan_en;          break;
      default: break;
    }
  }
}
