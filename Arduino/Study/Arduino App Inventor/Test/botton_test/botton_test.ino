const int b1= 7;
const int b2 = 6;
const int b3 = 5;

void setup() {
 pinMode(b1,INPUT);

 Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int k = digitalRead(b1);
  Serial.println(k);
}
