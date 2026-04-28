//
// Created by admin on 17.04.2026.
//

#ifndef ESP_START_KIT_HANDLERS_H
#define ESP_START_KIT_HANDLERS_H
#include "components/bus/bus.h"

void print_handler(const bus_msg_t *msg);
void wifi_handler(const bus_msg_t *msg);
void motion_handler(const bus_msg_t *msg);
void ldr_handler(const bus_msg_t *msg);
void ir_handler(const bus_msg_t *msg);
void rain_handler(const bus_msg_t *msg);
#endif //ESP_START_KIT_HANDLERS_H
