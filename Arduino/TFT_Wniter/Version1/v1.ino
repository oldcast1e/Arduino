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
    mylcd.Set_Draw_color(WHITE);
    mylcd.Draw_Line(0, y, mylcd.Get_Display_Width() - 1, y);
}

// Function to draw a vertical line
void drawVerticalLine(int x, int yStart, int yEnd) {
    mylcd.Set_Draw_color(WHITE);
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
    mylcd.Set_Text_Back_colour(BLACK);
    mylcd.Set_Text_Size(textSize);
    mylcd.Print_String(text, x, y);
}

void setup() {
    mylcd.Init_LCD();
    mylcd.Fill_Screen(BLACK);

    int screenHeight = mylcd.Get_Display_Height();
    int screenWidth = mylcd.Get_Display_Width();

    // Divide the screen into 3 vertical sections
    int sectionHeight = screenHeight / 3;

    // Draw horizontal dividing lines
    drawHorizontalLine(sectionHeight);
    drawHorizontalLine(2 * sectionHeight);

    // First Section: Display "SUN" in red
    printCenteredText("SUN", 0, screenWidth, 0, sectionHeight, RED, 3);

    // Second Section: Subdivide horizontally into 3 parts
    int subSectionWidth = screenWidth / 3;

    // Draw vertical dividing lines
    drawVerticalLine(subSectionWidth, sectionHeight, 2 * sectionHeight);
    drawVerticalLine(2 * subSectionWidth, sectionHeight, 2 * sectionHeight);

    // Display text in each horizontal subsection
    printCenteredText("25", 0, subSectionWidth, sectionHeight, 2 * sectionHeight, WHITE, 2);
    printCenteredText("HUMINIT", subSectionWidth, 2 * subSectionWidth, sectionHeight, 2 * sectionHeight, WHITE, 2);
    printCenteredText("STATE", 2 * subSectionWidth, screenWidth, sectionHeight, 2 * sectionHeight, WHITE, 2);

    // Third Section: Subdivide horizontally into 3 parts
    drawVerticalLine(subSectionWidth, 2 * sectionHeight, screenHeight);
    drawVerticalLine(2 * subSectionWidth, 2 * sectionHeight, screenHeight);

    // Display text in each horizontal subsection
    printCenteredText("06", 0, subSectionWidth, 2 * sectionHeight, screenHeight, WHITE, 2);
    printCenteredText("12", subSectionWidth, 2 * subSectionWidth, 2 * sectionHeight, screenHeight, WHITE, 2);
    printCenteredText("18", 2 * subSectionWidth, screenWidth, 2 * sectionHeight, screenHeight, WHITE, 2);
}

void loop() {
    // No action required in loop
}
