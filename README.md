# ESP32 Starter Kit

🚀 **IoT Development Platform for ESP32-S3 Microcontrollers**

A modular IoT development environment featuring sensor integration, OLED display, WiFi connectivity, and event-driven architecture.

---

## 📋 Overview

The ESP32 Starter Kit is a comprehensive IoT platform built for ESP32-S3 microcontrollers. It provides a component-based architecture with an event bus system for inter-component communication, supporting multiple sensors, wireless connectivity, and real-time data processing.

---

## ✨ Key Features

- **🔧 Hardware Abstraction**: ESP32-S3 low-power microcontroller support
- **🌡️ Multi-Sensor Integration**: Temperature, fire, rain, light, motion, ultrasonic, IR sensors
- **🔊 Audio Output**: Buzzer with melody playback (pb component)
- **📱 OLED Display**: SSD1306 I2C display with status indicators
- **🌐 Wireless Connectivity**: WiFi with HTTP client and Telegram integration
- **⏰ Time Synchronization**: SNTP/NTP integration
- **🔍 Service Discovery**: MDNS support (dnsm component)
- **🎛️ Modular Architecture**: Component-based design with event bus system
- **📊 Event Bus System**: Queue-based inter-component messaging
- **💾 Persistent Storage**: NVS for configuration persistence
- **🎚️ PWM LED Control**: LED dimming and effects

---

## 🛠️ Supported Components

### Sensors & Inputs
| Component | Function | Status |
|-----------|----------|--------|
| **temp** | Temperature readings | ✅ Active |
| **fire** | Fire/smoke detection | ✅ Active |
| **rain** | Rain detection | ✅ Active |
| **ultra** | Ultrasonic distance measurement | ✅ Active |
| **ldr** | Light/dark detection | ✅ Active |
| **motion** | PIR motion detection | ✅ Active |
| **ir** | Infrared receiver | ✅ Active |
| **button** | User button input | ✅ Active |

### Output & Interface
| Component | Function | Features |
|-----------|----------|----------|
| **oled** | SSD1306 I2C display | Status icons, text output |
| **led** | LED indicators | GPIO control |
| **led_pwm** | LED PWM control | Dimming, effects |
| **pb** | Buzzer/Piezo | Melody playback |
| **http** | HTTP client | RESTful API, Telegram |

### System Services
| Service | Purpose | Implementation |
|---------|---------|----------------|
| **wifi** | Network connectivity | Automatic connection handling |
| **nvs** | Non-volatile storage | Configuration persistence |
| **sntp** | Time synchronization | NTP server integration |
| **bus** | Event bus | Queue-based messaging |
| **dnsm** | Network discovery | MDNS service advertising |
| **adc** | ADC services | Analog reading utilities |
| **move_avg** | Data smoothing | Moving average filter |

---

## 🚀 Quick Start

### Prerequisites
- ESP-IDF v6.0+ development environment (IDF_PATH must be set)
- ESP32-S3 development board
- Sensors and peripherals per your configuration

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/dbunt1tled/esp32-starter-kit.git
   cd esp32-starter-kit
   ```

2. **Set up ESP-IDF environment**
   ```bash
   # Adjust path to your ESP-IDF installation
   export IDF_PATH=/Users/admin/.espressif/v6.0/esp-idf
   . $IDF_PATH/export.sh
   ```

3. **Configure local settings**
   ```bash
   # Create local config (never commit this file)
   cp main/components/cfg/configure_loc.h.example main/components/cfg/configure_loc.h
   # Edit with your WiFi credentials and API tokens
   # configure.h includes configure_loc.h when USE_LOCAL_CONFIG is defined
   ```

4. **Build and flash**
   ```bash
   idf.py build
   idf.py flash monitor
   ```

---

## 📁 Project Structure

```
esp_start_kit/
├── README.md                    # This documentation
├── CMakeLists.txt               # Main build configuration
├── sdkconfig                    # ESP-IDF configuration
├── version.txt                  # Project version (auto-bumped on build)
├── .clang-format                # Code formatting rules
├── main/                        # Main application
│   ├── esp_start_kit_main.c     # Application entry point
│   ├── CMakeLists.txt           # Component build config
│   ├── components/              # Hardware components
│   │   ├── bus/                # Event bus system
│   │   ├── button/             # Button handling
│   │   ├── cfg/                # Configuration (configure.h, configure_loc.h)
│   │   ├── dnsm/               # MDNS service
│   │   ├── fire/               # Fire sensor
│   │   ├── http/               # HTTP client
│   │   ├── icons/              # Display icons
│   │   ├── ir/                 # IR receiver
│   │   ├── ldr/                # Light sensor
│   │   ├── led/                # LED control
│   │   ├── led_pwm/            # PWM LED control
│   │   ├── mbus/               # Modbus (or measurement bus)
│   │   ├── motion/             # Motion detection
│   │   ├── nvs/                # Non-volatile storage
│   │   ├── oled/               # OLED display
│   │   ├── pb/                 # Buzzer melody playback
│   │   ├── rain/               # Rain sensor
│   │   ├── sntp/               # Time synchronization
│   │   ├── temp/               # Temperature sensor
│   │   ├── ultra/              # Ultrasonic sensor
│   │   └── wifi/               # WiFi management
│   └── services/                # Utility services
│       ├── adc/                # ADC utilities
│       └── move_avg/           # Moving average filter
├── scripts/                     # Utility scripts
│   └── bump_version.py         # Auto-version bump on build
└── managed_components/          # ESP-IDF component manager dependencies
```

---

## ⚙️ Build System

### Build Commands
```bash
# Load ESP-IDF environment first (required)
# export IDF_PATH=/Users/admin/.espressif/v6.0/esp-idf
# . $IDF_PATH/export.sh

