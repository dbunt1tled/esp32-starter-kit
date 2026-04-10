//
// Created by admin on 10.04.2026.
//

#ifndef HELLO_WORLD_ESP_BUTTON_H
#define HELLO_WORLD_ESP_BUTTON_H
#include "driver/gpio.h"

#define BUTTON_PIN GPIO_NUM_4

typedef enum {
    BUTTON_EVENT_CLICK,
    BUTTON_EVENT_LONG_PRESS,
    BUTTON_EVENT_HOLD,
    BUTTON_EVENT_RELEASE
} button_event_t;

typedef void (*button_callback_t)(gpio_num_t gpio, button_event_t event);

typedef struct {
    gpio_num_t gpio;
    button_callback_t cb;

    int last_state;
    int64_t press_time;
    int64_t last_event_time;
} button_t;

void button_init(const gpio_num_t gpio, const button_callback_t cb);;


#endif //HELLO_WORLD_ESP_BUTTON_H
