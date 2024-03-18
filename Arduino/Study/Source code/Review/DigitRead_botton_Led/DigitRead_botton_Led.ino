const int b = 2;
const int l = 3;

int cnt = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(b,INPUT);
  pinMode(l,OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  int n = digitalRead(b);
  if(n==1){
    cnt = (cnt==1?cnt=0:cnt=1);
    delay(100);
  }
  

  if(cnt==1) digitalWrite(l,HIGH);
  else digitalWrite(l,LOW);

}
