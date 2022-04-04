void setup() {
  // pinMode(13, OUTPUT);
  Serial.begin(9600);
//  Serial.print("#13P1200T1000\r\n");
  move();move();

}

void move(){
//
   Serial.print("#13P1000T500\r\n");
   delay(1000);
   Serial.print("#13P1500T500\r\n");
   delay(1000);
//   Serial.print("#11P1800T1000\r\n");
//   delay(1000);
//   Serial.print("#11P1500T1000\r\n");
//   delay(1000);
}

void loop() {


}
