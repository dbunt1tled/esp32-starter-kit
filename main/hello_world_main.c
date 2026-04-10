#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include <stdio.h>
#include <inttypes.h>
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "components/button/button.h"
#include "components/button/handlers/handler.h"
#include "components/led/leds.h"


void app_main(void) {
    ESP_LOGI("Main", "Start Program");
    gpio_install_isr_service(0);
    ESP_LOGI("MAIN", "isr_installed");
    led_init(LED_PIN);
    ESP_LOGI("MAIN", "led inited");
    button_init(BUTTON_PIN, led_handler);
    ESP_LOGI("MAIN", "button inited");
}
