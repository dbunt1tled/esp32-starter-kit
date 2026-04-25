//
// Created by admin on 10.04.2026.
//

#ifndef ESP_START_KIT_HANDLER_H
#define ESP_START_KIT_HANDLER_H
#include "driver/gpio.h"
#include "../button.h"

void led_handler(gpio_num_t gpio, button_event_t event);
#endif //ESP_START_KIT_HANDLER_H
