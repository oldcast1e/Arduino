#include <OneWire.h>  //디지털 온도 센서를 사용하기 위한 라이브러리

OneWire ds(2); //2번 핀에 연결된 OneWire 개체 설정 

void setup() {
  Serial.begin(9600); //시리얼 통신 속도를 9600으로 설정
}

void loop() {
  byte i;
  byte present = 0;
  byte data[12]; //data 저장 공간 설정
  byte addr[8]; //addr 저장 공간 설정 
  float Temp; //Temp 변수 설정

  if (!ds.search(addr)) {
    ds.reset_search();
    return;
  }
  //no more sensors on chain, reset search

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); //start conversion, with parasite power on at the end
  delay(1000);

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad

  for (i = 0; i < 9; i++) { 
    data[i] = ds.read();
  }

  Temp=(data[1]<<8)+data[0];
  Temp=Temp/16;


  Serial.print("C=");
  Serial.print(Temp);
  Serial.print(", ");
  //섭씨 온도 출력

  Temp=Temp*1.8+32; //섭씨를 화씨로 변환

  Serial.print("F=");
  Serial.print(Temp);
  Serial.println(" ");
  //화씨 온도 출력
}
