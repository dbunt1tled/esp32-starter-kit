//
// Created by admin on 05.05.2026.
//

#include "fire.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "components/bus/bus.h"
#include "services/adc/adc.h"

static const char *FIRE_TAG = "FIRE";

static void fire_task(void *arg) {
    static int prev_fire_mv = 0;
    while (true) {
        const int fire_mv = adc_service_read_mv(FIRE_PIN);
        // ESP_LOGI(FIRE_TAG, "Fire: %d mV", fire_mv);
        if (fire_mv > 3000 && prev_fire_mv > 3000) {
           prev_fire_mv = fire_mv;
            vTaskDelay(pdMS_TO_TICKS(3000));
           continue;
        }
        const bus_msg_t msg = {
            .action = ACTION_FIRE,
            .value = {.val = fire_mv}
        };
        bus_send(msg);
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

void fire_init(void) {
    // DIGITAL OUTPUT
    // const gpio_config_t cfg = {
    //     .pin_bit_mask = (1ULL << FIRE_PIN),
    //     .mode = GPIO_MODE_INPUT,
    //     .pull_up_en = GPIO_PULLUP_ENABLE,
    //     .pull_down_en = GPIO_PULLDOWN_DISABLE,
    //     .intr_type = GPIO_INTR_DISABLE,
    // };
    //
    // gpio_config(&cfg);

    adc_service_add_channel(FIRE_PIN);
    xTaskCreate(fire_task, "fire_task", configMINIMAL_STACK_SIZE * 2, NULL, 5, NULL);
    ESP_LOGI(FIRE_TAG, "Fire inited");
}

