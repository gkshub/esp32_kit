# Weather Man ESP32 Project Requirements

## Overview

An ESP32-based weather display application that connects to WiFi, fetches weather data from OpenWeatherMap, and renders the current conditions on an SSD1306 OLED display.

## Functional Requirements

1. WiFi Connectivity
   - Connect to a configurable WiFi SSID and password stored in `secrets.h`.
   - Retry WiFi connection when the network is unavailable.
   - Log connection status and IP address to the serial console.

2. Weather Data Fetching
   - Fetch current weather data from OpenWeatherMap using the configured API key.
   - Use the configured latitude and longitude values from `config.h`.
   - Request weather in metric units.
   - Repeat weather fetch at the interval defined by `Config::Timing::WEATHER_FETCH_INTERVAL`.

3. Weather Parsing and Display
   - Parse the JSON response to extract at least:
     - Current temperature
     - Weather description
   - Render weather data on the OLED display using the `DisplayManager`.
   - Display a user-friendly summary of the current conditions.

4. Display Management
   - Initialize the SSD1306 display during setup.
   - Provide a reusable `DisplayManager` abstraction for rendering.
   - Support a welcome screen or basic UI while waiting for weather data.

5. Task Management and Responsiveness
   - Use FreeRTOS tasks to separate display animation, LED blinking, weather fetching, and optional CPU monitoring.
   - Ensure the main loop stays idle or minimal.
   - Prevent blocking delays from interfering with other tasks.

6. Configuration and Secrets
   - Keep WiFi credentials and API key out of version control via `secrets.h`.
   - Provide `secrets.h.example` with placeholder values for onboarding.
   - Keep API endpoint, coordinates, and timing constants in `config.h`.

7. Error Handling and Logging
   - Log HTTP response codes and JSON parse errors to serial.
   - Continue retrying even after transient failures.
   - Display fallback or cached state if weather fetch fails.

## Non-functional Requirements

- Code should compile for the ESP32 Arduino platform.
- Use standard Arduino libraries and avoid unnecessary dependencies.
- Keep the implementation modular and maintainable.
- Keep configuration centralized in `config.h` and `secrets.h`.
- Provide clear documentation of implementation status and requirements.

## Project Artifacts

- `weather_man.ino`
- `config.h`
- `display_manager.h`
- `display_manager.cpp`
- `weather_manager.h`
- `weather_manager.cpp`
- `secrets.h`
- `secrets.h.example`
- `plan/IMPLEMENTATION_PLAN.md`
- `requirements/REQUIREMENTS.md`

## Future Enhancements

- Add humidity, pressure, and sunrise/sunset display.
- Add weather icons or graphics for conditions.
- Add a settings mode for selecting location or units.
- Add improved WiFi connection state UI.
