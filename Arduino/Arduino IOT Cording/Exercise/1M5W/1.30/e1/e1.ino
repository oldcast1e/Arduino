//void setup(){
//  Serial.begin(115200);
//  Serial.print("Hello World!");
//}
//
//void loop(){
//
//  
//}

//millis 함수 이용

int k =0;
int t = 1000;

void setup(){
  Serial.begin(115200);
   
}


void loop(){
  unsigned int now = millis(); 
  if (now >= t){
    
    Serial.print(k);
    Serial.println("초");

    t += 1000;
    k+=1;
    
  }
}
