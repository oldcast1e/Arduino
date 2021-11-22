void setup(){
  Serial.begin(9600);
  while(!Serial);
}

void loop(){
//  String str1 = "Hello String!";
//  Serial.println(str1);
//  
//  Serial.println("");
//  
//  str1 = String('a');
//  Serial.println(str1);
//  
//  Serial.println("");
//  
//  String str2 = String(str1+"With more");
//  Serial.print(str2);
//
//  Serial.end();
if (Serial.available()>0){
  
  String str = Serial.readString();                   //read()가 아닌 readString()으로 읽기
                                                 //왜? 웬만한 교과서에는 read()로 한 문자만 읽어오는 것만 설명하는지 모르겠음
  str = str.substring(0, str.length()-1);      //시리얼모니터에서 엔터 치면서 마지막에 송신한 \n 제거
  Serial.println(str);


}
}
