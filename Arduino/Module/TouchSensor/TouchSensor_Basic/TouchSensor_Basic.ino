int Dit_Sensor = 2; // INPUT PIN (DIGTAL)
int Anal_Sensor = A0; // INPUT PIN (DIGTAL)

// 프로그램 시작 - 초기화 작업
void setup(){
    Serial.begin(9600); // 시리얼 통신 초기화
    Serial.println("Arduino Examples - [WAT-S009] Touch Dit_Sensor");
    pinMode(Dit_Sensor, INPUT);
    pinMode(Anal_Sensor, INPUT);
}

void loop(){
    /*아날로그 출력: 전압값 확인*/
    float Analog = analogRead (Anal_Sensor) * (5.0 / 1023.0); 
    Serial.print ("Analog voltage value:"); Serial.print (Analog, 4);  Serial.print ("V\n");

    /*디지털 출력: 터치의 유무 판단 조건*/
    if (true == IsTouchec(Dit_Sensor))Serial.println("Touched");
    else Serial.print(".");
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