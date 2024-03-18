//millis함수 이용하기
const int L = 2;

int vc = LOW;
int nv = 0;
int dv = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(L,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  if (now - nv >= dv){
    nv = now;

    
    digitalWrite(L,vc =(vc == LOW?HIGH:LOW));
  }

}
