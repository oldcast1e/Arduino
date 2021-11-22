unsigned long tp = 0;
unsigned long td = 1000;

void setup() {
 Serial.begin(115200);
 
}

void loop() {
  // put your main code here, to run repeatedly:
 unsigned long tn = millis();
 if(tn-tp >= td){
  tp = tn ;
  Serial.println(tn);
 }

}
