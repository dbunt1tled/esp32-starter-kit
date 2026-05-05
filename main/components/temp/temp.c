//
// Created by admin on 21.04.2026.
//

#include "temp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "dht.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "components/bus/bus.h"

static void temp_task(void *arg) {
    int16_t temperature = 0;
    int16_t humidity = 0;
    static char buf[32];
    bus_msg_t m = {
        .action = ACTION_PRINT,
        .reg.oled = {
            .type = OLED_BLOCK_FOOTER,
        },
       .param.flag = 0,
    };

    while (true) {
        if (dht_read_data(DHT_TYPE_AM2301, TEMP_PIN, &humidity, &temperature) == ESP_OK) {
            snprintf(buf, sizeof(buf),"T:%dC H:%d%%", temperature / 10,humidity / 10);
            m.value.text = buf;
        } else {
            m.value.text = "Temperature Err";
        }
        bus_send(m);
        vTaskDelay(pdMS_TO_TICKS(25000));
    }
}

void temp_init(void) {
    xTaskCreate(temp_task, "temperature", 2048, NULL, 3, NULL);
}
