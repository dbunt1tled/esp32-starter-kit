//
// Created by admin on 27.04.2026.
//

#include "rain.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "components/bus/bus.h"
#include "services/adc/adc.h"

static const char *RAIN_TAG = "RAIN";

static void rain_task(void *arg) {
    while (true) {
        const int rain_mv = adc_service_read_mv(RAIN_PIN);

        const bus_msg_t msg = {
            .action = ACTION_RAIN,
            .value = {.val = rain_mv}
        };
        // ESP_LOGI("RAIN","raw=%d filtered=%d\n", rain, rain_mv);
        bus_send(msg);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void rain_init(void) {
    adc_service_add_channel(RAIN_PIN);
    xTaskCreate(rain_task, "rain_task", configMINIMAL_STACK_SIZE * 2, NULL, 5, NULL);
    ESP_LOGI(RAIN_TAG, "Rain inited");
}