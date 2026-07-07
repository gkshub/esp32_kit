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
    constexpr const char* HOST = "http://api.openweathermap.org/data/2.5/weather";
    constexpr const char* CITY = "London,uk";
  }
  namespace Timing {
    constexpr unsigned long WEATHER_FETCH_INTERVAL = 60 * 1000 *10; // 10mins
  }
}




#endif