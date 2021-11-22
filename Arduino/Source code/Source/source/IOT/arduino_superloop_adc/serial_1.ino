void serial_1_setup() {  
  Serial1.begin(9600);
}

void serial_1_loop() {
  if (Serial1.available() > 0) {
    int userCmd = Serial1.read();

    switch(userCmd) {
      case '1': potentiometer_en = !potentiometer_en;    break;
      case '2': tmp36sensor_en = !tmp36sensor_en;        break; 
      case '3': photosensor_en = !photosensor_en;        break;
      case '4': distancesensor_en = !distancesensor_en;  break;
      default: break;
    }
  }
}
