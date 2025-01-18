#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library
#include "bitmap.h" // Include bitmap data

// LCD configuration for Mega2560 (model, cs, cd, wr, rd, reset)
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4);

// Define color values
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define BLUE    0x001F

// Define thresholds for humidity levels
#define HUMIDITY_LOW 30
#define HUMIDITY_HIGH 70

// Time interval for updates
#define UPDATE_INTERVAL 5000 // 5 seconds

// Variables to store the current weather information
char weatherStateA[16] = "CLR"; // Default for A section
int temperatureB = 25; // Default for B section
int humidityC = 65; // Default humidity
char stateC[16] = "Proper"; // Default state
char weatherDataE[3][16] = {"CLR", "CLD", "OVC"}; // Default for F, G, H sections

unsigned long lastUpdate = 0;

// Function to draw horizontal and vertical lines
void drawHorizontalLine(int y) {
    mylcd.Set_Draw_color(BLACK);
    mylcd.Draw_Line(0, y, mylcd.Get_Display_Width() - 1, y);
}

void drawVerticalLine(int x, int yStart, int yEnd) {
    mylcd.Set_Draw_color(BLACK);
    mylcd.Draw_Line(x, yStart, x, yEnd);
}

// Function to clear a specific region
void clearRegion(int xStart, int xEnd, int yStart, int yEnd) {
    mylcd.Set_Draw_color(WHITE);
    for (int y = yStart; y <= yEnd; y++) {
        mylcd.Draw_Line(xStart, y, xEnd, y);
    }
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

// Function to map weather codes to bitmaps
const unsigned char* mapWeatherToBitmap(const char* weatherCode) {
    if (strcmp(weatherCode, "CLR") == 0) {
        return weather_sun;
    } else if (strcmp(weatherCode, "RN") == 0 || strcmp(weatherCode, "RS") == 0 ||
               strcmp(weatherCode, "SH") == 0 || strcmp(weatherCode, "DZ") == 0 || strcmp(weatherCode, "DS") == 0) {
        return weather_rain;
    } else if (strcmp(weatherCode, "SN") == 0 || strcmp(weatherCode, "FL") == 0) {
        return weather_snow;
    } else if (strcmp(weatherCode, "CLD") == 0) {
        return weather_cloudy;
    } else if (strcmp(weatherCode, "OVC") == 0) {
        return weather_cloud;
    } else {
        return weather_sun; // Default to sunny
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

// Function to update the display
void updateDisplay() {
    int screenHeight = mylcd.Get_Display_Height();
    int screenWidth = mylcd.Get_Display_Width();
    int sectionHeight = screenHeight / 3;

    // Draw dividing lines for sections
    drawHorizontalLine(sectionHeight); // Between A and B sections
    drawHorizontalLine(2 * sectionHeight); // Between D and E sections

    int leftWidth = (3 * screenWidth) / 5;
    int middleSectionStart = sectionHeight;
    int middleSectionEnd = 2 * sectionHeight;
    int middleHorizontalLine = (middleSectionStart + middleSectionEnd) / 2;

    // Draw lines for C and D subsections
    drawVerticalLine(leftWidth, middleSectionStart, middleSectionEnd);

    // Draw vertical lines to split the "E" section into F, G, H subsections
    int bottomSectionStart = 2 * sectionHeight;
    int bottomSectionEnd = screenHeight;
    int bottomSectionWidth = screenWidth / 3;
    for (int i = 1; i < 3; i++) {
        drawVerticalLine(i * bottomSectionWidth, bottomSectionStart, bottomSectionEnd);
    }

    // Top Section (A)
    float scale = 1.5;
    int bitmapScaledWidth = BITMAP_WIDTH * scale;
    int bitmapScaledHeight = BITMAP_HEIGHT * scale;
    const unsigned char* bitmapA = mapWeatherToBitmap(weatherStateA);
    clearRegion(0, screenWidth, 0, sectionHeight); // Clear previous content
    drawBitmapScaled((screenWidth - bitmapScaledWidth) / 2, (sectionHeight - bitmapScaledHeight) / 2, bitmapA, BITMAP_WIDTH, BITMAP_HEIGHT, scale);

    // Middle Section (B, C, D)
    // B Sub-section: Display temperature
    clearRegion(0, leftWidth, middleSectionStart, middleSectionEnd); // Clear B section
    char temperatureText[16];
    sprintf(temperatureText, "%d C", temperatureB);
    printCenteredText(temperatureText, 0, leftWidth, middleSectionStart, middleSectionEnd, BLACK, 4);

    // Right sub-section (C and D)
    printCenteredText("Humidity", leftWidth, screenWidth, middleSectionStart, middleSectionStart + 40, RED, 2);
    char humidityValue[16];
    sprintf(humidityValue, "%d%%", humidityC);
    printCenteredText(humidityValue, leftWidth, screenWidth, middleSectionStart + 40, middleSectionStart + 70, BLACK, 2);
    
    printCenteredText("STATE", leftWidth, screenWidth, middleHorizontalLine, middleHorizontalLine + 40, BLUE, 2);
    printCenteredText(stateC, leftWidth, screenWidth, middleHorizontalLine + 40, middleHorizontalLine + 70, BLACK, 2);

    // Bottom Section (E)
    for (int i = 0; i < 3; i++) {
        int xStart = i * bottomSectionWidth;
        int xEnd = (i + 1) * bottomSectionWidth;
        const unsigned char* bitmap = mapWeatherToBitmap(weatherDataE[i]);
        clearRegion(xStart, xEnd, bottomSectionStart, bottomSectionEnd); // Clear subsection
        drawBitmapScaled((xStart + xEnd - (BITMAP_WIDTH / 2)) / 2, (bottomSectionStart + bottomSectionEnd - (BITMAP_HEIGHT / 2)) / 2, bitmap, BITMAP_WIDTH, BITMAP_HEIGHT, 0.5);
    }

    // Redraw section dividing lines to ensure they remain visible
    drawHorizontalLine(sectionHeight);
    drawHorizontalLine(2 * sectionHeight);
    drawVerticalLine(leftWidth, middleSectionStart, middleSectionEnd);
    for (int i = 1; i < 3; i++) {
        drawVerticalLine(i * bottomSectionWidth, bottomSectionStart, bottomSectionEnd);
    }
}

// Function to parse serial input
void parseSerialInput(String input) {
    Serial.println("Parsing Serial Input:");
    Serial.println(input);

    if (input.startsWith("CW|")) {
        // Update current weather for section A
        int index = input.indexOf('|');
        if (index > 0) {
            String weather = input.substring(index + 3, index + 6);
            strncpy(weatherStateA, weather.c_str(), sizeof(weatherStateA));
            Serial.print("Updated A section weather: ");
            Serial.println(weatherStateA);
        }
    }

    // Update B section temperature
    int tIndex = input.indexOf("T:");
    if (tIndex > 0) {
        int endIndex = input.indexOf('|', tIndex);
        temperatureB = input.substring(tIndex + 2, endIndex).toInt();
        Serial.print("Updated B section temperature: ");
        Serial.println(temperatureB);
    }

    // Update C section humidity
    int hIndex = input.indexOf("H:");
    if (hIndex > 0) {
        int endIndex = input.indexOf('|', hIndex);
        humidityC = input.substring(hIndex + 2, endIndex).toInt();
        strncpy(stateC, determineState(humidityC), sizeof(stateC));
        Serial.print("Updated C section humidity: ");
        Serial.println(humidityC);
        Serial.print("Updated C section state: ");
        Serial.println(stateC);
    }

    // Update E section (F, G, H subsections)
    for (int i = 0; i < 3; i++) {
        int timeIndex = input.indexOf(String(i * 100 + 100).c_str());
        if (timeIndex > 0) {
            int wIndex = input.indexOf("W:", timeIndex);
            int wEndIndex = input.indexOf('|', wIndex);
            String weather = input.substring(wIndex + 2, wEndIndex);
            strncpy(weatherDataE[i], weather.c_str(), sizeof(weatherDataE[i]));
            Serial.print("Updated E section (F, G, H) weather: ");
            Serial.println(weatherDataE[i]);
        } else {
            strncpy(weatherDataE[i], "UNK", sizeof(weatherDataE[i]));
        }
    }
}

void setup() {
    mylcd.Init_LCD();
    mylcd.Fill_Screen(WHITE);
    Serial.begin(9600);
    updateDisplay();
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        parseSerialInput(input);
        updateDisplay();
        delay(UPDATE_INTERVAL); // Prevent rapid updates
    }
}
