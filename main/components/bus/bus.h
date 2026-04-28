//
// Created by admin on 16.04.2026.
//

#ifndef ESP_START_KIT_BUS_H
#define ESP_START_KIT_BUS_H
#include "components/oled/oled.h"
#include "components/wifi/wifi.h"

typedef enum {
    ACTION_PRINT,
    ACTION_WIFI,
    ACTION_MOTION,
    ACTION_LDR,
    ACTION_IR,
    ACTION_RAIN,
} bus_action_t;

typedef struct {
    int count;
    int delay;
} bus_cfg_t;

typedef struct {
    bus_action_t action;
    union {
        wifi_ev wifi_event;
        oled_msg_t oled;
    } reg;
    union {
        int flag;
    } param;
    union {
        int val;
        char* text;
        uint8_t val8;
    } value;

} bus_msg_t;

typedef void (*bus_handler_t)(const bus_msg_t *msg);

void bus_init(bus_cfg_t *cfg);
void bus_register(bus_action_t action, bus_handler_t handler);
void bus_send(bus_msg_t msg);
void bus_send_isr(bus_msg_t msg);
#endif //ESP_START_KIT_BUS_H
