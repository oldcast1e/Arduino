void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  

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
      cnt = 0;
      int num = atoi(str);
      if(0<= num && num <= 180) ms.write(num);
      for(int i=0;i<100;i++)str[i] = '\0';
      
    }
      
      
  }

}
