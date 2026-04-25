# ESP32 Starter Kit

🚀 **IoT Development Platform for ESP32-S3 Microcontrollers**

A comprehensive, modular IoT development environment featuring hardware abstraction, sensor integration, and real-time data processing capabilities.

---

## 📋 Overview

The ESP32 Starter Kit is an advanced IoT development platform designed for ESP32-S3 microcontrollers. Built for real-time IoT applications, it provides a modular architecture supporting multiple sensors, wireless connectivity, and display capabilities.

---

## ✨ Key Features

- **🔧 Hardware Abstraction**: Efficient low-power microcontroller support
- **🌡️ Multi-Sensor Integration**: Temperature, humidity, light, motion, and IR sensors
- **📱 OLED Display**: High-contrast display with centered text output
- **🌐 Wireless Connectivity**: WiFi integration with HTTP client capabilities
- **⏰ Time Synchronization**: SNTP/NTP integration for accurate timestamps
- **🔍 Service Discovery**: MDNS support for local network discovery
- **🎛️ Modular Architecture**: Component-based design for easy customization
- **📊 Event Bus System**: Efficient inter-component communication

---

## 🛠️ Supported Components

### Sensors & Inputs
| Component | Function | Status |
|-----------|----------|--------|
| **Temperature Sensor** | DHT-based temperature readings | ✅ Active |
| **Humidity Sensor** | DHT-based humidity monitoring | ✅ Active |
| **LDR Sensor** | Light/dark ratio detection | ✅ Active |
| **Motion Sensor** | PIR-based movement detection | ⚠️ Configurable |
| **IR Receiver** | Infrared signal reception | ✅ Active |
| **Button Input** | User interaction handling | ✅ Active |

### Output & Interface
| Component | Function | Features |
|-----------|----------|----------|
| **OLED Display** | Visual output interface | Centered text, contrast control |
| **LED Indicators** | Status and feedback | PWM support available |
| **HTTP Client** | Web service integration | RESTful API communication |

### System Services
| Service | Purpose | Implementation |
|---------|---------|----------------|
| **WiFi Manager** | Network connectivity | Automatic connection handling |
| **NVS Storage** | Non-volatile data storage | Configuration persistence |
| **SNTP Client** | Time synchronization | NTP server integration |
| **Event Bus** | Component communication | Queue-based messaging |
| **MDNS Service** | Network discovery | Local service advertising |

---

## 🎥 Video Demonstration

### Hardware in Action

Watch the ESP32 Starter Kit in action with sensor readings and display output:

[📹 View Demo Video](assets/esp32.mp4)

> **Note**: The video demonstrates real-time temperature and humidity sensor readouts on the OLED display, showcasing the kit's data acquisition and visualization capabilities.

---

## 🚀 Quick Start

### Prerequisites
- ESP-IDF development environment
- ESP32-S3 development board
- Required sensors and peripherals

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/esp-start-kit/esp_start_kit.git
   cd esp_start_kit
   ```

2. **Configure the project**
   ```bash
   # Create configuration file
   touch main/components/cfg/configure.h
   
   # Edit configuration with your WiFi credentials and settings
   # Configure: WIFI_SSID, WIFI_PASSWORD, sensor pins, etc.
   ```

3. **Build and flash**
   ```bash
   # Build the project
   idf.py build
   
   # Flash to device
   idf.py flash monitor
   ```

### Configuration

Edit `main/components/cfg/configure.h` to customize:
- WiFi credentials
- GPIO pin assignments
- Sensor configurations
- Display settings

---

## 📁 Project Structure

```
esp_start_kit/
├── README.md                    # This documentation
├── CMakeLists.txt              # Main build configuration
├── sdkconfig                   # ESP-IDF configuration
├── assets/                     # Media files
│   └── esp32.mp4               # Demo video
├── main/                       # Main application
│   ├── esp_start_kit_main.c    # Application entry point
│   ├── CMakeLists.txt          # Component build config
│   └── components/             # Hardware components
│       ├── bus/               # Event bus system
│       ├── button/            # Button handling
│       ├── cfg/               # Configuration management
│       ├── dnsm/              # MDNS service
│       ├── http/              # HTTP client
│       ├── icons/             # Display icons
│       ├── ir/                # IR receiver
│       ├── ldr/               # Light sensor
│       ├── led/               # LED control
│       ├── led_pwm/           # PWM LED control
│       ├── motion/            # Motion detection
│       ├── nvs/               # Non-volatile storage
│       ├── oled/              # OLED display
│       ├── sntp/              # Time synchronization
│       ├── temp/              # Temperature sensor
│       └── wifi/              # WiFi management
├── scripts/                    # Utility scripts
│   └── bump_version.py        # Version management
└── version.txt                 # Project version
```

---

## ⚙️ Build System

### Build Commands
```bash
# Clean build
idf.py clean

# Build project
idf.py build

# Flash and monitor
idf.py flash monitor

# Build only
idf.py app

# Menu configuration
idf.py menuconfig
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

## 🔧 Hardware Setup

### Required Components
- ESP32-S3 development board
- DHT22/DHT11 temperature & humidity sensor
- LDR (Light Dependent Resistor)
- PIR motion sensor
- IR receiver module
- OLED display (SSD1306 or compatible)
- Push button
- LED indicators

### Pin Configuration
Default pin assignments (configurable in `configure.h`):
- Button: GPIO 0
- LED: GPIO 2
- DHT Sensor: GPIO 4
- LDR: ADC1_CH0 (GPIO 1)
- PIR Motion: GPIO 5
- IR Receiver: GPIO 6
- OLED Display: I2C SDA/CLK pins

---

## 📊 Component Architecture

### Event Bus System
The kit uses a centralized event bus for component communication:
- **Queue-based messaging** for reliable data transfer
- **Handler registration** for modular event processing
- **Configurable delay** and queue size for performance tuning

### Component Lifecycle
1. **Initialization**: Hardware setup and configuration
2. **Registration**: Event handlers registered with bus
3. **Processing**: Continuous monitoring and data collection
4. **Communication**: Event-driven data sharing

---

## 🧪 Development & Testing

### Debugging
```bash
# Monitor serial output
idf.py monitor

# Enable logging levels
idf.py menuconfig → Component config → Log output
```

### Testing Features
- Sensor data validation
- Display output verification
- Network connectivity testing
- Event bus functionality

---

## 🌐 External Resources

- **Project Tracking**: [Linear Dashboard](https://linear.app/esp-start-kit)
- **Documentation**: Component-specific docs in `main/components/`
- **ESP-IDF Guide**: [Official ESP-IDF Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/)

---

## 🤝 Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

### Development Guidelines
- Follow ESP-IDF coding standards
- Add appropriate logging
- Update documentation
- Test on hardware when possible

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👥 Development Team

- **Deni** - Main Developer & Architecture
- **IoT Team** - Hardware & Software Design

---

## 📈 Version History

- **Current**: See `version.txt` for latest version
- **Release Branch**: `release-2026-03-05` for mobile features

---

## 🔍 Troubleshooting

### Common Issues
- **WiFi Connection**: Check credentials and network availability
- **Sensor Readings**: Verify pin connections and power supply
- **Display Issues**: Check I2C connections and contrast settings
- **Build Errors**: Ensure ESP-IDF environment is properly configured

### Support
For issues and questions:
- Check component documentation in `main/components/`
- Review ESP-IDF official documentation
- Open an issue on the project repository

---

*Built with ❤️ for the IoT community* 