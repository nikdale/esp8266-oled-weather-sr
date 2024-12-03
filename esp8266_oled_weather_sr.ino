#include <U8g2lib.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h"

// OLED settings
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ OLED_CLOCK, /* data=*/ OLED_DATA, /* reset=*/ U8X8_PIN_NONE);

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void fetchWeather() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    return;
  }

  HTTPClient http;
  WiFiClient client;
  String url = String("http://api.openweathermap.org/data/2.5/weather?q=") + 
               OWM_LOCATION + "&units=" + OWM_UNITS + "&appid=" + OWM_API_KEY;
  http.begin(client, url);
  
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      DynamicJsonDocument doc(2048);
      DeserializationError error = deserializeJson(doc, payload);
      
      if (error) {
        Serial.println("Failed to parse JSON!");
        return;
      }

      String weather = doc["weather"][0]["main"].as<String>();
      float temp = doc["main"]["temp"];
      int humidity = doc["main"]["humidity"];
      float windSpeed = doc["wind"]["speed"];

      // Display data on the OLED screen
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_unifont_t_cyrillic);
        u8g2.drawUTF8(0, 12, (DISPLAY_CITY_LABEL + String(DISPLAY_CITY)).c_str());
        u8g2.drawUTF8(0, 24, (DISPLAY_WEATHER_LABEL + weather).c_str());
        u8g2.drawUTF8(0, 36, (DISPLAY_TEMP_LABEL + String(temp, 1) + DISPLAY_TEMP_UNIT).c_str());
        u8g2.drawUTF8(0, 48, (DISPLAY_HUMID_LABEL + String(humidity) + DISPLAY_HUMID_UNIT).c_str());
        u8g2.drawUTF8(0, 60, (DISPLAY_WIND_LABEL + String(windSpeed, 1) + DISPLAY_WIND_UNIT).c_str());
      } while (u8g2.nextPage())
    }
  } else {
    Serial.print("HTTP request failed: ");
    Serial.println(httpCode);
  }
  http.end();
}

void setup() {
  Serial.begin(115200);
  
  // Initialize OLED with UTF-8 support
  u8g2.begin();
  u8g2.enableUTF8Print();
  
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_unifont_t_cyrillic);
    u8g2.drawUTF8(0, 32, DISPLAY_INIT_TEXT);
  } while (u8g2.nextPage());
  
  connectToWiFi();
}

void loop() {
  fetchWeather();
  delay(UPDATE_INTERVAL);
}