//
// Created by admin on 17.04.2026.
//

#include "handlers.h"
#include "esp_log.h"
#include "components/bus/bus.h"
#include "components/oled/oled.h"

void print_handler(const bus_msg_t *msg) {
    const oled_msg_t oled = msg->reg.oled;
    switch (oled.type) {
        case OLED_BLOCK_HEADER:
            if (OLED_ICON_WIFI & oled.icons.set) {
                display_draw_icon(0,   0, &ICON_WIFI, true);
            }
            if (OLED_ICON_WIFI & oled.icons.clear) {
                display_draw_icon(0,   0, &ICON_WIFI, false);
            }
            if (OLED_ICON_BLE & oled.icons.set) {
                display_draw_icon(20,   0, &ICON_BLUETOOTH, true);
            }
            if (OLED_ICON_BLE & oled.icons.clear) {
                display_draw_icon(20,   0, &ICON_BLUETOOTH, false);
            }
            if (OLED_ICON_BATT & oled.icons.set) {
                oled_clear_area(110, 0, 16, 16);
                switch (msg->value.val) {
                    case 0:
                        display_draw_icon(110,   0, &ICON_BATTERY_EMPTY, true);
                        break;
                    case 1:
                        display_draw_icon(110,   0, &ICON_BATTERY_LOW, true);
                        break;
                    case 2:
                        display_draw_icon(110,   0, &ICON_BATTERY_HALF, true);
                        break;
                    case 3:
                        display_draw_icon(110,   0, &ICON_BATTERY_FULL, true);
                        break;
                    case 4:
                        display_draw_icon(110,   0, &ICON_BATTERY_CHARGING, true);
                        break;
                    default:
                        break;

                }
            }
            if (OLED_ICON_BATT & oled.icons.clear) {
                oled_clear_area(40, 0, 16, 16);
            }
            if (OLED_ICON_RAIN & oled.icons.set) {
                oled_clear_area(40, 0, 16, 16);
                switch (msg->value.val) {
                    case 0:
                        display_draw_icon(40,   0, &ICON_SUN, true);
                        break;
                    case 1:
                        display_draw_icon(40,   0, &ICON_CLOUD_RAIN, true);
                        break;
                    case 2:
                        display_draw_icon(40,   0, &ICON_RAIN, true);
                        break;
                    default:
                        break;
                }
            }
            if (OLED_ICON_RAIN & oled.icons.clear) {
                oled_clear_area(40, 0, 16, 16);
            }

            break;
        case OLED_BLOCK_TITLE:
            oled_clear_line(20, TITLE_H);
            if (msg->param.flag == 1) {
                oled_draw_text_centered(20, msg->value.text, false, true);
            } else {
                oled_draw_text(0, 20, msg->value.text, true);
            }
            break;
        case OLED_BLOCK_MAIN:
            oled_clear_line(36, MAIN_H);
            if (msg->param.flag == 1) {
                oled_draw_text_centered(36, msg->value.text, true, true);
            } else {
                oled_draw_text_big(0, 36, msg->value.text, true);
            }
            break;
        case OLED_BLOCK_FOOTER:
            oled_clear_line(56, FOOTER_H);
            if (msg->param.flag == 1) {
                oled_draw_text_centered(56, msg->value.text, false, true);
            } else {
                oled_draw_text(0, 56, msg->value.text, true);
            }

            break;
    }
    oled_flush();
}
