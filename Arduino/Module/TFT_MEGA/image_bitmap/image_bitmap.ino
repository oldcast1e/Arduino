#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>
#include "bitmap.h" // 비트맵 데이터 포함

// LCD 설정
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4);

// 색상 정의
#define BLACK   0x0000  // 검정색
#define WHITE   0xFFFF  // 흰색

void setup() {
  mylcd.Init_LCD();       // LCD 초기화
  mylcd.Fill_Screen(BLACK); // 화면 초기화

  // 비트맵 출력
  drawBitmap(0, 0, weather_sun, BITMAP_WIDTH, BITMAP_HEIGHT);
}

void loop() {
  // 빈 루프
}

void drawBitmap(int16_t x, int16_t y, const unsigned char *bitmap, int16_t w, int16_t h) {
  for (int16_t j = 0; j < h; j++) {
    for (int16_t i = 0; i < w; i++) {
      uint16_t byteIndex = (j * w + i) / 8;
      uint8_t bitIndex = i % 8;
      uint8_t byte = pgm_read_byte(&bitmap[byteIndex]);
      if (byte & (0x80 >> bitIndex)) {
        mylcd.Set_Draw_color(WHITE);
        mylcd.Draw_Pixel(x + i, y + j);
      } else {
        mylcd.Set_Draw_color(BLACK);
        mylcd.Draw_Pixel(x + i, y + j);
      }
    }
  }
}
