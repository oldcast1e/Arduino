const int ec = 2;
const int tr = 3;

void setup() {

 pinMode(tr,OUTPUT);
 pinMode(ec,INPUT);

 Serial.begin(9600);
}

void loop() {
 digitalWrite(tr,LOW);
 delayMicroseconds(2);
 
 digitalWrite(tr,HIGH);
 delayMicroseconds(10);
 
 digitalWrite(tr,LOW);
 
 long Distance = (pulseIn(ec,HIGH)/2)/29.1;

 delay(100);
 Serial.print(Distance);
 Serial.println( "cm");


}