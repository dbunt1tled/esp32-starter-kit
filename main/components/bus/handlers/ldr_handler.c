//
// Created by admin on 17.04.2026.
//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "handlers.h"
#include <stdio.h>
#include <driver/gpio.h>
#include "esp_log.h"
#include "components/bus/bus.h"


// static const char* LDRH_TAG = "LDR_H";
void ldr_handler(const bus_msg_t *msg) {
    set_contrast(msg->value.val8);
    // ESP_LOGI(LDRH_TAG, "contrast=%d", msg->value.val8);
}
