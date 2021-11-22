const int L = 13;

int on_off = 0;

unsigned long tp=0;
unsigned td =500;

void setup() {

  pinMode(L,OUTPUT);

}

void loop() {

 unsigned long tn = millis();
 if(tn - tp>= td){
  tp = tn;

  on_off++;
  if(on_off>1) on_off =0;
  digitalWrite(L,on_off);
 }

}
