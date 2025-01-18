#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library

// LCD configuration for Mega2560 (model, cs, cd, wr, rd, reset)
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4);

// Define color values
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800

// Function to draw a horizontal line
void drawHorizontalLine(int y) {
    mylcd.Set_Draw_color(BLACK);
    mylcd.Draw_Line(0, y, mylcd.Get_Display_Width() - 1, y);
}

// Function to draw a vertical line
void drawVerticalLine(int x, int yStart, int yEnd) {
    mylcd.Set_Draw_color(BLACK);
    mylcd.Draw_Line(x, yStart, x, yEnd);
}

// Function to print text in the center of a region
void printCenteredText(const char* text, int xStart, int xEnd, int yStart, int yEnd, uint16_t color, uint8_t textSize) {
    int charWidth = 6 * textSize; // Approximate character width in pixels
    int charHeight = 8 * textSize; // Approximate character height in pixels
    int textWidth = charWidth * strlen(text); // Total text width based on number of characters
    int textHeight = charHeight; // Total text height (same for single-line text)

    int x = xStart + (xEnd - xStart - textWidth) / 2; // Center text horizontally
    int y = yStart + (yEnd - yStart - textHeight) / 2; // Center text vertically

    mylcd.Set_Text_colour(color);
    mylcd.Set_Text_Back_colour(WHITE);
    mylcd.Set_Text_Size(textSize);
    mylcd.Print_String(text, x, y);
}

void setup() {
    mylcd.Init_LCD();
    mylcd.Fill_Screen(WHITE);

    int screenHeight = mylcd.Get_Display_Height();
    int screenWidth = mylcd.Get_Display_Width();

    // Divide the screen into 3 vertical sections
    int sectionHeight = screenHeight / 3;

    // Draw horizontal dividing lines for main sections
    drawHorizontalLine(sectionHeight);
    drawHorizontalLine(2 * sectionHeight);

    // Top Section (A): Display "A" placeholder
    printCenteredText("A", 0, screenWidth, 0, sectionHeight, BLACK, 3);

    // Middle Section (B, C, D)
    int middleSectionStart = sectionHeight;
    int middleSectionEnd = 2 * sectionHeight;

    // Divide the middle section into left (B) and right sub-sections (C and D)
    int leftWidth = (3 * screenWidth) / 5; // Adjusted ratio for 3:2
    int rightWidth = screenWidth - leftWidth;

    drawVerticalLine(leftWidth, middleSectionStart, middleSectionEnd);

    // B Sub-section
    printCenteredText("B", 0, leftWidth, middleSectionStart, middleSectionEnd, BLACK, 2);

    // Right sub-section (C and D) divided horizontally
    int middleHorizontalLine = (middleSectionStart + middleSectionEnd) / 2;

    // C Sub-section
    printCenteredText("HUMINIT", leftWidth, screenWidth, middleSectionStart, middleHorizontalLine, BLACK, 2);

    // D Sub-section
    printCenteredText("STATE", leftWidth, screenWidth, middleHorizontalLine, middleSectionEnd, BLACK, 2);

    // Draw a horizontal line only within the right section (C and D)
    mylcd.Set_Draw_color(BLACK);
    mylcd.Draw_Line(leftWidth, middleHorizontalLine, screenWidth - 1, middleHorizontalLine);

    // Bottom Section (E): Display "E" placeholder
    printCenteredText("E", 0, screenWidth, 2 * sectionHeight, screenHeight, BLACK, 3);
}

void loop() {
    // No action required in loop
}
