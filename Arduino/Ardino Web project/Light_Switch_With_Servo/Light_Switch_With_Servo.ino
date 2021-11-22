#include<Servo.h>

Servo ms;
char str[100] = {0};
int cnt = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ms.attach(A0);
  ms.write(0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    char u = Serial.read();
    
    if(u!='\n'){
       str[cnt] = u;
       cnt ++;
    } 
    else{
      
      int num = atoi(str);
      Serial.println(num);
      if(0<= num && num <= 180) ms.write(num);
      
      for(int i=0;i<100;i++)str[i] = '\0';
      cnt = 0;
      
    }
      
      
  }

}
