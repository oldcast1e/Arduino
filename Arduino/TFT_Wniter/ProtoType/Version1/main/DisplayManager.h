#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>
#include "bitmap.h"

class DisplayManager {
private:
    LCDWIKI_KBV& lcd;
    int screenWidth;
    int screenHeight;
    static constexpr uint16_t WHITE = 0xFFFF;
    static constexpr uint16_t BLACK = 0x0000;

public:
    DisplayManager(LCDWIKI_KBV& lcdRef) : lcd(lcdRef) {
        screenWidth = lcd.Get_Display_Width();
        screenHeight = lcd.Get_Display_Height();
    }

    void initialize() {
        lcd.Init_LCD();
        lcd.Fill_Screen(WHITE);
    }

    void drawHorizontalLine(int y) {
        lcd.Set_Draw_color(BLACK);
        lcd.Draw_Line(0, y, screenWidth - 1, y);
    }

    void drawVerticalLine(int x, int yStart, int yEnd) {
        lcd.Set_Draw_color(BLACK);
        lcd.Draw_Line(x, yStart, x, yEnd);
    }

    void clearRegion(int xStart, int xEnd, int yStart, int yEnd) {
        lcd.Set_Draw_color(WHITE);
        for (int y = yStart; y <= yEnd; y++) {
            lcd.Draw_Line(xStart, y, xEnd, y);
        }
    }

    void printCenteredText(const char* text, int xStart, int xEnd, int yStart, int yEnd, uint16_t color, uint8_t textSize) {
        int charWidth = 6 * textSize;
        int charHeight = 8 * textSize;
        int textWidth = charWidth * strlen(text);
        int textHeight = charHeight;

        int x = xStart + (xEnd - xStart - textWidth) / 2;
        int y = yStart + (yEnd - yStart - textHeight) / 2;

        lcd.Set_Text_colour(color);
        lcd.Set_Text_Back_colour(WHITE);
        lcd.Set_Text_Size(textSize);
        lcd.Print_String(text, x, y);
    }

    void drawBitmapScaled(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, float scale) {
        int scaledWidth = w * scale;
        int scaledHeight = h * scale;

        for (int16_t j = 0; j < scaledHeight; j++) {
            for (int16_t i = 0; i < scaledWidth; i++) {
                int16_t originalX = i / scale;
                int16_t originalY = j / scale;
                uint16_t byteIndex = (originalY * w + originalX) / 8;
                uint8_t bitIndex = originalX % 8;
                uint8_t byte = pgm_read_byte(&bitmap[byteIndex]);
                lcd.Set_Draw_color(byte & (0x80 >> bitIndex) ? BLACK : WHITE);
                lcd.Draw_Pixel(x + i, y + j);
            }
        }
    }
};

#endif
