unsigned long tp = 0;
unsigned long td = 1000;

unsigned long tp_2 = 0;
unsigned long td_2 = 500;

void setup() {
 Serial.begin(115200);
 
}

void loop() {
  // put your main code here, to run repeatedly:
 unsigned long tn = millis();
 if(tn-tp >= td){
  tp = tn ;
  Serial.print("    ");
  Serial.println(tn);
 }

 unsigned long tn_2 = millis();
 if(tn_2-tp_2 >= td_2){
  tp_2 = tn_2 ;
  Serial.println(tn_2);
 }

}
