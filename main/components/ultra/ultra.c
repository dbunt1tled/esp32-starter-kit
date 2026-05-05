//
// Created by admin on 05.05.2026.
//

#include "ultra.h"

#include <esp_timer.h>
#include <rom/ets_sys.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "components/bus/bus.h"


static const char* ULTRA_TAG = "ULTRA";
#define SOUND_SPEED_CM_US  0.0343f   // скорость звука: 343 м/с = 0.0343 см/мкс


static float hcsr04_measure_cm(void) {
    gpio_set_level(ULTRA_TRIG_PIN, 0);
    ets_delay_us(2);
    gpio_set_level(ULTRA_TRIG_PIN, 1);
    ets_delay_us(10);
    gpio_set_level(ULTRA_TRIG_PIN, 0);

    int64_t timeout = esp_timer_get_time() + 25000; // 25ms timeout
    while (gpio_get_level(ULTRA_ECHO_PIN) == 0) {
        if (esp_timer_get_time() > timeout) {
            return -1.0f;
        }
    }

    const int64_t start = esp_timer_get_time();
    timeout = start + 38000; // 38ms timeout for max 4m range
    while (gpio_get_level(ULTRA_ECHO_PIN) == 1) {
        if (esp_timer_get_time() > timeout) {
            return -1.0f;
        }
    }

    const int64_t duration_us = esp_timer_get_time() - start;
    const float distance_cm = (duration_us * SOUND_SPEED_CM_US) / 2.0f;

    return distance_cm;
}

static void ultra_task(void *arg) {
    while (1) {
        const float distance = hcsr04_measure_cm();

        if (distance > 0 && distance < 30) {
            const bus_msg_t msg = {
                .action = ACTION_ULTRA,
                .value = {.valf = distance}
            };
            bus_send(msg);
        }
        if (distance < 0) {
            ESP_LOGW(ULTRA_TAG, "Distance measurement failed");
        } else {
            ESP_LOGI(ULTRA_TAG, "Distance: %.2f cm", distance);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void ultra_init(void) {
    const gpio_config_t trig_cfg = {
        .pin_bit_mask = (1ULL << ULTRA_TRIG_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&trig_cfg);

    const gpio_config_t echo_cfg = {
        .pin_bit_mask = (1ULL << ULTRA_ECHO_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&echo_cfg);
    gpio_set_level(ULTRA_TRIG_PIN, 0);

    ESP_LOGI(ULTRA_TAG, "Ultra init");
    xTaskCreate(ultra_task, "ultrarange", 2048, NULL, 3, NULL);
}
