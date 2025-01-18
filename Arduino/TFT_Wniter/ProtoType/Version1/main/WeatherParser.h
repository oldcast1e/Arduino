#ifndef WEATHERPARSER_H
#define WEATHERPARSER_H

#include <Arduino.h>
#include "WeatherDataManager.h"

class WeatherParser {
public:
    static void parseInput(const String& input, WeatherDataManager& manager) {
        manager.setErrorState(false);

        int dateEnd = input.indexOf('_');
        if (dateEnd == -1) {
            manager.setErrorState(true);
            return;
        }

        String dateStr = input.substring(0, dateEnd);
        manager.setCurrentDate(dateStr.c_str());

        String weatherData = input.substring(dateEnd + 1);
        int tIndex = weatherData.indexOf("T:");
        if (tIndex != -1) {
            float temp = weatherData.substring(tIndex + 2).toFloat();
            manager.setTemperatureB(temp);
        }

        int hIndex = weatherData.indexOf("H:");
        if (hIndex != -1) {
            int humidity = weatherData.substring(hIndex + 2).toInt();
            manager.setHumidityC(humidity);
        }
    }
};

#endif
