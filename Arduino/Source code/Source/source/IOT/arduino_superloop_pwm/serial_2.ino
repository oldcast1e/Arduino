void showMenu_2() {  
  Serial2.println("\033[2J");
  Serial2.println("\033[H");
  Serial2.println("1. Tilt Melody Enable/Disable ");
  Serial2.println("2. Auto Curtain Enable/Disable");
  Serial2.println("3. Auto Fan Enable/Disable");
}

void serial_2_setup() {  
  Serial2.begin(115200);
 
  showMenu_2();
}

void serial_2_loop() {
  if (Serial2.available() > 0) {
    int userCmd = Serial2.read();

    switch(userCmd) {
      case '1': melody_en = !melody_en;        break;
      case '2': autocurtain_en = !autocurtain_en;  break;
      case '3': autofan_en = !autofan_en;          break;
      default: break;
    }
  }
}
