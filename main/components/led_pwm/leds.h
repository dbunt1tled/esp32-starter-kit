//
// Created by admin on 10.04.2026.
//

#ifndef HELLO_WORLD_ESP_LEDS_H
#define HELLO_WORLD_ESP_LEDS_H
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2

typedef enum {
    LED_CMD_ON,
    LED_CMD_OFF,
    LED_CMD_TOGGLE,
    LED_CMD_BLINK,
    LED_CMD_FADE
} led_cmd_t;

void led_init(gpio_num_t gpio);
void led_set(gpio_num_t gpio, led_cmd_t cmd);
#endif //HELLO_WORLD_ESP_LEDS_H
