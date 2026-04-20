#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "components/bus/bus.h"
#include "components/button/button.h"
#include "components/button/handlers/handler.h"
#include "components/dnsm/dnsm.h"
#include "components/led/leds.h"
#include "components/nvs/nvs.h"
#include "components/oled/oled.h"
#include "components/sntp/sntp.h"

static const char* MAIN_TAG = "Main";

void app_main(void) {
    ESP_LOGI(MAIN_TAG, "Start Program");
    ESP_LOGI(MAIN_TAG, "Version: %s\n", PROJECT_VER);

    gpio_install_isr_service(0);
    ESP_LOGI(MAIN_TAG, "isr_installed");
    button_init(BUTTON_PIN, led_handler);
    ESP_LOGI(MAIN_TAG, "button inited");
    oled_init();
    ESP_LOGI(MAIN_TAG, "oled inited");
    bus_cfg_t q_qfg = {
        .count = 10,
        .delay = 100,
    };

    bus_init(&q_qfg);
    ESP_LOGI(MAIN_TAG, "bus inited");
    nvs_init();
    led_init(LED_PIN);
    ESP_LOGI(MAIN_TAG, "led inited");
    wifi_init("sidni", "18111958");
    // if (!wifi_is_connected()) {
    //     ESP_LOGE(MAIN_TAG, "WiFi is not connected");
    //     return;
    // }
    time_sync_init();
    dnsm_init();
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
