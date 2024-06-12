#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(4, 5, 3); // DAT, CLK, RST  디지털 연결 번호
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
    Serial.begin(9600);
    Rtc.Begin();
  
    // 현재 시간을 가져와 시리얼 모니터에 출력
    RtcDateTime now = RtcDateTime(__DATE__, __TIME__);
    printDateTime(now);

//    Serial.println("시간을 확인하고, 정확한 시간으로 설정하세요.");
}

void loop() {
    // 아무것도 수행하지 않음
}

void printDateTime(const RtcDateTime& dt) {
    char datestring[20];
    snprintf_P(datestring, 
               sizeof(datestring),
               PSTR("%04u/%02u/%02u %02u:%02u:%02u"),
               dt.Year(),
               dt.Month(),
               dt.Day(),
               dt.Hour(),
               dt.Minute(),
               dt.Second());
    Serial.println(datestring);
}
