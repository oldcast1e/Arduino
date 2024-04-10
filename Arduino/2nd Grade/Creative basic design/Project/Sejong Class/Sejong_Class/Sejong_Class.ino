#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)
typedef struct sejongclass {
    char class_name[40];
    double class_start_time;
    double class_end_time;
    struct sejongclass* next;
} sejongclass;

typedef struct days {
    sejongclass* H;
} days;

int isEmpty(struct days* L) {
    return L->H == NULL;
}

void schedule(struct days* L, const char* name, double st, double et) {
    sejongclass* node = (sejongclass*)malloc(sizeof(sejongclass));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    strcpy(node->class_name, name);
    node->class_start_time = st;
    node->class_end_time = et;
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

void class_check(days* L, double time) {
    sejongclass* p;
    int flag = 0;
    for (p = L->H; p != NULL; p = p->next) {
        if (time >= p->class_start_time && time <= p->class_end_time) {
            flag = 1;
            printf("%.1f부터 %.1f까지 %s의 수업이 있습니다\n", p->class_start_time, p->class_end_time, p->class_name);
        }
    }
    if (flag == 0) {
        printf("수업이 없습니다\n");
    }
}

int main() {
    double time;
    char day[20]; // 요일을 저장할 배열 크기를 충분히 크게 지정
    scanf("%s %lf", day, &time);

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

    class_check(&d, time);

    
    sejongclass* curr = d.H;
    while (curr != NULL) {
        sejongclass* next = curr->next;
        free(curr);
        curr = next;
    }

    return 0;
}


