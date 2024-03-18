const int L[5] = {22,24,26,28,30};

void DC(){

  for(int x=0;x<=4;x++){
    digitalWrite(L[x],LOW);
  }
}


void setup(){

  for(int x=0;x<=4;x++){
    pinMode(L[x],OUTPUT);
  }

  Serial.begin(9600);
  Serial1.begin(9600);

  DC();
//  for(int x=0;x<=4;x++){
//    digitalWrite(L[x],HIGH);
//  }
}

void loop(){

  if(Serial1.available()){

    char u = Serial1.read();

//    Serial.print(">");
//    Serial.println(u);
//
    if(u == '1'){

      Serial.println("LED_1 is on");
      digitalWrite(L[0],HIGH);
    }

    else if(u == '2'){

      Serial.println("LED_2 is on");
      digitalWrite(L[1],HIGH);
    }

    else if(u == '3'){

      Serial.println("LED_3 is on");
      digitalWrite(L[2],HIGH);
    }

    else if(u == '4'){

      Serial.println("LED_4 is on");
      digitalWrite(L[3],HIGH);
    }
    else if(u == '5'){

      Serial.println("LED_5 is on");
      digitalWrite(L[4],HIGH);
    }

    else if(u=='0'){
      DC();
    }

    
  }
}
