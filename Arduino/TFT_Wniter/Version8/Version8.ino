#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library
#include "bitmap.h" // Include bitmap data

// LCD configuration for Mega2560 (model, cs, cd, wr, rd, reset)
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4);

// Define color values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Define thresholds for humidity levels
#define HUMIDITY_LOW 30
#define HUMIDITY_HIGH 70

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
    int textHeight = charHeight; // Single-line height

    int x = xStart + (xEnd - xStart - textWidth) / 2; // Center text horizontally
    int y = yStart + (yEnd - yStart - textHeight) / 2; // Center text vertically

    mylcd.Set_Text_colour(color);
    mylcd.Set_Text_Back_colour(WHITE);
    mylcd.Set_Text_Size(textSize);
    mylcd.Print_String(text, x, y);
}

// Function to print bold text in the center of a region
void printCenteredBoldText(const char* text, int xStart, int xEnd, int yStart, int yEnd, uint16_t color, uint8_t textSize) {
    int charWidth = 6 * textSize; // Approximate character width in pixels
    int charHeight = 8 * textSize; // Approximate character height in pixels
    int textWidth = charWidth * strlen(text); // Total text width based on number of characters
    int textHeight = charHeight; // Single-line height

    int x = xStart + (xEnd - xStart - textWidth) / 2; // Center text horizontally
    int y = yStart + (yEnd - yStart - textHeight) / 2; // Center text vertically

    mylcd.Set_Text_colour(color);
    mylcd.Set_Text_Back_colour(WHITE);
    mylcd.Set_Text_Size(textSize);

    // Draw the text multiple times with slight offsets for bold effect
    mylcd.Print_String(text, x, y);          // Original position
    mylcd.Print_String(text, x + 1, y);      // Slightly right
    mylcd.Print_String(text, x, y + 1);      // Slightly below
    mylcd.Print_String(text, x + 1, y + 1);  // Diagonal
}

// Function to determine the state based on humidity
const char* determineState(int humidity) {
    if (humidity < HUMIDITY_LOW) {
        return "Humidification";
    } else if (humidity > HUMIDITY_HIGH) {
        return "Ventilation";
    } else {
        return "Proper";
    }
}

// Function to draw a bitmap with scaling
void drawBitmapScaled(int16_t x, int16_t y, const unsigned char *bitmap, int16_t w, int16_t h, float scale) {
    int scaledWidth = w * scale;
    int scaledHeight = h * scale;

    for (int16_t j = 0; j < scaledHeight; j++) {
        for (int16_t i = 0; i < scaledWidth; i++) {
            int16_t originalX = i / scale;
            int16_t originalY = j / scale;
            uint16_t byteIndex = (originalY * w + originalX) / 8;
            uint8_t bitIndex = originalX % 8;
            uint8_t byte = pgm_read_byte(&bitmap[byteIndex]);
            if (byte & (0x80 >> bitIndex)) {
                mylcd.Set_Draw_color(BLACK);
                mylcd.Draw_Pixel(x + i, y + j);
            } else {
                mylcd.Set_Draw_color(WHITE);
                mylcd.Draw_Pixel(x + i, y + j);
            }
        }
    }
}

