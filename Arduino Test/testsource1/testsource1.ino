#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(4, 5, 3); // DAT, CLK, RST  디지털 연결 번호
RtcDS1302<ThreeWire> Rtc(myWire);

unsigned long previousMillis = 0;
const long interval = 1000;  // 1초 (1000밀리초)

typedef struct sejongclass {
    char class_name[40];
    float class_start_c_time;
    float class_end_c_time;
    struct sejongclass* next;
} sejongclass;

typedef struct days {
    sejongclass* H;
} days;

int isEmpty(struct days* L) {
    return L->H == NULL;
}

void schedule(struct days* L, const char* name, float st, float et) {
    sejongclass* node = (sejongclass*)malloc(sizeof(sejongclass));
    if (node == NULL) {
        Serial.println("Memory allocation failed");
        return;
    }

    strcpy(node->class_name, name);
    node->class_start_c_time = st;
    node->class_end_c_time = et;
    node->next = NULL;

    if (isEmpty(L)) {
        L->H = node;
    }
    else {
        sejongclass* p;
        for (p = L->H; p->next != NULL; p = p->next);
        p->next = node;
    }
}

void class_check(days* L, float c_time) {
    sejongclass* p;
    int flag = 0;
    for (p = L->H; p != NULL; p = p->next) {
        if (c_time >= p->class_start_c_time && c_time <= p->class_end_c_time) {
            flag = 1;

            char* c_name = p->class_name;
            int starthour = (int)p->class_start_c_time, endhour = (int)p->class_end_c_time;

            int startmin = (p->class_start_c_time - starthour) * 60;
            int endmin = (p->class_end_c_time - endhour) * 60;

            Serial.print(c_name);
            Serial.print(' ');

            Serial.print(starthour);
            Serial.print(':');
            if (startmin < 10) Serial.print('0');
            Serial.print(startmin);
            Serial.print('~');
            Serial.print(endhour);
            Serial.print(':');
            if (endmin < 10) Serial.print('0');
            Serial.println(endmin);
        }
    }
    if (flag == 0) {
        Serial.println("수업이 없습니다.");
    }
}

int getWeekday(int year, int month, int dayOfMonth) {
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int daysInMonth[] = {31, 28 + isLeapYear, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = dayOfMonth - 1;
    for (int i = 0; i < month - 1; ++i) {
        days += daysInMonth[i];
    }
    for (int i = 1; i < year; ++i) {
        days += (i % 4 == 0 && i % 100 != 0) || (i % 400 == 0) ? 366 : 365;
    }
    return (days + 2) % 7; // 2024년 1월 1일은 화요일이므로, 0: 화요일, 1: 수요일, ..., 6: 월요일
}

const char* getWeekdayString(int weekday) {
    switch (weekday) {
        case 0:
            return "Sun";
        case 1:
            return "Mon";
        case 2:
            return "Tue";
        case 3:
            return "Wed";
        case 4:
            return "Thu";
        case 5:
            return "Fri";
        case 6:
            return "Sat";
        default:
            return ""; // 예외 처리
    }
}

void check(const char* day, int year, int month, int dayOfMonth, int hour, int minute, int second) {
    days d;
    d.H = NULL;

    if (strcmp(day, "Mon") == 0) {
        schedule(&d, "창의SW기초설계", 9.0, 12.0);
        schedule(&d, "창의SW기초설계", 12.0, 15.0);
        schedule(&d, "확률및통계", 16.5, 18.0);
    }
    else if (strcmp(day, "Tue") == 0) {
        schedule(&d, "창의SW기초설계", 9.0, 12.0);
        schedule(&d, "전기회로", 12.0, 13.5);
        schedule(&d, "확률및통계", 13.5, 15.0);
        schedule(&d, "통신시스템", 15.0, 16.5);
        schedule(&d, "선형대수및프로그래밍", 18.0, 21.0);
    }
    else if (strcmp(day, "Wed") == 0) {
        schedule(&d, "무인이동체융합프로젝트(대학원)", 9.0, 12.0);
        schedule(&d, "박사논문연구1(대학원)", 12.0, 13.5);
        schedule(&d, "학과 회의", 13.5, 13.0);
        schedule(&d, "확률및통계", 16.5, 18.0);
        schedule(&d, "선형대수및프로그래밍", 19.5, 21.0);
    }
    else if (strcmp(day, "Thu") == 0) {
        schedule(&d, "창의SW기초설계", 9.0, 12.0);
        schedule(&d, "전기회로", 12.0, 13.5);
        schedule(&d, "확률및통계", 13.5, 15.0);
        schedule(&d, "통신시스템", 15.0, 16.5);
        schedule(&d, "AI로봇설계", 16.5, 19.5);
    }
    else {
        schedule(&d, "반도체소자", 9.0, 12.0);
        schedule(&d, "박사논문연구1(대학원)", 12.0, 13.5);
        schedule(&d, "Capston디자인(산학협력프로젝트)", 13.5, 19.5);
        schedule(&d, "선형대수및프로그래밍", 19.5, 21.0);
    }

    float c_time = hour + minute / 60.0 + second / 3600.0;
    class_check(&d, c_time);

    sejongclass* curr = d.H;
    while (curr != NULL) {
        sejongclass* next = curr->next;
        free(curr);
        curr = next;
    }
}

void setup() {
    Serial.begin(9600);
    Rtc.Begin();
}

void loop() {
    unsigned long currentMillis = millis();

    // 경과된 시간이 interval 이상이면 현재 시간을 출력하고 previousMillis를 업데이트합니다.
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  

        RtcDateTime now = Rtc.GetDateTime();
        int year = now.Year(), month = now.Month(), dayOfMonth = now.Day(), hour = now.Hour(), minute = now.Minute(), second = now.Second();
        int weekday = getWeekday(year, month, dayOfMonth);
        const char* weekdayString = getWeekdayString(weekday);
        check(weekdayString, year, month, dayOfMonth, hour, minute, second);
    }
}
