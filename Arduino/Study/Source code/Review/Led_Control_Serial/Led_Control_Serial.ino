const int arr[5] = {8, 9, 10, 11, 12};
int count = 0;


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i++) {
    pinMode(arr[i], OUTPUT);
  }
  Serial.begin(115200);


}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()==1) {
    char sv = Serial.read();
    
    Serial.print(sv);
    if(sv == '1'){
      for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
      digitalWrite(arr[0],HIGH);
    }
    if(sv == '2'){
      for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
      digitalWrite(arr[1],HIGH);
    }
    if(sv == '3'){
      for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
      digitalWrite(arr[2],HIGH);
    }
    if(sv == '4'){
      for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
      digitalWrite(arr[3],HIGH);
    }
    if(sv == '5'){
      for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
      digitalWrite(arr[4],HIGH);
    }

  

}
}
