idf_component_register(SRCS "hello_world_main.c"
                       INCLUDE_DIRS "."
                       REQUIRES
                        esp_driver_gpio
                        esp_driver_ledc
                        esp_timer
                        spi_flash
)