const int L = 10;

void setup() {
  
pinMode(L,OUTPUT);
Serial.begin(115200);

}

void loop(){

if(Serial.available()){

  int u= Serial.read();
 switch(u){

  case '0' :
  analogWrite(L,0*25);
  break;

  case '1' :
  analogWrite(L,1*25);
  break;

  case '2' :
  analogWrite(L,2*25);
  break;
  
  case '3' :
  analogWrite(L,3*25);
  break;

  case '4' :
  analogWrite(L,4*25);
  break;

  case '5' :
  analogWrite(L,5*25);
  break;

  case '6' :
  analogWrite(L,6*25);
  break;

  case '7' :
  analogWrite(L,7*25);
  break;

  case '8' :
  analogWrite(L,8*25);
  break;
  
  case '9' :
  analogWrite(L,9*25);
  break;

  default : break;
  
 }
 
}


}
