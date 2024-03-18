void showMenu_1() {  
  Serial1.println("\033[2J");
  Serial1.println("\033[H");
  Serial1.println("1. Tilt Melody Enable/Disable ");
  Serial1.println("2. Auto Curtain Enable/Disable");
  Serial1.println("3. Auto Fan Enable/Disable");
}

void serial_1_setup() {  
  Serial1.begin(9600);
 
  showMenu_1();
}

void serial_1_loop() {
  if (Serial1.available() > 0) {
    int userCmd = Serial1.read();

    switch(userCmd) {
      case '1': melody_en = !melody_en;        break;
      case '2': autocurtain_en = !autocurtain_en;  break;
      case '3': autofan_en = !autofan_en;          break;
      default: break;
    }
  }
}
