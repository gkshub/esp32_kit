#include "weather_manager.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"
#include "secrets.h"

static void WeatherTask(void* pvParameters) {
  DisplayManager* display = reinterpret_cast<DisplayManager*>(pvParameters);

  // Connect to WiFi
  Serial.println(F("Connecting to WiFi..."));
  WiFi.begin(Config::WiFi::SSID, Config::WiFi::PASSWORD);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    Serial.print(F("."));
    vTaskDelay(pdMS_TO_TICKS(500));
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("\nWiFi connection failed"));
    // Still continue; sometimes WiFi may come up later
  } else {
    Serial.println(F("\nWiFi connected"));
    Serial.print(F("IP: "));
    Serial.println(WiFi.localIP());
  }

  for(;;) {
    if (WiFi.status() == WL_CONNECTED) {
      // Build URL using OpenWeatherMap current weather endpoint for simplicity
      String url = String("https://api.openweathermap.org/data/2.5/weather?lat=")
        + String(Config::WeatherApi::LATITUDE, 2)
        + String("&lon=") + String(Config::WeatherApi::LONGITUDE, 2)
        + String("&units=metric&appid=") + String(Config::WeatherApi::API_KEY);

      HTTPClient http;
      http.begin(url);
      int httpCode = http.GET();

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();

        // Parse JSON (small doc)
        StaticJsonDocument<4096> doc;
        DeserializationError err = deserializeJson(doc, payload);
        if (!err) {
          float temp = NAN;
          const char* desc = "";

          if (doc.containsKey("main") && doc["main"].containsKey("temp")) {
            temp = doc["main"]["temp"].as<float>();
          }

          if (doc.containsKey("weather") && doc["weather"][0].containsKey("description")) {
            desc = doc["weather"][0]["description"].as<const char*>();
          }

          Serial.print(F("Weather: "));
          Serial.print(temp);
          Serial.print(F(" C - "));
          Serial.println(desc);

          if (display) display->showWeather(temp, desc);

        } else {
          Serial.print(F("JSON parse error: "));
          Serial.println(err.c_str());
        }

      } else {
        Serial.print(F("HTTP error: "));
        Serial.println(httpCode);
      }

      http.end();
    } else {
      Serial.println(F("WiFi not connected, retrying connection"));
      WiFi.reconnect();
    }

    // Sleep until next fetch
    vTaskDelay(pdMS_TO_TICKS(Config::Timing::WEATHER_FETCH_INTERVAL));
  }
}

void startWeatherTask(DisplayManager* displayPtr) {
  xTaskCreatePinnedToCore(
    WeatherTask,
    "Weather_Fetch",
    8192,
    displayPtr,
    1,
    NULL,
    1
  );
}
