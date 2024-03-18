float h(int x,float y,float z){

  return (x+y+z)/3;
}


int x = 90;
float y = 91.2;
float z = 95;

float R = h(x,y,z);

void setup(){

  Serial.begin(115200);
 
  Serial.print("당신의 성적의 평균은: ");
  Serial.println(R);
  
}

void loop(){
  
}
