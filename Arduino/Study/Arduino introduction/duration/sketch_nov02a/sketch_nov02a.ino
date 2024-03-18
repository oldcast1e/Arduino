void setup() {
 
Serial.begin(115200);

}

void loop() {
if (Serial.available()){


 char k = Serial.read();
 int t = k*2;
 Serial.println(k); 
}
}
