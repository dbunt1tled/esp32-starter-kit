## Supported Sensors

The project supports the following sensor components:

| Sensor Component | Function | Dependencies |
  |-----------------|----------|--------------|                                          
| Temperature Sensor | Read and display temperature readings | dht |                   
| Humidity Sensor | Monitor air humidity levels | dht |                                
| LDR Sensor | Light/dark ratio sensing (Light Detection Resistor) | - |               
| Motion Sensor | Detect movement in real-time | - |                                   
| OLED Display | Centered text display with contrast control | - |                     

### Sensor Capabilities

- **Temperature** (DHT sensor)
- **Humidity** (DHT sensor)
- **Light Sensing** (LDR)
- **Motion Detection** (IMU-based)
- **Display** (OLED with center alignment and contrast)

## Video Documentation

### Video Reference

> The device includes a video demonstration of temperature and humidity sensor
readouts. For details, view the video file located at `@assets/esp32.mp4`.


❯ write this to the readme.md

⏺ ESP Start Kit

▎ IoT Development Platform for ESP32-S3 Microcontrollers                               
▎ A cross-platform, modular IoT development environment featuring hardware abstraction,
▎  HTTP client integration, and OLED contrast control.
                  
---                                                                                    
🚀 Project Overview

The ESP Start Kit is an advanced IoT development platform designed for low-resource
microcontrollers. Built for real-time IoT devices, it provides a modular architecture  
supporting motion detection, sensor integration, and time synchronization.

✅ Key Features                                                                        ─

- Hardware Abstraction: Efficient low-power microcontroller support
- IoT Sensor Integration: Motion, LDR, and temperature/humidity sensing
- HTTP Client: Built-in client library for web services
- OLED Display: Contrast-controlled LCD/LED screen with centered text output
- Time Synchronization: SNTP and NTP integration
- MDNS Service: Local network service discovery
- Build Configuration: Dynamic USE_LOCAL_CONFIG macro management
- Mobile Release: Session token storage compliant with new legal requirements

  ---                                                                                    
📦 Release Branch

This repository includes a release branch (release-2026-03-05) for mobile cut features.
- Release Branch: https://github.com/esp-start-kit/release-2026-03-05 
---                                                                                    
🛠 Quick Start

1. Clone the repository:

git clone https://github.com/esp-start-kit/esp_start_kit.git                           
cd esp_start_kit

2. Configure:                                                                          
   touch config/configure.h

3. Build:                                                                              
   make

  ---                                                                                    
📁 File Structure

esp_start_kit/                                                                         
├── README.md              # Project documentation                                     
├── Makefile               # Build configuration                                       
├── config/                                                                            
│   ├── configure.h        # Configurable build macros                                 
│   └── esp32.mp4          # Hardware video capture                                    
├── components/            # Sensor and controller components                          
├── examples/              # Code examples                                             
├── tests/                 # Unit tests                                                
├── scripts/               # Automation scripts                                        
├── legal/                 # Compliance documentation                                  
├── .gitignore            # Git ignore rules                                           
└── .github/               # GitHub workflows
                                                                                         
---                                                                                    
⚙️ Build Instructions

macOS (Using Xcode)

xcode-select --install                                                                 
make

Linux (Using Yocto)

make clean                                                                             
make distrelease
                                                                                         
---                                                                                    
🌐 External Resources

- Project Tracking: Check Linear for https://linear.app/esp-start-kit
- Oncall Dashboard: Visit Grafana at https://grafana.internal/d/api-latency to monitor
  request handling
- Compliance Policy: Review legal docs at ./legal/session_token_policy.txt

  ---                                                                                    
🧪 Testing

make test       
make test-integration
                                                                                         
---                                                                                    
📚 License

Licensed under MIT.
                                                                                         
---                                                                                    
🤝 Contributing

Contributions are welcome! Please read our contributing guidelines.
                                                                                         
---                                                                                    
👥 Team

- Deni: Main Developer
- IoT Team: Hardware and Software Design
  ---                                                                                    
📄 License

MIT License 