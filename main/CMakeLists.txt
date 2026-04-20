file(STRINGS ${CMAKE_CURRENT_LIST_DIR}/../version.txt PROJECT_VER LIMIT_COUNT 1)
string(STRIP "${PROJECT_VER}" PROJECT_VER)

idf_component_register(SRCS
        "hello_world_main.c"
        "components/button/button.h"
        "components/button/button.c"
        "components/button/handlers/handler.h"
        "components/button/handlers/led_handler.c"
        "components/led/leds.h"
        "components/led/leds.c"
        "components/oled/oled.h"
        "components/oled/oled.c"
        "components/icons/icons.h"
        "components/icons/icons.c"
        "components/wifi/wifi.h"
        "components/wifi/wifi.c"
        "components/bus/bus.h"
        "components/bus/bus.c"
        "components/bus/handlers/handlers.h"
        "components/bus/handlers/print_handler.c"
        "components/bus/handlers/wifi_handler.c"
        "components/nvs/nvs.h"
        "components/nvs/nvs.c"
        "components/sntp/sntp.h"
        "components/sntp/sntp.c"
        INCLUDE_DIRS "."
        REQUIRES
        esp_driver_gpio
        esp_driver_ledc
        esp_timer
        spi_flash
        esp_lcd
        esp_netif
        esp_event
        esp_wifi
        lwip
        nvs_flash
)
target_compile_definitions(${COMPONENT_LIB} PRIVATE -DPROJECT_VER="${PROJECT_VER}")