idf.py clean              # Clean build artifacts
idf.py build              # Build project (auto-bumps version via bump_version.py)
idf.py flash monitor      # Flash and open serial monitor
idf.py menuconfig         # Interactive configuration
```

### Dependencies
The project uses ESP-IDF components and requires:
- `esp_driver_gpio` - GPIO operations
- `esp_driver_ledc` - PWM/LED control
- `esp_wifi` - WiFi functionality
- `esp_netif` - Network interface
- `esp_http_client` - HTTP communications
- `nvs_flash` - Non-volatile storage
- `mbedtls` - Security layer

---

## 🔧 Configuration

Configuration is managed in `main/components/cfg/`:

- **configure.h** - Main configuration, includes `configure_loc.h` when `USE_LOCAL_CONFIG` is defined
- **configure_loc.h** - Local overrides (WiFi credentials, API tokens) - **never commit this file**

To customize:
1. Create `configure_loc.h` with your local settings
2. Ensure `USE_LOCAL_CONFIG` is defined in `configure.h` (enabled by default)
3. Add your WiFi credentials, Telegram tokens, and pin assignments

---

## 🔩 Hardware Setup

### Required Components
- ESP32-S3 development board
- Temperature sensor
- Fire/smoke sensor
- Rain sensor
- Ultrasonic distance sensor (HC-SR04 or compatible)
- LDR (Light Dependent Resistor)
- PIR motion sensor
- IR receiver module
- OLED display (SSD1306 I2C)
- Push button
- LED indicators
- Buzzer/Piezo speaker

### Pin Configuration
Default pin assignments (configurable in `configure.h`):
- Button: GPIO 0
- LED: GPIO 2
- Temperature Sensor: GPIO 4
- LDR: ADC1 channel
- PIR Motion: GPIO 5
- IR Receiver: GPIO 6
- Ultrasonic Trigger/Echo: Configurable
- OLED Display: I2C SDA/SCL pins
- Buzzer: PWM-capable GPIO

---

## 📊 Component Architecture

### Event Bus System
The kit uses a centralized event bus for component communication:
- **Queue-based messaging** for reliable data transfer
- **Handler registration** for modular event processing
- **Configurable delays** and queue size for performance tuning

### Component Lifecycle
1. **Initialization**: Hardware setup and configuration
2. **Registration**: Event handlers registered with bus
3. **Processing**: Continuous monitoring and data collection
4. **Communication**: Event-driven data sharing via bus

---

## 🧪 Development & Testing

### Debugging
```bash
# Monitor serial output
idf.py monitor

# Enable logging levels
idf.py menuconfig → Component config → Log output
```

### Version Management
Version is tracked in `version.txt` (format: `0.0.1+build-NN`).
The version is automatically bumped on each build via `scripts/bump_version.py`.

Current version: **0.0.1+build-19**

---

## 🌐 External Resources

- **Documentation**: Component-specific docs in `main/components/<name>/`
- **ESP-IDF Guide**: [Official ESP-IDF Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/)

---

## 🤝 Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Follow the coding style (4-space indent, snake_case, `//` comments)
4. Test thoroughly on hardware
5. Submit a pull request

### Commit Message Style
Follow the existing convention:
- `✨ feat(...)` - New features
- `🔧 feat(...)` - Configuration/system features
- `♻️ refactor(...)` - Code refactoring

---

## 📄 License

This project is licensed under the MIT License (LICENSE file to be added).

---

## 👥 Development Team

- **Deni** - Main Developer & Architecture

---

## 🔍 Troubleshooting

### Common Issues
- **WiFi Connection**: Check credentials in `configure_loc.h` and network availability
- **Sensor Readings**: Verify pin connections and power supply
- **Display Issues**: Check I2C connections and address (typically 0x3C)
- **Build Errors**: Ensure ESP-IDF environment is properly loaded (IDF_PATH set)
- **Version Bump Fails**: Check `scripts/bump_version.py` is executable

### Support
For issues and questions:
- Check component documentation in `main/components/<name>/`
- Review ESP-IDF official documentation
- Open an issue on the project repository

---

*Current Version: 0.0.1+build-19*
*Last Updated: 2026-05-07*