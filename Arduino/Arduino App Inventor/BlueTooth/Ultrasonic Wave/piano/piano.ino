# include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9,10);

int E = 6;
int T = 7;

void setup(){

  pinMode(E,INPUT);
  pinMode(T,OUTPUT);

  btS.begin(9600);
}

void loop(){

  digitalWrite(T,HIGH);
  delayMicroseconds(10);
  digitalWrite(T,LOW);

  unsigned long D = pulseIn(E,HIGH);

  float d = ((34000*D)/1000000)/2;

  if(d <=5 && d <10) btS.println("do"); 
  else if(d <=10 && d <15) btS.println("le"); 
  else if(d <=20 && d <25) btS.println("mi"); 
  else if(d <=30 && d <35) btS.println("fa"); 
  else if(d <=40 && d <45) btS.println("sol"); 
  else if (d <= 50 && 55 < d) btS.println("ra");
  else if (d <= 60 && 65 < d) btS.println("si");
  else if (d <= 70 && 75 < d) btS.println("Do");
  else btS.println("OUT");  

  delay(100);
  
}
