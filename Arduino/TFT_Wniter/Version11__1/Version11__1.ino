#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library
#include <Wire.h>        // I2C library for communication
#include "bitmap.h"      // Include bitmap data

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
char currentDate[32] = "";      // Date string (e.g., "2025.1.10 11:51")
char weatherStateA[16] = "CLR"; // Current weather
char futureWeather[3][16];      // Weather for 1, 2, 3 hours

unsigned long lastUpdate = 0;

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

// Function to update the display
void updateDisplay() {
    mylcd.Fill_Screen(WHITE);
    mylcd.Set_Text_colour(BLACK);
    mylcd.Set_Text_Back_colour(WHITE);
    mylcd.Set_Text_Size(2);

    // Display current date
    mylcd.Print_String(currentDate, 10, 10);

    // Display current weather
    const unsigned char* bitmapA = mapWeatherToBitmap(weatherStateA);
    drawBitmapScaled(100, 50, bitmapA, BITMAP_WIDTH, BITMAP_HEIGHT, 1.5);

    // Display future weather
    for (int i = 0; i < 3; i++) {
        char futureBuffer[32];
        sprintf(futureBuffer, "%d hr: %s", i + 1, futureWeather[i]);
        mylcd.Print_String(futureBuffer, 10, 150 + (i * 30));
    }
}

// Function to parse input data
void parseInputData(String input) {
    Serial.println("Parsing Input:");
    Serial.println(input);

    // Parse the date and time
    int dateEnd = input.indexOf('_');
    String dateStr = input.substring(0, dateEnd);
    strncpy(currentDate, dateStr.c_str(), sizeof(currentDate));

    // Extract current hour
    int currentHour = dateStr.substring(dateStr.lastIndexOf('.') + 1, dateStr.lastIndexOf(':')).toInt();

    // Parse the weather data
    String weatherData = input.substring(dateEnd + 1);

    // Extract current weather (CW|W:XXX)
    int currentWeatherStart = weatherData.indexOf("CW|W:") + 5;
    int currentWeatherEnd = weatherData.indexOf('|', currentWeatherStart);
    String currentWeather = weatherData.substring(currentWeatherStart, currentWeatherEnd);
    strncpy(weatherStateA, currentWeather.c_str(), sizeof(weatherStateA));

    // Extract future weather for 1, 2, 3 hours
    for (int i = 0; i < 3; i++) {
        int futureHour = (currentHour + i + 1) % 24; // Wrap around at 24 hours
        char futureKey[8];
        sprintf(futureKey, "$%02d00|W:", futureHour);
        int futureStart = weatherData.indexOf(futureKey);
        if (futureStart != -1) {
            futureStart += strlen(futureKey);
            int futureEnd = weatherData.indexOf('|', futureStart);
            String futureWeatherStr = weatherData.substring(futureStart, futureEnd);
            strncpy(futureWeather[i], futureWeatherStr.c_str(), sizeof(futureWeather[i]));
        } else {
            strncpy(futureWeather[i], "UNK", sizeof(futureWeather[i])); // Unknown if not found
        }
    }

    // Debugging output
    Serial.println(currentDate);
    Serial.print("Current Time: ");
    Serial.println(currentDate);
    Serial.print("Current Weather: ");
    Serial.println(weatherStateA);
    for (int i = 0; i < 3; i++) {
        Serial.print(i + 1);
        Serial.print(" hour ahead: ");
        Serial.println(futureWeather[i]);
    }
}

// Function to read data via I2C
void receiveI2CData() {
    if (Wire.available()) {
        String inputData = "";
        while (Wire.available()) {
            char c = Wire.read();
            inputData += c;
        }
        parseInputData(inputData);
        updateDisplay();
    }
}

void setup() {
    mylcd.Init_LCD();
    mylcd.Fill_Screen(WHITE);
    Serial.begin(9600);
    Wire.begin(8); // I2C slave address
    Wire.onReceive(receiveI2CData);
    updateDisplay();
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        parseInputData(input);
        updateDisplay();
        delay(UPDATE_INTERVAL);
    }
}
