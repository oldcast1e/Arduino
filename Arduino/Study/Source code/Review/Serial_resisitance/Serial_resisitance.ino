const int res = A0;
const int led = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(res,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int n = analogRead(res);
//  Serial.println(n);
  analogWrite(led,n/4);
  delay(50);

}
