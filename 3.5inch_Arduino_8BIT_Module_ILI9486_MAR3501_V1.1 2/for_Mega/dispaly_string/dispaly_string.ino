/***********************************************************************************
* 이 프로그램은 문자열을 표시하는 데모입니다.
* 이 데모는 8비트 또는 16비트 데이터 포트를 사용하는 LCD 모듈을 대상으로 합니다.
* 이 프로그램은 LCDKIWI 라이브러리가 필요합니다.

* File                : display_string.ino
* Hardware Environment: Arduino UNO&Mega2560
* Build Environment   : Arduino

* 개발 보드 또는 브레이크아웃 보드에 맞는 핀을 설정하십시오.
* 이 데모는 BREAKOUT BOARD만 사용하며 LCD에 이러한 8비트 데이터 라인을 사용합니다.
* 핀 사용은 다음과 같습니다:
*                  LCD_CS  LCD_CD  LCD_WR  LCD_RD  LCD_RST  SD_SS  SD_DI  SD_DO  SD_SCK 
*     Arduino Uno    A3      A2      A1      A0      A4      10     11     12      13                            
*Arduino Mega2560    A3      A2      A1      A0      A4      10     11     12      13                           

*                  LCD_D0  LCD_D1  LCD_D2  LCD_D3  LCD_D4  LCD_D5  LCD_D6  LCD_D7  
*     Arduino Uno    8       9       2       3       4       5       6       7
*Arduino Mega2560    8       9       2       3       4       5       6       7 

* 디스플레이 모듈에 맞게 핀을 설정해야 합니다!
*
* @attention
*
* 현재 펌웨어는 가이드 역할을 하기 위해 제공되는 것으로 고객이 자신의 제품에 대한 코딩 정보를 제공하여
* 시간을 절약할 수 있도록 목적을 가지고 있습니다. 결과적으로 QD electronic은
* 이러한 펌웨어의 내용 및 이러한 코딩 정보를 사용함으로써 발생하는
* 어떠한 청구에 대해서도 책임을 지지 않습니다.
**********************************************************************************/

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

// IC 모델을 알고 있거나 모듈을 읽을 수 있는 경우 이 구성 함수를 사용할 수 있습니다.
LCDWIKI_KBV mylcd(ILI9486,A3,A2,A1,A0,A4); //모델,cs,cd,wr,rd,reset
// IC 모델을 모르고 모듈을 읽을 수 있는 경우 이 구성 함수를 사용할 수 있습니다.
//LCDWIKI_KBV mylcd(320,480,A3,A2,A1,A0,A4);//width,height,cs,cd,wr,rd,reset

// 몇 가지 색상 값을 정의합니다.
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup() 
{
  Serial.begin(9600);
  mylcd.Init_LCD();
  Serial.println(mylcd.Read_ID(), HEX);
  mylcd.Fill_Screen(BLACK);
}

void loop() 
{
  mylcd.Set_Text_Mode(0);
  // 문자열 1회 표시
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_colour(RED);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Hello World!", 0, 0);
  mylcd.Print_Number_Float(01234.56789, 2, 0, 8, '.', 0, ' ');  
  mylcd.Print_Number_Int(0xDEADBEF, 0, 16, 0, ' ',16);
  //mylcd.Print_String("DEADBEF", 0, 16);

  // 문자열 2회 표시
  mylcd.Set_Text_colour(GREEN);
  mylcd.Set_Text_Size(2);
  mylcd.Print_String("Hello World!", 0, 40);
  mylcd.Print_Number_Float(01234.56789, 2, 0, 56, '.', 0, ' ');  
  mylcd.Print_Number_Int(0xDEADBEF, 0, 72, 0, ' ',16);
  //mylcd.Print_String("DEADBEEF", 0, 72);

  // 문자열 3회 표시
  mylcd.Set_Text_colour(BLUE);
  mylcd.Set_Text_Size(3);
  mylcd.Print_String("Hello World!", 0, 104);
  mylcd.Print_Number_Float(01234.56789, 2, 0, 128, '.', 0, ' ');  
  mylcd.Print_Number_Int(0xDEADBEF, 0, 152, 0, ' ',16);
 // mylcd.Print_String("DEADBEEF", 0, 152);

  // 문자열 4회 표시
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Size(4);
  mylcd.Print_String("Hello!", 0, 192);

  // 문자열 5회 표시
  mylcd.Set_Text_colour(YELLOW);
  mylcd.Set_Text_Size(5);
  mylcd.Print_String("Hello!", 0, 224);

  // 문자열 6회 표시
  mylcd.Set_Text_colour(RED);
  mylcd.Set_Text_Size(6);
  mylcd.Print_String("Hello!", 0, 266);

  delay(3000);
}
