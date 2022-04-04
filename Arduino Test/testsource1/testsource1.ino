void setup() {
  // pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.print("#11P1500T1000\r\n");

}

void move(){

   Serial.println("#11P1200T3000\r\n");
   delay(1000);
   Serial.print("#11P1500T3000\r\n");
   delay(1000);
   Serial.println("#11P1800T3000\r\n");
   delay(1000);
   Serial.print("#11P1500T3000\r\n");
   delay(1000);
}

void loop() {


}
