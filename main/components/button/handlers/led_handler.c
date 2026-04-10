//
// Created by admin on 10.04.2026.
//
#include "esp_log.h"
#include "handler.h"
#include "../button.h"
#include "components/led/leds.h"

static const char *LH_TAG = "l_h";

void led_handler(gpio_num_t gpio, button_event_t event)
{
    if (event == BUTTON_EVENT_CLICK) {
        ESP_LOGI(LH_TAG, "Click - %d", gpio);
        led_set(LED_PIN, LED_CMD_TOGGLE);
    }

    if (event == BUTTON_EVENT_LONG_PRESS) {
        ESP_LOGI(LH_TAG, "Long Press - %d", gpio);
        led_set(LED_PIN, LED_CMD_BLINK);
    }

}
