//
// Created by admin on 10.04.2026.
//

#include "button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "esp_timer.h"

#define MAX_GPIO 40
#define DEBOUNCE_MS 40
#define LONG_PRESS_MS 800
#define DOUBLE_CLICK_MS 400

static button_t *buttons[MAX_GPIO];

static TaskHandle_t button_task_handle = NULL;

static void IRAM_ATTR gpio_isr_handler(void *arg) {
    const uint32_t gpio_num = (uint32_t) arg;
    BaseType_t hp_task_woken = pdFALSE;

    xTaskNotifyFromISR(button_task_handle, (1UL << gpio_num), eSetBits, &hp_task_woken);
    if (hp_task_woken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}

static void button_task(void *arg) {
    uint32_t notified;
    while (1) {
        xTaskNotifyWait(0, UINT32_MAX, &notified, pdMS_TO_TICKS(50));
        const int64_t now = esp_timer_get_time() / 1000;
        for (int gpio = 0; gpio < MAX_GPIO; gpio++) {
            button_t *btn = buttons[gpio];
            if (!btn) {
                continue;
            }
            // check timeout single click
            if (btn->waiting_double && now - btn->last_click_time > DOUBLE_CLICK_MS) {
                btn->waiting_double = false;
                btn->cb(btn->gpio, BUTTON_EVENT_CLICK);
            }
            if (!(notified & (1UL << gpio))) {
                continue;
            }
            if (now - btn->last_event_time < DEBOUNCE_MS) {
                continue;
            }
            btn->last_event_time = now;
            const int level = gpio_get_level(btn->gpio);
            if (level == 0) {
                btn->press_time = now;
            } else {
                const int duration = now - btn->press_time;
                if (duration < LONG_PRESS_MS) {
                    if (btn->waiting_double &&
                        now - btn->last_click_time < DOUBLE_CLICK_MS) {
                        btn->waiting_double = false;
                        btn->cb(btn->gpio, BUTTON_EVENT_DOUBLE_CLICK);
                    } else {
                        btn->waiting_double = true;
                        btn->last_click_time = now;
                    }
                } else {
                    btn->cb(btn->gpio, BUTTON_EVENT_LONG_PRESS);
                }
                btn->cb(btn->gpio, BUTTON_EVENT_RELEASE);
            }
        }
    }
}

void button_init(const gpio_num_t gpio, const button_callback_t cb) {
    button_t *btn = malloc(sizeof(button_t));

    btn->gpio = gpio;
    btn->cb = cb;
    btn->press_time = 0;
    btn->last_event_time = 0;
    buttons[gpio] = btn;

    const gpio_config_t io = {
        .pin_bit_mask = (1ULL << gpio),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_ANYEDGE
    };
    gpio_config(&io);

    if (!button_task_handle) {
        xTaskCreate(button_task, "button_task", 2048, NULL, 10, &button_task_handle);
    }
    gpio_isr_handler_add(gpio, gpio_isr_handler, (void *) gpio);
}
