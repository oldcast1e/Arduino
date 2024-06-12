#include <Wire.h>
#include <EEPROM.h>

const int ledPin = 13; // LED 핀 설정
unsigned long previousMillis = 0; // 이전 시간 저장
const long interval = 60000; // 1분(60초) 간격으로 시간 출력하기
int year, month, day, hour, minute, second, dayOfWeek; // 시간 및 요일 변수 선언
bool timeSet = false; // 시간이 설정되었는지 여부

const long updateTimeInterval = 1000; // 1초 간격
const long printTimeInterval = 60000; // 1분 간격
unsigned long previousPrintMillis = 0; // 이전 출력 시간const long updateTimeInterval = 1000; // 1초 간격
//const long printTimeInterval = 60000; // 1분 간격
//unsigned long previousPrintMillis = 0; // 이전 출력 시간


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
        printf("Memory allocation failed\n");
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

            char *c_name = p->class_name;
            int starthour = (int)p->class_start_c_time;
            int startmin = (p->class_start_c_time - starthour) * 60;
            int endhour = (int)p->class_end_c_time;
            int endmin = (p->class_end_c_time - endhour) * 60;

            Serial.print(c_name); Serial.print(' ');
            // 수업 시작 시간 출력
            if (starthour < 10) Serial.print("0");
            Serial.print(starthour); Serial.print(":");
            if (startmin < 10) Serial.print("0");
            Serial.print(startmin); Serial.print('~');
            // 수업 종료 시간 출력
            if (endhour < 10) Serial.print("0");
            Serial.print(endhour); Serial.print(":");
            if (endmin < 10) Serial.print("0");
            Serial.println(endmin);
        }   
    }
    if (flag == 0) {
        Serial.println("수업이 없습니다.");
    }
}

void check(const char* day, float input_c_time) {
    float c_time = input_c_time;
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
        schedule(&d, "학과 회의", 13.5, 15.0);
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

    class_check(&d, c_time);

    sejongclass* curr = d.H;
    while (curr != NULL) {
        sejongclass* next = curr->next;
        free(curr);
        curr = next;
    }
}

bool readTimeFromEEPROM() {
    if (EEPROM.read(0) == 1) { // EEPROM에 시간이 저장되어 있는지 확인
        year = EEPROM.read(1);
        month = EEPROM.read(2);
        day = EEPROM.read(3);
        hour = EEPROM.read(4);
        minute = EEPROM.read(5);
        second = EEPROM.read(6);
        dayOfWeek = EEPROM.read(7); // 요일 정보도 읽어옴

        // EEPROM에 저장된 시간 값이 올바르지 않은 경우 다시 시간 설정
        if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31 ||
            hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
            return false;
        }

        return true;
    }
    return false;
}

void setTimeManually() {
    Serial.println("Enter the current date and time (YYYY/MM/DD HH:MM:SS):");
    while (!Serial.available()) {} // 사용자 입력이 있을 때까지 대기
    readTime(); // 시간 읽기 함수 호출
    Serial.println("Time set.");
    EEPROM.write(0, 1); // EEPROM에 시간이 설정되었음을 표시
    EEPROM.write(1, year);
    EEPROM.write(2, month);
    EEPROM.write(3, day);
    EEPROM.write(4, hour);
    EEPROM.write(5, minute);
    EEPROM.write(6, second);
    // 요일 정보도 저장
    EEPROM.write(7, getDayOfWeek(year, month, day)); 
}

void readTime() {
    year = Serial.parseInt();
    while (Serial.read() != '/') {}
    month = Serial.parseInt();
    while (Serial.read() != '/') {}
    day = Serial.parseInt();
    while (Serial.read() != ' ') {}
    hour = Serial.parseInt();
    while (Serial.read() != ':') {}
    minute = Serial.parseInt();
    while (Serial.read() != ':') {}
    second = Serial.parseInt();
}

void updateSecond() {
    second++; // 초 증가
    if (second >= 60) { // 60초가 되면
        second = 0; // 0초로 초기화
        minute++; // 분 증가
        if (minute >= 60) { // 60분이 되면
            minute = 0; // 0분으로 초기화
            hour++; // 시 증가
            if (hour >= 24) { // 24시가 되면
                hour = 0; // 0시로 초기화
                day++; // 일 증가
                // 달마다 일수가 다를 수 있으므로 해당 달의 마지막 날을 체크하여 일을 증가시킴
                if (day > daysInMonth(year, month)) {
                    day = 1; // 다음 달로 넘어가기 위해 일을 1로 설정
                    month++; // 달 증가
                    if (month > 12) { // 12월을 넘어가면
                        month = 1; // 1월로 초기화
                        year++; // 년도 증가
                    }
                }
            }
        }
    }
}

