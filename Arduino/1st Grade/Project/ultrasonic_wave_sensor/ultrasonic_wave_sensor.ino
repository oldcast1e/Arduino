const int tr = 10;
const int ec = 11;

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
 long D = pulseIn(ec,HIGH);
 long d = (D/2)/29.1;

 delay(100);
 Serial.print(d);
 Serial.println( "cm");


}
