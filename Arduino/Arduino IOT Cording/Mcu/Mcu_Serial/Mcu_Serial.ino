const int bt = D3;
int prv = 0;
int duration = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(bt,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int ct = millis();
  if(ct - prv >= duration){
    prv = ct;
    int bts = digitalRead(bt);
     Serial.println(bts);
  }
  

}
