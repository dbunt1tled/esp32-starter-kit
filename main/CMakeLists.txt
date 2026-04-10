idf_component_register(SRCS
        "hello_world_main.c"
        "components/button/button.h"
        "components/button/button.c"
        "components/button/handlers/handler.h"
        "components/button/handlers/led_handler.c"
        "components/led/leds.h"
        "components/led/leds.c"
        INCLUDE_DIRS "."
        REQUIRES
        esp_driver_gpio
        esp_driver_ledc
        esp_timer
        spi_flash
)