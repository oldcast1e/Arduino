void showMenu() {
  Serial.println("\033[2J\033[H");
  Serial.println("1. Potentiomter Led Brightness Enable/Disable");
  Serial.println("2. Tmperature sensor Led Blink Enable/Disable");
  Serial.println("3. Photo Sensor RGB Led On/Off Enable/Disable");
  Serial.println("4. Distance Sensor RGB Led Brighness Enable/Disable");
}

void serial_setup() {  
  Serial.begin(115200);
  
  showMenu();
}

void serial_loop() {
  if (Serial.available() > 0) {
    int userCmd = Serial.read();

    switch(userCmd) {
      case '1': potentiometer_en = !potentiometer_en;    break;
      case '2': tmp36sensor_en = !tmp36sensor_en;        break; 
      case '3': photosensor_en = !photosensor_en;        break;
      case '4': distancesensor_en = !distancesensor_en;  break;
      default: break;
    }
  }
}
