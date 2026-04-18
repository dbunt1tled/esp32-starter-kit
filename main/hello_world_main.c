#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "components/bus/bus.h"
#include "components/button/button.h"
#include "components/button/handlers/handler.h"
#include "components/led/leds.h"
#include "components/oled/oled.h"

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
    led_init(LED_PIN);
    ESP_LOGI(MAIN_TAG, "led inited");

    bus_cfg_t q_qfg = {};
    q_qfg.count = 10;
    q_qfg.delay = 1000;

    bus_init(&q_qfg);
    ESP_LOGI(MAIN_TAG, "bus inited");

    bus_msg_t msg = {
        .action = ACTION_PRINT,
        .reg.oled = {
            .type = OLED_BLOCK_HEADER,
            .icons = {
                .set = OLED_ICON_WIFI | OLED_ICON_BLE,
                .clear = 0,
            }
        }
    };
    bus_send(msg);
    ESP_LOGI(MAIN_TAG, "send msg 1");

    bus_msg_t msg1 = {
        .action = ACTION_PRINT,
        .reg.oled = {
            .type = OLED_BLOCK_HEADER,
            .icons = {
                .set = 0,
                .clear = OLED_ICON_WIFI,
            }
        }
    };
    bus_send(msg1);

    bus_msg_t msg3 = {
        .action = ACTION_PRINT,
        .reg.oled = {
            .type = OLED_BLOCK_TITLE,
        },
        .value.text = "Temperature: 21.5C",
    };
    bus_send(msg3);

    msg3.value.text = "Boroda";
    bus_send(msg3);

    msg3.reg.oled.type=OLED_BLOCK_FOOTER;
    msg3.value.text = "Holoda";
    bus_send(msg3);

    msg3.value.text = "1111Holoda11111111111";
    bus_send(msg3);

    msg3.reg.oled.type=OLED_BLOCK_MAIN;
    msg3.value.text = "127.0.0.1";
    bus_send(msg3);

    msg3.value.text = "aa127.0.0.1aa";
    bus_send(msg3);

}
