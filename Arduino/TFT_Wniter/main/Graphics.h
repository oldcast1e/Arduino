#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

class Graphics {
public:
    static void drawHorizontalLine(LCDWIKI_KBV &lcd, int y);
    static void drawVerticalLine(LCDWIKI_KBV &lcd, int x, int yStart, int yEnd);
    static void clearRegion(LCDWIKI_KBV &lcd, int xStart, int xEnd, int yStart, int yEnd);
    static void printCenteredText(LCDWIKI_KBV &lcd, const char *text, int xStart, int xEnd, int yStart, int yEnd, uint16_t color, uint8_t textSize);
    static void printTextInRegion(LCDWIKI_KBV &lcd, const char *text, int xStart, int xEnd, int yStart, int lineHeight, uint16_t color, uint8_t textSize, int line);
    static void drawBitmapScaled(LCDWIKI_KBV &lcd, int16_t x, int16_t y, const unsigned char *bitmap, int16_t w, int16_t h, float scale);
};

#endif