void displayWeatherBitmap(const char* weatherCode, int xStart, int xEnd, int yStart, int yEnd) {
    const unsigned char* bitmap;
    if (strcmp(weatherCode, "CLR") == 0) {
        bitmap = weather_sun;
    } else if (strcmp(weatherCode, "CLD") == 0) {
        bitmap = weather_cloud;
    } else if (strcmp(weatherCode, "RN") == 0) {
        bitmap = weather_rain;
    } else if (strcmp(weatherCode, "OVC") == 0) {
        bitmap = weather_cloudy;
    } else if (strcmp(weatherCode, "SN") == 0) {
        bitmap = weather_snow;
    } else {
        bitmap = weather_sun; // Default to sunny
    }

    int bitmapScaledWidth = BITMAP_WIDTH * 0.5;
    int bitmapScaledHeight = BITMAP_HEIGHT * 0.5;
    drawBitmapScaled((xStart + xEnd - bitmapScaledWidth) / 2, (yStart + yEnd - bitmapScaledHeight) / 2, bitmap, BITMAP_WIDTH, BITMAP_HEIGHT, 0.5);
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

    // Top Section (A): Display "weather_sun" bitmap scaled by 1.5x to fit within the section
    float scale = 1.5;
    int bitmapScaledWidth = BITMAP_WIDTH * scale;
    int bitmapScaledHeight = BITMAP_HEIGHT * scale;
    drawBitmapScaled((screenWidth - bitmapScaledWidth) / 2, (sectionHeight - bitmapScaledHeight) / 2, weather_sun, BITMAP_WIDTH, BITMAP_HEIGHT, scale);

    // Middle Section (B, C, D)
    int middleSectionStart = sectionHeight;
    int middleSectionEnd = 2 * sectionHeight;

    // Divide the middle section into left (B) and right sub-sections (C and D)
    int leftWidth = (3 * screenWidth) / 5; // Adjusted ratio for 3:2
    int rightWidth = screenWidth - leftWidth;

    drawVerticalLine(leftWidth, middleSectionStart, middleSectionEnd);

    // Mock data for current weather
    int currentTemperature = 25; // Example temperature in Celsius
    int currentHumidity = 65; // Example humidity in percentage

    // B Sub-section: Display temperature
    char temperatureText[16];
    sprintf(temperatureText, "%d °C", currentTemperature);

    printCenteredText(temperatureText, 0, leftWidth, middleSectionStart, middleSectionEnd, BLACK, 4);

    // Right sub-section (C and D) divided horizontally
    int middleHorizontalLine = (middleSectionStart + middleSectionEnd) / 2;

    // C Sub-section: Display humidity text and value
    int cSectionCenterX = (leftWidth + screenWidth) / 2;
    int cSectionHumidityTextY = middleSectionStart + 40; // Adjust Y position for text alignment
    int cSectionHumidityValueY = cSectionHumidityTextY + 30; // Place value slightly below text
    printCenteredText("Humidity", leftWidth, screenWidth, middleSectionStart, cSectionHumidityTextY, RED, 2);
    char humidityValue[16];
    sprintf(humidityValue, "%d%%", currentHumidity);
    
    // printCenteredText(humidityValue, leftWidth, screenWidth, cSectionHumidityTextY, cSectionHumidityValueY, BLACK, 2);
    printCenteredBoldText(humidityValue, leftWidth, screenWidth, cSectionHumidityTextY, cSectionHumidityValueY, BLACK, 2);


    // D Sub-section: Display state text and value
    int dSectionCenterX = (leftWidth + screenWidth) / 2;
    int dSectionStateTextY = middleHorizontalLine + 40; // Adjust Y position for text alignment
    int dSectionStateValueY = dSectionStateTextY + 30; // Place value slightly below text
    printCenteredText("STATE", leftWidth, screenWidth, middleHorizontalLine, dSectionStateTextY, BLUE, 2);
    const char* state = determineState(currentHumidity);
    
    printCenteredText(state, leftWidth, screenWidth, dSectionStateTextY, dSectionStateValueY, BLACK, 2);

    // Draw a horizontal line only within the right section (C and D)
    mylcd.Set_Draw_color(BLACK);
    mylcd.Draw_Line(leftWidth, middleHorizontalLine, screenWidth - 1, middleHorizontalLine);

    // Bottom Section (E): Divide into F, G, H
    int bottomSectionStart = 2 * sectionHeight;
    int bottomSectionEnd = screenHeight;
    int bottomSectionWidth = screenWidth / 3;

    drawVerticalLine(bottomSectionWidth, bottomSectionStart, bottomSectionEnd);
    drawVerticalLine(2 * bottomSectionWidth, bottomSectionStart, bottomSectionEnd);

    // Mock weather data
    const char* weatherData[3] = {"CLR", "CLD", "OVC"}; // Example data

    for (int i = 0; i < 3; i++) {
        int xStart = i * bottomSectionWidth;
        int xEnd = (i + 1) * bottomSectionWidth;
        if (weatherData[i] != NULL) {
            displayWeatherBitmap(weatherData[i], xStart, xEnd, bottomSectionStart, bottomSectionEnd);
        } else {
            printCenteredText("NO DATA", xStart, xEnd, bottomSectionStart, bottomSectionEnd, BLACK, 2);
        }
    }
}

void loop() {
    // No action required in loop
}
