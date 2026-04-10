//
// Created by admin on 10.04.2026.
//

#ifndef HELLO_WORLD_ESP_HANDLER_H
#define HELLO_WORLD_ESP_HANDLER_H
#include "driver/gpio.h"
#include "../button.h"

void led_handler(gpio_num_t gpio, button_event_t event);
#endif //HELLO_WORLD_ESP_HANDLER_H
