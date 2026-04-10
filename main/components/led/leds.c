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

#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_RES LEDC_TIMER_10_BIT
#define LEDC_FREQ 1000

#define LED_STEP 2
#define BLINK_PERIOD_MS 400

#define DUTY_MAX ((1 << LEDC_RES) - 1)

typedef struct {
    gpio_num_t gpio;
    ledc_channel_t channel;

    bool blink;
    bool state;

    uint8_t brightness;
    uint8_t target;

    int64_t last_toggle;
} led_t;

static const char *LED_TAG = "led";
static led_t *leds[MAX_GPIO];

static int channel_index = 0;
static TaskHandle_t led_task_handle = NULL;

static void pwm_apply(led_t *led)
{
    uint32_t duty = (led->brightness * DUTY_MAX) / 100;

    ledc_set_duty(LEDC_MODE, led->channel, duty);
    ledc_update_duty(LEDC_MODE, led->channel);
}

static void led_task(void *arg)
{
    uint32_t notified;

    while (1) {

        xTaskNotifyWait(0, UINT32_MAX, &notified, pdMS_TO_TICKS(20));

        int64_t now = esp_timer_get_time() / 1000;

        for (int gpio = 0; gpio < MAX_GPIO; gpio++) {

            led_t *led = leds[gpio];
            if (!led)
                continue;

            // fade
            if (led->brightness != led->target) {

                if (led->brightness < led->target)
                    led->brightness += LED_STEP;
                else
                    led->brightness -= LED_STEP;

                pwm_apply(led);
            }

            // blink
            if (led->blink) {

                if (now - led->last_toggle > BLINK_PERIOD_MS) {

                    led->state = !led->state;
                    led->target = led->state ? 100 : 0;

                    led->last_toggle = now;
                }
            }
        }
    }
}

void led_init(gpio_num_t gpio)
{
    if (gpio >= MAX_GPIO)
        return;

    led_t *led = malloc(sizeof(led_t));

    led->gpio = gpio;
    led->channel = channel_index++;

    led->blink = false;
    led->state = false;

    led->brightness = 0;
    led->target = 0;

    led->last_toggle = 0;

    leds[gpio] = led;
    ESP_LOGI(LED_TAG, "registred led - %d", gpio);

    ledc_timer_config_t timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_RES,
        .freq_hz = LEDC_FREQ,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_timer_config(&timer);

    ledc_channel_config_t ch = {
        .gpio_num = gpio,
        .speed_mode = LEDC_MODE,
        .channel = led->channel,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0
    };

    ledc_channel_config(&ch);

    if (!led_task_handle)
        xTaskCreate(led_task, "led_task", 2048, NULL, 10, &led_task_handle);
}

void led_set(const gpio_num_t gpio, const led_cmd_t cmd)
{
    ESP_LOGI(LED_TAG, "CMD - %d, led - %d", cmd, gpio);
    led_t *led = leds[gpio];
    if (!led)
        return;
    switch (cmd) {
        case LED_CMD_TOGGLE:
            if (led->blink) {
                led->blink = false;
                led->state = false;
                led->target = 0;
            } else {
                led->target = led->state ? 0 : 100;
                led->state = !led->state;
            }
            break;

        case LED_CMD_ON:
            led->blink = false;
            led->state = true;
            led->target = 100;
            break;

        case LED_CMD_OFF:
            led->blink = false;
            led->state = false;
            led->target = 0;
            break;

        case LED_CMD_BLINK:
            led->blink = true;
            break;

        case LED_CMD_FADE:
            led->blink = false;
            led->target = led->state ? 0 : 100;
            led->state = !led->state;
            break;
    }

    xTaskNotify(led_task_handle, (1UL << gpio), eSetBits);
}