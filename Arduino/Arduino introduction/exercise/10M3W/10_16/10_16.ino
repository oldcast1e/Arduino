const int L[8] ={2,3,4,5,6,7,8,9};

void setup(){

for(int x=0;x<=8 ;x++){
  pinMode(L[x],OUTPUT);
 

}

}

void loop(){

  
for(int x=0;x<=8 ;x++){
  digitalWrite(L[x],LOW);
  delay(50);
 
}

for(int x=0;x<=8 ;x++){
  digitalWrite(L[x],HIGH
  );
  delay(50);
 
}
  
}
