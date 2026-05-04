//
// Created by admin on 22.04.2026.
//

#include "motion.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/gpio.h>

#include "configure_loc.h"
#include "esp_log.h"
#include "components/bus/bus.h"
#include "components/http/client/h_client.h"


static void IRAM_ATTR motion_isr_handler(void *arg) {
    const bus_msg_t msg = {
        .action = ACTION_MOTION,
        .value.val = gpio_get_level((gpio_num_t)(uint32_t)arg),
    };
    bus_send_isr(msg);
}
static int prev_level = 0;
static void pir_polling_task(void *arg)
{
    static char response[512];
    int curr_level = 0;

    while (1) {
        curr_level = gpio_get_level(MOTION_PIN);

        if (curr_level != prev_level) {
            if (curr_level == 1) {
                ESP_LOGI("MOTION", "[Polling] Движение обнаружено! %d", curr_level);
                // http_post_req(
                //     TELEGRAM_URL_SEND_MESSAGE,
                //     "{\"chat_id\": 307851817, \"text\": \"Motion detected!!!\"}",
                //     "application/json",
                //     response,
                //     sizeof(response)
//                );
            }
            prev_level = curr_level;
        }
        ESP_LOGI("MOTION", "STATE %d", curr_level);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void motion_init(void) {
    const gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << MOTION_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    };

    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_ERROR_CHECK(gpio_isr_handler_add(MOTION_PIN, motion_isr_handler, (void*) MOTION_PIN));
    //xTaskCreate(pir_polling_task, "pir_polling_task", 8192, NULL, 5, NULL);
}

