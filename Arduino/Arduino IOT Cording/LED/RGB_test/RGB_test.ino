const int RGB[3] = {22,24,26};
const int color[8][3] = {

  {1, 0, 0}, //빨
  {1, 1, 0}, //노
  {0, 1, 0}, //초
  {0, 1, 1}, //하늘
  {0, 0, 1}, //파
  {1, 0, 1}, //보라
  {1, 1, 1}, //흰
  {0, 0, 0} //

};
void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<3;i++){
    pinMode(RGB[i],OUTPUT);
  }
//  digitalWrite(RGB[0],LOW);
//  digitalWrite(RGB[1],LOW);
//  digitalWrite(RGB[2],HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<8;i++){
    for(int j=0;j<3;j++){
      digitalWrite(RGB[j],color[i][j]);
      
    }
    delay(1000);
    
  }
  

}
