#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "components/bus/bus.h"
#include "components/button/button.h"
#include "components/button/handlers/handler.h"
#include "components/dnsm/dnsm.h"
#include "components/led/leds.h"
#include "components/motion/motion.h"
#include "components/nvs/nvs.h"
#include "components/oled/oled.h"
#include "components/sntp/sntp.h"
#include "components/temp/temp.h"
#include "components/cfg/configure.h"
#include "components/ldr/ldr.h"
#include "components/ir/ir.h"
#include "components/pb/pb.h"
#include "components/rain/rain.h"
#include "services/adc/adc.h"

static const char *MAIN_TAG = "Main";

void app_main(void) {
    ESP_LOGI(MAIN_TAG, "Start Program");
    ESP_LOGI(MAIN_TAG, "Version: %s\n", PROJECT_VER);

    gpio_install_isr_service(0);
    ESP_LOGI(MAIN_TAG, "isr_installed");
    button_init(BUTTON_PIN, led_handler);
    oled_init();
    bus_cfg_t q_qfg = {
        .count = 10,
        .delay = 50,
    };
    bus_init(&q_qfg);

    nvs_init();
    led_init(LED_PIN);
    wifi_init(WIFI_SSID, WIFI_PASSWORD);
    time_sync_init();
    // dnsm_init();
    temp_init();
    // ESP_LOGI(MAIN_TAG, "WARM PIR... waiting 60 sec");
    // vTaskDelay(pdMS_TO_TICKS(60000));
    motion_init();
    pb_init();
    ir_init();
    adc_service_init();
    ldr_init();
    rain_init();


    gamma_p();
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
