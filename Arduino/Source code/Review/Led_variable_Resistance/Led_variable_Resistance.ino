const int led = 3;
const int vr = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(vr,INPUT);

  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  int n = analogRead(vr)/4;
  analogWrite(led,n);

  Serial.println(n);
  delay(100);

}
