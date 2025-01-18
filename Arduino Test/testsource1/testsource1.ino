#include<Servo.h>
Servo ms;

int cds = A1;      
int dr = A0;       
int led = A2;     

int distance = 0; 
int angle = 0;

const int ec = 2;
const int tr = 3;



int iaPin = 6; // A-IA 핀을 Arduino의 D9 핀에 연결
int ibPin = 7; // A-IB 핀을 Arduino의 D10 핀에 연결

void setup() {
  Serial.begin(9600); 
  ms.attach(3);
  ms.write(0);

  pinMode(tr,OUTPUT);
  pinMode(ec,INPUT);


  pinMode(iaPin, OUTPUT); // A-IA 핀을 출력 모드로 설정
  pinMode(ibPin, OUTPUT); // A-IB 핀을 출력 모드로 설정

  pinMode(led, OUTPUT);    
  pinMode(dr,INPUT);
}

void loop() {
  // int drValue = analogRead(dr);   // 가변 저항 값 읽기 (0~1023)
  

  // Serial.print("Potentiometer = "); Serial.println(drValue);     
  // Serial.print("PWM = "); Serial.println(pwmValue);      

  digitalWrite(tr,LOW);
  delayMicroseconds(2);
  
  digitalWrite(tr,HIGH);
  delayMicroseconds(10);
  
  digitalWrite(tr,LOW);
  
  long Distance = (pulseIn(ec,HIGH)/2)/29.1;

  if(0<=Distance &&  Distance<= 30){
    int pwmValue = map(Distance, 0, 30, 0, 255); // 가변 저항 값을 PWM 값(0~255)으로 매핑
    analogWrite(ibPin, pwmValue);   // 팬 속도를 설정
    analogWrite(iaPin, 0);          // 팬의 정방향 회전 설정
  }
  else{
      // for(int i=255;i>=0;i--){ analogWrite(ibPin, i); delay(10); }
      analogWrite(ibPin, 0); 
  }

  delay(300);
  Serial.print(Distance);
  Serial.println( "cm");
  // analogWrite(ibPin, pwmValue);   // 팬 속도를 설정
  // analogWrite(iaPin, 0);          // 팬의 정방향 회전 설정
  

  // delay(100); // 팬 속도 변화 확인 딜레이
  // analogWrite(iaPin, 1023 -drValue 200); // A-IA 핀에 PWM 신호 200(듀티 사이클 약 78%) 전송
  // analogWrite(ibPin, 0); // A-IB 핀에 LOW 신호 전송 (팬의 한 방향 회전 설정) 
  // if(drValue)ms.write(angle);
  //Serial.println(drValue);

  //analogWrite(led, drValue / 4);   
  //delay(100);     

  // analogWrite(iaPin, 200); // A-IA 핀에 PWM 신호 200(듀티 사이클 약 78%) 전송
  // analogWrite(ibPin, 0); // A-IB 핀에 LOW 신호 전송 (팬의 한 방향 회전 설정)
  // delay(5000); // 팬을 5초간 회전
  

  // analogWrite(iaPin, 0); // A-IA 핀에 LOW 신호 전송
  // analogWrite(ibPin, 200); // A-IB 핀에 PWM 신호 200(듀티 사이클 약 78%) 전송
  // delay(5000); // 팬을 반대 방향으로 5초간 회전

  // analogWrite(iaPin, 0); // A-IA 핀에 LOW 신호 전송
  // analogWrite(ibPin, 0); // A-IB 핀에 LOW 신호 전송 (팬 정지)
  // delay(2000); // 팬을 2초간 정지
  // pinMode(6, OUTPUT);  
  // digitalWrite(6, HIGH);  delay(10); digitalWrite(6, LOW); 
  
  // pinMode(6, INPUT);  
  // distance = 0.01723 * pulseIn(6, HIGH); // 들어온 값을 0.01723과 곱하여 거리 계산
  // angle = 179 - distance/2;
  
  // if(0 <= angle && angle <= 179)ms.write(angle);

  // Serial.print(distance); Serial.println(" cm");
  // Serial.print(angle); Serial.println(" dgree");

  // delay(10);
 
}
