//
// Created by admin on 17.04.2026.
//
#include "freertos/FreeRTOS.h"
#include "handlers.h"
#include <stdio.h>
#include <driver/gpio.h>
#include "esp_log.h"
#include "components/bus/bus.h"
#include "components/pb/pb.h"


static const char* IRH_TAG = "IR_H";
void ir_handler(const bus_msg_t *msg) {
    if (msg->value.val) {
        bip();
    }
    ESP_LOGI(IRH_TAG, "IR=%d", msg->value.val);
}
