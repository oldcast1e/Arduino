int a = A0;
int L = 10;
void setup() {

 Serial.begin(115200);
}
void loop() {

 int r =analogRead(a);

 Serial.println(r);
 analogWrite(L,r/4);
}
