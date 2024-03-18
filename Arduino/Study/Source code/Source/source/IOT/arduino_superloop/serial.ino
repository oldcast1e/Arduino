void showMenu() {
  Serial.println("\033[2J\033[H");
  Serial.println("1. Led Blink Enable/Disable");
  Serial.println("2. Led Fading Enable/Disable");
  Serial.println("3. RGB Led Blink Enable/Disable");
  Serial.println("4. RGB Led Fading Enable/Disable");
}

void serial_setup() {  
  Serial.begin(115200);
  
  showMenu();
}

int userCmd = 0;

void serial_loop() {
  if (Serial.available() > 0) {
    userCmd = Serial.read();

    switch(userCmd) {
      case '1': blink_en = !blink_en;          break;
      case '2': fading_en = !fading_en;        break; 
      case '3': blinkRGB_en = !blinkRGB_en;    break;
      case '4': fadingRGB_en = !fadingRGB_en;  break;
      default: break;
    }
  }
}
