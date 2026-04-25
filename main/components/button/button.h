//
// Created by admin on 10.04.2026.
//

#ifndef ESP_START_KIT_BUTTON_H
#define ESP_START_KIT_BUTTON_H
#include "driver/gpio.h"

#define BUTTON_PIN GPIO_NUM_4

typedef enum {
    BUTTON_EVENT_CLICK,
    BUTTON_EVENT_LONG_PRESS,
    BUTTON_EVENT_RELEASE,
    BUTTON_EVENT_DOUBLE_CLICK
} button_event_t;

typedef void (*button_callback_t)(gpio_num_t gpio, button_event_t event);

typedef struct {
    gpio_num_t gpio;
    button_callback_t cb;
    int last_state;
    int64_t press_time;
    int64_t last_event_time;
    int64_t last_click_time;
    bool waiting_double;
} button_t;

void button_init(const gpio_num_t gpio, const button_callback_t cb);


#endif //ESP_START_KIT_BUTTON_H
