# include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9,10);

const int b1= 7;
const int b2 = 6;
const int b3 = 5;

bool s1 = false;
bool s2 = false;
bool s3 = false;

void F1(){

  if(s1){
    btS.print("R");
    Serial.println("R");
    delay(400);
  }
}

void F2(){

  if(s2){
    btS.print("Y");
    Serial.println("Y");
    delay(400);
  }
}

void F3(){

  if(s3){
    btS.print("G");
    Serial.println("G");
    delay(400);
  }
}

void setup(){

  pinMode(b1,INPUT);
  pinMode(b1,INPUT);
  pinMode(b1,INPUT);

  Serial.begin(9600);
  btS.begin(9600);
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

// 이렇게하면 스위치 OFF의 입력을 받을 수 없으므로 옳바르지않은 코드임.