void printTime() {
    Serial.print(year);
    Serial.print("/");
    if (month < 10) Serial.print("0");
    Serial.print(month);
    Serial.print("/");
    if (day < 10) Serial.print("0");
    Serial.print(day);
    Serial.print(" ");
    printDay(); // 요일 출력 함수 호출
    Serial.print(" ");
    if (hour < 10) Serial.print("0");
    Serial.print(hour);
    Serial.print(":");
    if (minute < 10) Serial.print("0");
    Serial.print(minute);
    Serial.print(":");
    if (second < 10) Serial.print("0");
    Serial.println(second);
}

void printDay() {
    const char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    // 요일 정보는 이미 업데이트되어 있으므로 그대로 사용
    Serial.print(days[dayOfWeek]);
}

int daysInMonth(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        days[1] = 29; // 윤년인 경우 2월의 일 수 변경
    }
    return days[month - 1]; // 인덱스는 0부터 시작하므로 1을 빼줌
}

int getDayOfWeek(int year, int month, int day) {
    int t = (14 - month) / 12;
    int y = year - t;
    int m = month + 12 * t - 2;
    int d = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
    return d;
}

void saveTimeToEEPROM() {
    EEPROM.write(0, 1); // EEPROM에 시간이 설정되었음을 표시
    EEPROM.write(1, year);
    EEPROM.write(2, month);
    EEPROM.write(3, day);
    EEPROM.write(4, hour);
    EEPROM.write(5, minute);
    EEPROM.write(6, second);
    // 요일 정보도 저장
    EEPROM.write(7, getDayOfWeek(year, month, day)); 
}

void setup() {
    Serial.begin(9600); // 시리얼 통신 시작
    pinMode(ledPin, OUTPUT); // LED 핀을 출력으로 설정
    // 초기 시간 설정
    if (!timeSet) {
        if (readTimeFromEEPROM()) { // 외부 EEPROM에서 시간을 읽어옴
            timeSet = true; // 시간 설정됨 표시
        } else {
            setTimeManually(); // 시간 수동 설정
        }
    }
}

void loop() {
    unsigned long currentMillis = millis(); // 현재 시간 가져오기
    
    if (currentMillis - previousMillis >= updateTimeInterval) { // 1초 간격이 지났는지 확인
        previousMillis = currentMillis; // 시간 업데이트
        updateSecond(); // 1초마다 시간 업데이트 함수 호출
    }
    
    // 1분 간격으로 출력
    if (currentMillis - previousPrintMillis >= printTimeInterval) {
        previousPrintMillis = currentMillis; // 출력 시간 업데이트
        dayOfWeek = getDayOfWeek(year, month, day); // 요일 정보 업데이트
        // printTime(); // 시간 출력 함수 호출
        saveTimeToEEPROM(); // 시간과 요일을 EEPROM에 저장
        
        // 현재 시간을 이용하여 수업 정보 확인 및 출력
        switch (dayOfWeek) {
            case 0: // Sunday
                Serial.println("No classes today.");
                break;
            case 1: // Monday
                check("Mon", hour + (minute / 60.0)); // 현재 요일이 월요일인 경우 수업 정보 확인
                break;
            case 2: // Tuesday
                check("Tue", hour + (minute / 60.0)); // 현재 요일이 화요일인 경우 수업 정보 확인
                break;
            case 3: // Wednesday
                check("Wed", hour + (minute / 60.0)); // 현재 요일이 수요일인 경우 수업 정보 확인
                break;
            case 4: // Thursday
                check("Thu", hour + (minute / 60.0)); // 현재 요일이 목요일인 경우 수업 정보 확인
                break;
            case 5: // Friday
                check("Fri", hour + (minute / 60.0)); // 현재 요일이 금요일인 경우 수업 정보 확인
                break;
            case 6: // Saturday
                Serial.println("No classes today.");
                break;
            default:
                Serial.println("Error: Invalid day of week.");
                break;
        }
    }
}
