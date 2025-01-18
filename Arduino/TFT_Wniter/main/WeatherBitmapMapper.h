#ifndef WEATHER_BITMAP_MAPPER_H
#define WEATHER_BITMAP_MAPPER_H

class WeatherBitmapMapper {
public:
    static const unsigned char* mapWeatherToBitmap(const char* weatherCode, bool hasError);
};

#endif
