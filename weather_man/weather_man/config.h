#ifndef CONFIG_H
#define CONFIG_H

// Comment this line out or change it to 0 to disable the monitor
#define ENABLE_CPU_MONITOR 0

// adhering to modern c++ by using constexpr
namespace Config {

  namespace System {
        constexpr unsigned long SERIAL_BAUD = 115200;
    }
  namespace Display {
    // OLED Display definitions
    constexpr int SCREEN_HEIGHT = 64; 
    constexpr int SCREEN_WIDTH = 128; 

    constexpr uint8_t i2cAddr = 0x3c;

  }
  namespace Pins {
    // Pin definitions
    constexpr int redledPin = 5;   

  }
  
  namespace WeatherApi {
    // https://openweathermap.org/api/one-call-4?collection=one_call_api#hourly_how
    constexpr const char* HOST = "https://api.openweathermap.org/data/4.0/onecall/timeline/1h";
    //constexpr const char* CITY = "London,uk";

    // coordinates for Brussels/Evere region
    constexpr float LATITUDE  = 50.87; 
    constexpr float LONGITUDE = 4.40;
  }
  namespace Timing {
    constexpr unsigned long WEATHER_FETCH_INTERVAL = 60 * 1000 *10; // 10mins
  }
}




#endif