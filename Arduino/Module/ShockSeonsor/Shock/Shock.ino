int Dit_Sensor = 2; // INPUT PIN (DIGTAL)
int LED= 13;

// 프로그램 시작 - 초기화 작업
void setup(){
    Serial.begin(9600); // 시리얼 통신 초기화
    Serial.println("Arduino Examples - Shock Dit_Sensor");
    pinMode(Dit_Sensor, INPUT);
}

void loop(){
    /*디지털 출력: 터치의 유무 판단 조건*/
    if (true == IsTouchec(Dit_Sensor)){
       Serial.println("Moved!"); digitalWrite(LED,HIGH);
    }
    else {Serial.print(".");digitalWrite(LED,LOW);}
    delay(500);
}

bool IsTouchec(int p){
    int time = 0;
    do{
        if (HIGH == digitalRead(Dit_Sensor)) return true;
        delay(1);
    } while (time++<15);
    
    return false;
}