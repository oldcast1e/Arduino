const unsigned int L[7] = {3,4,5,6,7,8,9};

void setup() {
  
for(int x =0 ; x<7 ; x++){
pinMode(L[x],OUTPUT);
}

for(int x =0 ; x<7 ; x++){
    digitalWrite(L[x],HIGH);
}

}
void loop() {
  
}
