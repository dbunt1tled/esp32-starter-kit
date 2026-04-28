//
// Created by admin on 17.04.2026.
//
#include "handlers.h"
#include "esp_log.h"
#include "components/oled/oled.h"
#include "components/bus/bus.h"

// static const char* RAIN_TAG = "RAIN_H";
void rain_handler(const bus_msg_t *msg) {
    //ESP_LOGI(RAIN_TAG, "RAIN=%d", msg->value.val);
    bus_msg_t m = {
        .action = ACTION_PRINT,
        .reg.oled = {
            .type = OLED_BLOCK_HEADER,
            .icons = {
                .set = OLED_ICON_RAIN,
                .clear = 0,
            }
        }
    };
    if (msg->value.val >=2900) {
        m.value.val = 0;
    }else if (msg->value.val >= 1500 && msg->value.val < 2900) {
        m.value.val = 1;
    }else if (msg->value.val < 1500) {
        m.value.val = 2;
    }
    bus_send(m);
}
