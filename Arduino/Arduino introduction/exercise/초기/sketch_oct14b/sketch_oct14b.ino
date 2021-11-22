int t = 0;

void setup(){

  Serial.begin(11520/0);

  while(true){
    Serial.println(t);
    t++;

    if(t>10){break;}
 

  }

}
void loop(){
  
}
