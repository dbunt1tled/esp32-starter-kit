//
// Created by admin on 17.04.2026.
//

#include "handlers.h"
#include <stdio.h>
#include "esp_log.h"
#include "components/bus/bus.h"
#include "components/oled/oled.h"

static const char* WH_TAG = "WH";

void wifi_handler(const bus_msg_t *msg) {
    switch (msg->reg.wifi_event) {
        case WIFI_EVENT_CONNECTED:
            const bus_msg_t m = {
                .action = ACTION_PRINT,
                .reg.oled = {
                    .type = OLED_BLOCK_HEADER,
                    .icons = {
                        .set = OLED_ICON_WIFI,
                        .clear = 0,
                    }
                }
            };
            bus_send(m);
            break;
        case WIFI_EVENT_DISCONNECTED:
            const bus_msg_t m1 = {
                .action = ACTION_PRINT,
                .reg.oled = {
                    .type = OLED_BLOCK_HEADER,
                    .icons = {
                        .set = 0,
                        .clear = OLED_ICON_WIFI,
                    }
                }
            };
            bus_send(m1);
            break;
        case WIFI_EVENT_GOT_IP:
            static char buffer[32];
            snprintf(buffer, sizeof(buffer),"IP: %s", msg->value.text);
            const bus_msg_t m2 = {
                 .action = ACTION_PRINT,
                 .reg.oled = {
                     .type = OLED_BLOCK_TITLE,
                 },
                .param.flag = 0,
                 .value.text = buffer,
             };
             bus_send(m2);
             break;
        default:
            break;
    }
}
