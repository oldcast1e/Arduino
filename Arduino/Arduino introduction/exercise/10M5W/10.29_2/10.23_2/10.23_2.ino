const int L = 13;
const int b = 2;

void setup() {
 
Serial.begin(115200);
pinMode(b,INPUT);
pinMode(L,OUTPUT);
}

void loop() {
 
 int d = digitalRead(b);
 Serial.println(d);
 digitalWrite(L,d);
}
