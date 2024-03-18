const int t = 9;
const int e = 10;

void setup() {

  pinMode(t,OUTPUT);
  pinMode(e,INPUT);

  Serial.begin(115200);
}

void loop() {
  
digitalWrite(t,LOW);
delayMicroseconds(2);

digitalWrite(t,HIGH);
delayMicroseconds(10);
digitalWrite(t,LOW);

long d = pulseIn(e,HIGH);
long s = d/58;

Serial.print(d);
Serial.println(" cm");



}
