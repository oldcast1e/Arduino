const int L1 = 9;
int lh_1 = 0;

const int L2 = 10;
int lh_2 = 0;

unsigned long tp_1 = 0;
unsigned long td_1 = 10;

unsigned long tp_2 = 0;
unsigned long td_2 = 20;

void setup() {
 Serial.begin(115200);
 pinMode(L1,OUTPUT);
 pinMode(L2,OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
 unsigned long tn_1 = millis();
 if(tn_1 -tp_1 >= td_1){
  tp_1 = tn_1 ;

  lh_1++;
  if(lh_1>=255) lh_1=0;
 analogWrite(L1,lh_1);
  
 }

 unsigned long tn_2 = millis();
 if(tn_2- tp_2 >= td_2){
  tp_2 = tn_2 ;

  lh_2 ++;
  if(lh_2 >=255) lh_2=0;
 analogWrite(L2,lh_2);
  
 }

}
