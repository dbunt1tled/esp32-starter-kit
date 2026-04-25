//
// Created by admin on 10.04.2026.
//

#ifndef ESP_START_KIT_LEDS_H
#define ESP_START_KIT_LEDS_H
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2

typedef enum {
    LED_CMD_ON,
    LED_CMD_OFF,
    LED_CMD_TOGGLE,
    LED_CMD_BLINK,
} led_cmd_t;

void led_init(gpio_num_t gpio);
void led_set(gpio_num_t gpio, led_cmd_t cmd);
#endif //ESP_START_KIT_LEDS_H
