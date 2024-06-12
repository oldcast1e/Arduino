#include <ThreeWire.h>  
#include <RtcDS1302.h>

/*
// CONNECTIONS:
// DS1302 CLK/SCLK --> 7
// DS1302 DAT/IO --> 6
// DS1302 RST/CE --> 5
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND
*/
//ThreeWire myWire(6, 7, 5); // DAT, CLK, RST  디지털 연결 번호
ThreeWire myWire(4, 5, 3); // DAT, CLK, RST  디지털 연결 번호
RtcDS1302<ThreeWire> Rtc(myWire);

unsigned long previousMillis = 0;
const long interval = 1000;  // 1초 (1000밀리초)

void setup () {    
    Serial.begin(9600);
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
}

void loop () {
    unsigned long currentMillis = millis();

    // 경과된 시간이 interval 이상이면 현재 시간을 출력하고 previousMillis를 업데이트합니다.
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  

        RtcDateTime now = Rtc.GetDateTime();
        printDateTime(now);   // 현재시간 함수 호출
        Serial.println();
    }
}

// 시계 모듈 년도, 달, 시간, 분, 초 받아오는 함수
#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt){
    char datestring[20];
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%04u/%02u/%02u %02u:%02u:%02u"),
            dt.Year(),
            dt.Month(),
            dt.Day(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
