const int arr[5] = {3,5,6,9,10};

void Ledcontrol(char u){

  if(u=='1'){
    for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
    digitalWrite(arr[0],HIGH);
  }
  else if(u=='2'){
    for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
    digitalWrite(arr[1],HIGH);
  }

  else if(u=='3'){
    for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
    digitalWrite(arr[2],HIGH);
  }

  else if(u=='4'){
    for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
    digitalWrite(arr[3],HIGH);
  }

  else if(u=='5'){
    for(int i=0;i<5;i++) digitalWrite(arr[i],LOW);
    digitalWrite(arr[4],HIGH);
  }
  
  
}

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<5;i++) pinMode(arr[i],OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char u = Serial.read();
    Ledcontrol(u);
  }

}
