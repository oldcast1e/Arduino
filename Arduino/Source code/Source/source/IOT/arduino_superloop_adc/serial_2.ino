void serial_2_setup() {  
  Serial2.begin(115200);
}

void serial_2_loop() {
  if (Serial2.available() > 0) {
    int userCmd = Serial2.read();

    switch(userCmd) {
      case '1': potentiometer_en = !potentiometer_en;    break;
      case '2': tmp36sensor_en = !tmp36sensor_en;        break; 
      case '3': photosensor_en = !photosensor_en;        break;
      case '4': distancesensor_en = !distancesensor_en;  break;
      default: break;
    }
  }
}
