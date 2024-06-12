// ESP8266 SoftwareSerial
// https://circuits4you.com/2016/12/14/software-serial-esp8266/

#include <SoftwareSerial.h>

// pins Rx GPIO14 (D5) and Tx GPIO 12 (D6)
SoftwareSerial swSer(14, 12);  

void setup() {
  Serial.begin(115200);   //Initialize hardware serial with baudrate of 115200
  swSer.begin(115200);    //Initialize software serial with baudrate of 115200
  Serial.println("\nESP8266 Software serial test started");
}

void loop() {
  while (swSer.available() > 0) {  //wait for data at software serial
    Serial.write(swSer.read()); //Send data recived from software serial to hardware serial    
  }
  while (Serial.available() > 0) { //wait for data at hardware serial
    swSer.write(Serial.read());     //send data recived from hardware serial to software serial
  }
}