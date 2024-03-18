int RGB_1[3] = {44,45,46};
int RGB_state[3] = {LOW,LOW,LOW};

long RGB_pM[3] = {0,};
long RGB_dt[3] = {1000,2000,3000};


void setup() {
  // put your setup code here, to run once:
  for(int n =0;n<=2;n++){
    pinMode(RGB_1[n],OUTPUT);
  }

}

void loop() {

  unsigned long n = millis();


  for(int i=0;i<3;i++){

    if(n - RGB_pM[i]>=RGB_dt[i]){
      RGB_pM[i] = n;

      if(RGB_state[i]==LOW){
        RGB_state = HIGH;
      }
      else {RGB_state[i] = HIGH;}
      digitalWrite(RGB_1[i],RGB_state[i]);
    }
  }

}
