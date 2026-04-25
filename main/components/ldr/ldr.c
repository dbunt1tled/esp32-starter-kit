//
// Created by admin on 24.04.2026.
//

#include "ldr.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "components/bus/bus.h"

static const char *LDR_TAG = "LDR";

static adc_oneshot_unit_handle_t adc_handle;
static adc_cali_handle_t cali_handle;

static float filtered = 0;
static uint8_t current_contrast = 0;
static uint8_t save_contrast = 0;

static void timer_cb(void *arg) {
    int raw = 0;
    adc_oneshot_read(adc_handle, LDR_PIN, &raw);

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

    ESP_LOGI(LDR_TAG, "raw=%d filtered=%.1f contrast=%d", raw, filtered, current_contrast);
}

static void adc_init(void) {
    const adc_oneshot_unit_init_cfg_t init_cfg = {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_new_unit(&init_cfg, &adc_handle);
    const adc_oneshot_chan_cfg_t cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12
    };
    adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_6, &cfg);
}

static void adc_calibration_init(void) {
    adc_cali_line_fitting_config_t cali_cfg = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    if (adc_cali_create_scheme_line_fitting(&cali_cfg, &cali_handle) != ESP_OK) {
        cali_handle = NULL;
    }
}


void ldr_init(void) {
    adc_init();
    adc_calibration_init();
    const esp_timer_create_args_t timer_args = {
        .callback = &timer_cb,
        .name = "ldr_timer"
    };
    esp_timer_handle_t timer;
    esp_timer_create(&timer_args, &timer);
    esp_timer_start_periodic(timer, 1000 * 1000); // 1 second in microseconds
}
