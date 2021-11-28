const int b1= 4;
const int b2 = 3;
const int b3 = 2;

bool s1 = false;
bool s2 = false;
bool s3 = false;

void F1(){

  if(s1){
    Serial1.println("b1");
    Serial.println("Red");
    delay(400);
  }
}
//App Inventor
void F2(){

  if(s2){
    Serial1.write("b2");
    Serial.println("Yellow");
    delay(400);
  }
}

void F3(){

  if(s3){
    Serial1.write("b3");
    Serial.println("Green");
    delay(400);
  }
}

void setup(){

  pinMode(b1,INPUT);
  pinMode(b1,INPUT);
  pinMode(b1,INPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
  
}

void loop(){
  int a1 = digitalRead(b1);
  int a2 = digitalRead(b2);
  int a3 = digitalRead(b3);
 
  if(a1==1){
    s1=(s1==false)?true:false;
    F1();
  }
  if(a2==1){
    s2=(s2==false)?true:false;
    F2();
  }
  if(a3==1){
    s3=(s3==false)?true:false;
    F3();
  }  
}
