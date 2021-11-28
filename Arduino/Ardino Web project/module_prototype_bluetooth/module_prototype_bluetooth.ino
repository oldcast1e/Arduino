#include <Servo.h>
#include <DHT.h>

/*조도 센 관련*/
const int light = A0;// 조도 센서
int light_status = false,key = 0;

/*초음파 관련*/
const int tr = 10;//초음파
const int ec = 11;
int tot_person = 0;//사람수서

/*소리감지 센서*/
const int SOUND_SENSOR_PIN = A15;
int sensorValue;

/*초음파 관련*/
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN,DHTTYPE);

int mq3 = A7;
int red = 3;

/*온습도*/
long pwm_ht = 0;//초기값 설정(마일값과 비교할 이전 시간_주어진 시간간격 차이 시 시간 증가)
long interval_ht = 10000;//시간 간격
/*조도*/
long pvm_light = 0;//초기값 설정(마일값과 비교할 이전 시간_주어진 시간간격 차이 시 시간 증가)
long interval_light = 300;//시간 간격
/*알코올*/
long pwm_ac = 0;//초기값 설정(마일값과 비교할 이전 시간_주어진 시간간격 차이 시 시간 증가)
long interval_ac = 10000;//시간 간격

/*소리감지 센서*/
long pwm_sd = 0;//초기값 설정(마일값과 비교할 이전 시간_주어진 시간간격 차이 시 시간 증가)
long interval_sd = 100;//시간 간격



Servo ms;

int Function_Ultra(int tr,int ec){

  int person_num = 0;
  digitalWrite(tr,LOW);
  delayMicroseconds(2);
  
  digitalWrite(tr,HIGH);
  
  delayMicroseconds(10);
  digitalWrite(tr,LOW);
  long uncalculation = pulseIn(ec,HIGH);
  long result = (uncalculation/2)/29.1;

  delay(1000);

  if(result < 65){
     return 1;
//    delay(3000);
  }
  else return 0;
}

int Function_Light(int val){

    unsigned long crmil_light = millis();
    if((crmil_light - pvm_light) >= interval_light){//현재 마일값과 이전 시간값과의 차이가 시간 간격일 때
        pvm_light = crmil_light;//이전 시간 업데이트 - 시간간격 맞추기
        //수행할 작업 코드
        if(val > 230){ light_status  = false;key == 1 ? 0: 1;}
        else {light_status  = true;key == 1 ? 0: 1;}

        if(light_status == 1 && key == 0){ 
            Serial.println("Light Status is ON");;
            Serial1.println("ON");key = 1 ; return 1;}
        else if(light_status == 0 && key == 1){
            Serial.println("Light Status is OFF"); ;
            Serial1.println("OFF");key = 0; return 0;}
        else return 3;


    }
    
}

void Function_Alcohol(){
  unsigned long crmil_ac = millis();
  if((crmil_ac - pwm_ac) >= interval_ac){//현재 마일값과 이전 시간값과의 차이가 시간 간격일 때
    pwm_ac = crmil_ac;//이전 시간 업데이트 - 시간간격 맞추기
    int val = analogRead(mq3);
    if(val >=  0) Serial1.println("Acl1");
    else if(val >=  200) Serial1.println("Acl2");
    else if(val >=  400){
      digitalWrite(red,HIGH);
      Serial1.println("Acl3");
    }
    Serial.print("recent Alcohol:");
    Serial.println(val);

  }
  
}

void Function_ht(){
  unsigned long crmil_ht = millis(); 
  if((crmil_ht - pwm_ht) >= interval_ht){//현재 마일값과 이전 시간값과의 차이가 시간 간격일 때
    pwm_ht = crmil_ht;//이전 시간 업데이트 - 시간간격 맞추기
    //수행할 작업 코드
    double h = dht.readHumidity();
    double t = dht.readTemperature();

    if(0<=h && h <30) Serial1.println("S");
    else if(30 <=h && h<60) Serial1.println("SC");
    else if(60<=h && h<90) Serial1.println("CL");
    else if(90<=h) Serial1.println("R");

    if(0<=h && h <30) Serial.println("S");
    else if(30 <=h && h<60) Serial.println("SC");
    else if(60<=h && h<90) Serial.println("CL");
    else if(90<=h) Serial.println("R");
    /*시리얼*/
    Serial1.print("<");
    Serial1.print(h);
    Serial1.print("(");
    Serial1.println(t);
    /*시리얼*/
    Serial.print("humidity:");
    Serial.println(h);
    Serial.print("temperature:");
    Serial.println(t);
    
  }
}

void Function_sd(){
  /*소리감지 센서*/
  unsigned long crmil_sd = millis();
  if((crmil_sd - pwm_sd) >= interval_sd){
    pwm_sd = crmil_sd;
    sensorValue = analogRead(SOUND_SENSOR_PIN);
    sensorValue /= 2;
    
//    Serial1.print("*");
//    Serial1.print(sensorValue);
//    Serial1.print("@");
  }
  
  
}

void setup(){

  ms.attach(6);

  pinMode(tr,OUTPUT);
  pinMode(ec,INPUT);
 
  Serial.begin(9600);
  Serial1.begin(9600);
  dht.begin();//온습도 센
  
  pinMode(light, INPUT);
  
  pinMode(red,OUTPUT);
  digitalWrite(red,LOW);
}

void loop(){

//  int lightV = analogRead(light);//조도 센서 값 저
  int val = analogRead(light)/4;
  
  int light_st = Function_Light(val);//조도센서 함수 리턴값
  //1일때 on | 0일때 off
//  if(light_st == 1 || light_st == 0 ){
//    Serial.println(light_st);    
//  }

//  int person_num = Function_Ultra(tr,ec);
//  if(person_num == 1){
//    tot_person ++;
//    Serial.print("Total Person : ");
//    Serial.println(tot_person);
//  }
  Function_ht();
  Function_Alcohol();
  Function_sd();
  //humidity:   
  //temperature
 
}
