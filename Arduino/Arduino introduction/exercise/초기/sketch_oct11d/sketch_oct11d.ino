float h(float x, int y){
 return x +y;
}

void setup(){

  Serial.begin(115200);

  float x = 2.1;
  int y =1;
  
  float z = h(x,y);
  Serial.println(z);
}


void loop(){
  
}
