//
// Created by admin on 10.04.2026.
//

#include "leds.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "driver/ledc.h"
#include "esp_timer.h"
#include "esp_log.h"

#define MAX_GPIO 40
#define BLINK_PERIOD_MS 400

typedef struct {
    gpio_num_t gpio;
    bool blink;
    bool state;
    int64_t last_toggle;
} led_t;

static led_t *leds[MAX_GPIO];

static TaskHandle_t led_task_handle = NULL;

static void led_task(void *arg)
{
    uint32_t notified;
    while (true) {
        const int64_t now = esp_timer_get_time() / 1000;
        if (xTaskNotifyWait(0, UINT32_MAX, &notified, pdMS_TO_TICKS(200))) {
            for (int gpio = 0; gpio < MAX_GPIO; gpio++) {
                if (!(notified & (1UL << gpio))) {
                    continue;
                }
                led_t *led = leds[gpio];
                if (!led) {
                    continue;
                }
                gpio_set_level(led->gpio, led->state);
            }
        }

        for (int gpio = 0; gpio < MAX_GPIO; gpio++) {
            led_t *led = leds[gpio];
            if (!led) {
                continue;
            }
            if (led->blink) {
                if (now - led->last_toggle > BLINK_PERIOD_MS) {
                    led->state = !led->state;
                    led->last_toggle = now;
                    gpio_set_level(led->gpio, led->state);
                }
            }
        }
    }
}

void led_init(gpio_num_t gpio)
{
    if (gpio >= MAX_GPIO) {
        return;
    }


    led_t *led = malloc(sizeof(led_t));

    led->gpio = gpio;
    led->blink = false;
    led->state = false;
    led->last_toggle = 0;

    leds[gpio] = led;

    const gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << gpio),
    };

    gpio_config(&io_conf);

    if (!led_task_handle)
        xTaskCreate(led_task, "led_task", 2048, NULL, 5, &led_task_handle);
}

void led_set(const gpio_num_t gpio, const led_cmd_t cmd)
{
    led_t *led = leds[gpio];
    if (!led)
        return;
    switch (cmd) {
        case LED_CMD_TOGGLE:
            if (led->blink) {
                led->blink = false;
                led->state = false;
            } else {
                led->state = !led->state;
            }
            break;

        case LED_CMD_ON:
            led->blink = false;
            led->state = true;
            break;

        case LED_CMD_OFF:
            led->blink = false;
            led->state = false;
            break;

        case LED_CMD_BLINK:
            led->blink = true;
            break;
    }

    xTaskNotify(led_task_handle, (1UL << gpio), eSetBits);
}