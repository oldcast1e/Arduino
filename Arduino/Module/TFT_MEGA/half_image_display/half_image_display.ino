#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>
#include <avr/pgmspace.h>

// LCD 설정 (Arduino Mega2560용)
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4);



// 비트맵 데이터 (PROGMEM에 저장하여 플래시 메모리 사용)
const unsigned char bitmap[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x01, 0x40, 0x00, 
0x00, 0x00, 0x00, 0x2B, 0xE5, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x35, 0x9D, 0x40, 0x00, 0x88, 0x00, 
0x00, 0x00, 0x03, 0x0F, 0xEF, 0xB8, 0xC0, 0x00, 0x00, 0x09, 0x7B, 0xDE, 0xDB, 0x80, 0x58, 0x00, 
0x00, 0x00, 0x0F, 0xCB, 0x7C, 0x6B, 0x44, 0x00, 0x00, 0x0D, 0x53, 0xD9, 0xF6, 0xC0, 0x00, 0x00, 
0x00, 0x00, 0x6E, 0x5F, 0x9E, 0x5A, 0x94, 0x00, 0x01, 0xEB, 0xDB, 0xB6, 0x13, 0xF8, 0x00, 0x00, 
0x00, 0x01, 0x7C, 0x4C, 0x00, 0x12, 0x1B, 0xC0, 0x04, 0xE4, 0xA0, 0x00, 0x6F, 0x87, 0x00, 0x00, 
0x00, 0x01, 0xBF, 0x40, 0x00, 0x01, 0x6E, 0x20, 0x1A, 0xB3, 0x00, 0x00, 0x03, 0xCF, 0x80, 0x00, 
0x00, 0x05, 0x79, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x6B, 0xE4, 0x00, 0x00, 0x00, 0x58, 0x80, 0x00, 
0x00, 0x03, 0x0C, 0x00, 0x00, 0x00, 0x06, 0x6E, 0xD6, 0xE0, 0x00, 0x00, 0x00, 0x22, 0xC0, 0x00, 
0x00, 0x1D, 0xE8, 0x00, 0x00, 0x00, 0x03, 0x54, 0xCA, 0x00, 0x01, 0xD0, 0x00, 0x10, 0x50, 0x00, 
0x00, 0x24, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xF4, 0x28, 0x00, 0x01, 0xE0, 0x00, 0x0C, 0x48, 0x00, 
0x00, 0x22, 0x60, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x7A, 0x00, 0x00, 0xB0, 0x00, 0x0F, 0x88, 0x00, 
0x00, 0x0D, 0x80, 0x01, 0x38, 0xF0, 0x00, 0x2C, 0xA8, 0x00, 0x1B, 0xE6, 0xC0, 0x08, 0x98, 0x00, 
0x00, 0x18, 0xA0, 0x07, 0xA6, 0xB0, 0x00, 0x36, 0x30, 0x00, 0x35, 0xEF, 0x80, 0x07, 0x40, 0x00, 
0x00, 0x36, 0x40, 0x03, 0x20, 0x18, 0x00, 0x41, 0x14, 0x00, 0x36, 0x50, 0x00, 0x0A, 0xC8, 0x00, 
0x00, 0x39, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x22, 0x9C, 0x00, 0x01, 0x60, 0x00, 0x0D, 0xA0, 0x00, 
0x00, 0x1E, 0x50, 0x00, 0x00, 0x00, 0x00, 0x64, 0xE2, 0x80, 0x01, 0xD8, 0x00, 0x09, 0xD0, 0x00, 
0x00, 0x1F, 0xFC, 0x00, 0x00, 0x00, 0x0E, 0x90, 0x2A, 0x40, 0x00, 0x00, 0x00, 0x3E, 0x70, 0x00, 
0x00, 0x07, 0x7C, 0x00, 0x00, 0x00, 0x17, 0x34, 0x56, 0x60, 0x00, 0x00, 0x00, 0xCF, 0xC0, 0x00, 
0x00, 0x05, 0xE7, 0x00, 0x00, 0x00, 0x39, 0x78, 0x35, 0xB8, 0x00, 0x00, 0x01, 0x9F, 0x00, 0x00, 
0x00, 0x01, 0x74, 0x20, 0x00, 0x02, 0xC2, 0x60, 0x0E, 0x8B, 0xC0, 0x00, 0x0D, 0x3D, 0x00, 0x00, 
0x00, 0x00, 0x92, 0x9C, 0x7B, 0x8B, 0x1D, 0x80, 0x02, 0xB5, 0x52, 0x4D, 0xBA, 0x8E, 0x00, 0x00, 
0x00, 0x00, 0x09, 0x64, 0xED, 0xD0, 0x96, 0x00, 0x00, 0x55, 0x23, 0x6B, 0xD9, 0x48, 0x00, 0x00, 
0x00, 0x00, 0x05, 0x09, 0x07, 0xB3, 0x80, 0x00, 0x00, 0x06, 0xE2, 0x11, 0xBA, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x8C, 0xE7, 0xBF, 0x80, 0x00, 0x00, 0x01, 0xF7, 0x15, 0xFA, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x07, 0xC5, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xB5, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x64, 0x0C, 0x08, 0x0D, 0x38, 0x20, 0x2C, 0x2F, 0xB1, 0x10, 0x30, 0x19, 0x80, 0x00, 
0x00, 0x00, 0xC8, 0x0B, 0x06, 0x16, 0x1A, 0x24, 0x3C, 0x06, 0x01, 0x40, 0xA1, 0x42, 0x00, 0x00, 
0x00, 0x00, 0x4C, 0x02, 0x02, 0x14, 0x02, 0x18, 0x00, 0x04, 0x01, 0xC4, 0xB1, 0x01, 0x40, 0x00, 
0x00, 0x01, 0xCD, 0x03, 0x03, 0x00, 0x19, 0x30, 0x30, 0x07, 0x01, 0x6C, 0xE1, 0x81, 0xC0, 0x00, 
0x00, 0x01, 0x71, 0x85, 0xB8, 0x04, 0x1C, 0x24, 0x20, 0x04, 0x01, 0x60, 0xD0, 0xC2, 0x40, 0x00, 
0x00, 0x02, 0x33, 0x01, 0x0C, 0x16, 0x34, 0x1A, 0x70, 0x07, 0x01, 0xE2, 0xB3, 0xC3, 0x40, 0x00, 
0x00, 0x02, 0x03, 0x81, 0x09, 0x1E, 0x48, 0x01, 0x90, 0x39, 0xE0, 0xC1, 0x50, 0x56, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x08, 0x00, 0x13, 0x08, 0x70, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x02, 0x34, 0x78, 0x1C, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x10, 0x08, 0x70, 0x0C, 0x70, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

// 비트맵의 원본 너비와 높이 (픽셀 단위)
#define BITMAP_WIDTH 128
#define BITMAP_HEIGHT 64

// 비트맵 출력 함수
void drawBitmapScaled(int16_t x, int16_t y, const unsigned char *bitmap, int16_t bmpW, int16_t bmpH, int16_t displayW, int16_t displayH) {
  float scaleX = (float)displayW / bmpW; // 가로 스케일 비율
  float scaleY = (float)displayH / bmpH; // 세로 스케일 비율

  for (int16_t j = 0; j < displayH; j++) { // 디스플레이 높이 루프
    for (int16_t i = 0; i < displayW; i++) { // 디스플레이 너비 루프
      // 원본 비트맵에서 대응되는 픽셀 계산
      int16_t srcX = i / scaleX; // 원본 비트맵의 x 좌표
      int16_t srcY = j / scaleY; // 원본 비트맵의 y 좌표
      uint16_t byteIndex = (srcY * bmpW + srcX) / 8; // 바이트 인덱스 계산
      uint8_t bitIndex = srcX % 8;                  // 바이트 내 비트 위치 계산
      uint8_t byte = pgm_read_byte(&bitmap[byteIndex]);

      if (byte & (0x80 >> bitIndex)) {   // 비트가 활성화된 경우
        mylcd.Set_Draw_color(WHITE);     // 흰색 설정
        mylcd.Draw_Pixel(x + i, y + j);  // 픽셀 출력
      } else {
        mylcd.Set_Draw_color(BLACK);     // 검정색 설정
        mylcd.Draw_Pixel(x + i, y + j);  // 픽셀 출력
      }
    }
  }
}

void setup() {
  mylcd.Init_LCD();       // LCD 초기화
  mylcd.Fill_Screen(BLACK); // 화면 초기화

  // 디스플레이 크기
  int16_t displayWidth = mylcd.Get_Display_Width(); // 디스플레이 너비
  int16_t displayHeight = mylcd.Get_Display_Height() / 2; // 디스플레이 절반 높이

  // 비트맵 출력
  drawBitmapScaled(0, 0, bitmap, BITMAP_WIDTH, BITMAP_HEIGHT, displayWidth, displayHeight);
}

void loop() {
  // 빈 루프
}