const int LED1 = 7;
const int LED2 = 5;

int dra1 = 1000,dra2 = 100;
int prv1 = 0,prv2=0;

bool lst1 = LOW;

int led2cnt = 0;
int led2prv = 0;

//초기값 주기값 이전값

void lf1(){

  unsigned int ct = millis();
  if(ct-prv1>=dra1){
    prv1 = ct;

    digitalWrite(LED1,lst1);
    lst1 = (lst1==HIGH?LOW:HIGH);
  }
}

void lf2(){

  unsigned ct = millis();
  if(ct-prv2>=dra2){
    prv2 = ct;

    if(led2cnt==0){
      if(led2prv == 255){
        led2cnt = 1;
      }
      else if(led2prv<256) led2prv += 5;
    }
    else if(led2cnt==1){
      if(led2prv == 0){
        led2cnt = 0;
      }
      if(led2prv>0) led2prv -= 5;
    }
    analogWrite(LED2,led2prv);
    Serial.println(led2prv);
    

    
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  lf1();
  lf2();

}
