const int RGB[3] = {22, 24, 26};
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
int prv3 = 0;
int duration3 = 1000;
int colval = 0;

void RGB_setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(RGB[i], OUTPUT);
  }
//  Serial.begin(115200);
}

void RGB_loop() {

  unsigned int ct3 = millis();
  if (ct3 - prv3 >= duration3) {
    prv3 = ct3;
    if (colval >= 8) colval = 0; 
        for(int i=0;i<3;i++){
          digitalWrite(RGB[i],color[colval][i]==1?HIGH:LOW);
        }
//        Serial.println(colval);
    colval ++;

  }

}
