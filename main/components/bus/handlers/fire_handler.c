//
// Created by admin on 17.04.2026.
//
#include "handlers.h"
#include "esp_log.h"
#include "components/oled/oled.h"
#include "components/bus/bus.h"

static const char* FIREH_TAG = "FIRE_H";

void fire_handler(const bus_msg_t *msg) {
    bus_msg_t m = {
        .action = ACTION_PRINT,
        .reg.oled = {
            .type = OLED_BLOCK_HEADER,
            .icons = {
                .set = OLED_ICON_FIRE,
                .clear = 0,
            }
        }
    };
    if (msg->value.val < 500) {
        m.value.val = 0;
    }else if (msg->value.val <= 2600) {
        m.value.val = 1;
    }else if (msg->value.val > 2600) {
        m.reg.oled.icons.set = 0;
        m.reg.oled.icons.clear = OLED_ICON_FIRE;
    }
    bus_send(m);
    ESP_LOGI(FIREH_TAG, "Fire: %d", msg->value.val);
}
