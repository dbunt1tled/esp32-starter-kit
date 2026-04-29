//
// Created by admin on 25.04.2026.
//

#include "ir.h"

#include <esp_timer.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "components/bus/bus.h"

// static const char* IR_TAG = "IR";

// static void IRAM_ATTR ir_isr_handler(void *arg) {
//
//     static int state = 0;
//     static int64_t last_time = 0;
//     const int level = gpio_get_level(IR_PIN);
//     if (state == level) {
//         const int64_t now = esp_timer_get_time();
//         if ((now - last_time) < 20000) {
//             return;
//         }
//         last_time = now;
//     }
//
//     state = level;
//     const bus_msg_t msg = {
//         .action = ACTION_IR,
//         .value = {.val = level}
//     };
//     bus_send_isr(msg);
//
// }
static void ir_task(void *arg)
{
    static int prev_level = -1;
    while (true) {
        const int level = gpio_get_level(IR_PIN);
        // ESP_LOGI(IR_TAG, "IR level: %d", level);
        if (level != prev_level) {
            prev_level = level;
            const bus_msg_t msg = {
                .action = ACTION_IR,
                .value = {.val = level}
            };
            bus_send(msg);
        }
        vTaskDelay(pdMS_TO_TICKS(25));
    }
}



void ir_init(void) {
    const gpio_config_t cfg = {
        .pin_bit_mask = (1ULL << IR_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE,
    };

    gpio_config(&cfg);
    // gpio_isr_handler_add(IR_PIN, ir_isr_handler, NULL);
    xTaskCreate(ir_task, "ir_task", 2048, NULL, 5, NULL);
}
