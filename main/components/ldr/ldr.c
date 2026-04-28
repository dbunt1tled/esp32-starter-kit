//
// Created by admin on 24.04.2026.
//

#include "ldr.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "components/bus/bus.h"
#include "services/adc/adc.h"

// static const char *LDR_TAG = "LDR";

static float filtered = 0;
static uint8_t current_contrast = 0;
static uint8_t save_contrast = 0;

static void timer_cb(void *arg) {
    int const raw  = adc_service_read_mv(LDR_PIN);

    const float alpha = 0.2;
    filtered = alpha * raw + (1 - alpha) * filtered;
    const uint8_t target = filtered / 16.0;
    current_contrast += (target - current_contrast) * 0.2;

    if (current_contrast > save_contrast + 10 || current_contrast < save_contrast - 10) {
        const bus_msg_t m = {
            .action = ACTION_LDR,
            .value.val8 = current_contrast,
        };
        bus_send(m);
        save_contrast = current_contrast;
    }

    // ESP_LOGI(LDR_TAG, "raw=%d filtered=%.1f contrast=%d", raw, filtered, current_contrast);
}

void ldr_init(void) {
    adc_service_add_channel(LDR_PIN);
    const esp_timer_create_args_t timer_args = {
        .callback = &timer_cb,
        .name = "ldr_timer"
    };
    esp_timer_handle_t timer;
    esp_timer_create(&timer_args, &timer);
    esp_timer_start_periodic(timer, 1000 * 1000); // 1 second in microseconds
}
