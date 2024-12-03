// config.h
#ifndef CONFIG_H
#define CONFIG_H

// WiFi settings
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// OpenWeatherMap API settings
#define OWM_API_KEY "YOUR_API_KEY"
#define OWM_LOCATION "Zeleznik"  // Your city
#define OWM_UNITS "metric"       // Use "metric" for Celsius, "imperial" for Fahrenheit

// Display text (Serbian Cyrillic)
#define DISPLAY_CITY "Железник"  // Your city name in Cyrillic
#define DISPLAY_CITY_LABEL "Град: "
#define DISPLAY_WEATHER_LABEL "Време: "
#define DISPLAY_TEMP_LABEL "Темп: "
#define DISPLAY_HUMID_LABEL "Влажност: "
#define DISPLAY_WIND_LABEL "Ветар: "
#define DISPLAY_TEMP_UNIT "°C"
#define DISPLAY_HUMID_UNIT "%"
#define DISPLAY_WIND_UNIT "м/с"
#define DISPLAY_INIT_TEXT "Иницијализација..."

// Hardware pins
#define OLED_CLOCK 12  // SCL pin
#define OLED_DATA 14   // SDA pin

// Update interval
#define UPDATE_INTERVAL 60000  // Update every 60 seconds (in milliseconds)

#endif