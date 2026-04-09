
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include <stdio.h>
#include <inttypes.h>
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/ledc.h"


#define LED_PIN GPIO_NUM_2
#define BUTTON_PIN GPIO_NUM_4

#define LEDC_TIMER LEDC_TIMER_1
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL LEDC_CHANNEL_2
#define LEDC_DUTY_RES LEDC_TIMER_10_BIT  // Set duty resolution to 13 bits
#define LEDC_DUTY (512)      // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY 1000  //(8192000)       // Frequency in Hertz
#define DUTY_100 (0x1 << LEDC_DUTY_RES)

#define LONG_PRESS_MS 1000

void led_init(int const pin) {
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = 1ULL << pin;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);
    gpio_set_level(LED_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
    gpio_set_level(LED_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(1000));
}

void power_init_led_pwm(uint8_t duty) {
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {.speed_mode = LEDC_MODE,
                                      .timer_num = LEDC_TIMER,
                                      .duty_resolution = LEDC_DUTY_RES,
                                      .freq_hz = LEDC_FREQUENCY,
                                      .clk_cfg = LEDC_AUTO_CLK};
    if (ledc_timer_config(&ledc_timer) != ESP_OK) {
        ESP_LOGI("Main", "ledc_timer_config1");
    }

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {.speed_mode = LEDC_MODE,
                                          .channel = LEDC_CHANNEL,
                                          .timer_sel = LEDC_TIMER,
                                          .intr_type = LEDC_INTR_DISABLE,
                                          .gpio_num = LED_PIN,
                                          .duty = ((duty * DUTY_100) / 100),
                                          .hpoint = 0};
    if (ledc_channel_config(&ledc_channel)) {
        ESP_LOGI("Main", "ledc_timer_config2");
    }
}

void power_set_led_pwm(uint8_t duty) {
    if (duty > 100) duty = 100;
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, ((duty * DUTY_100) / 100));
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void led_fade_to(uint8_t target)
{
    static uint8_t current = 0;

    if (target > current) {
        for (int i = current; i <= target; i++) {
            power_set_led_pwm(i);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    } else {
        for (int i = current; i >= target; i--) {
            power_set_led_pwm(i);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }

    current = target;
}

void button_init(const gpio_num_t pin) {
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = 1ULL << pin;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_ANYEDGE;
    gpio_config(&io_conf);
}

typedef enum {
    OFF,
    ON,
    BLINK
} led_state_t;




static led_state_t state = OFF;

static int64_t press_time = 0;

static void IRAM_ATTR button_isr_handler(void* arg) {
    const int level = gpio_get_level(BUTTON_PIN);
    int64_t now = esp_timer_get_time() / 1000;
    if (level == 0) {
        press_time = now;
    } else {
        int duration = now - press_time;
        if (duration > LONG_PRESS_MS) {
            if (state == BLINK) {
                state = OFF;
            } else {
                state = BLINK;
            }
        } else {
            if (state != BLINK) {
                if (state == OFF) {
                    state = ON;
                } else {
                    state = OFF;
                }
            }
        }
    }
}

void blink_task(void* arg) {
    while (1) {
        // ESP_LOGI("Main", "Start Task");
        if (state == BLINK) {
            led_fade_to(100);
            vTaskDelay(pdMS_TO_TICKS(300));

            led_fade_to(0);
            vTaskDelay(pdMS_TO_TICKS(300));
        } else {
            gpio_set_level(LED_PIN, state == ON);
            if (state == ON) {
                power_set_led_pwm(100);
            } else {
                power_set_led_pwm(0);
            }

            vTaskDelay(pdMS_TO_TICKS(20));
        }
    }
}

void app_main(void)
{
    ESP_LOGI("Main", "Start Program");
    // led_init(LED_PIN);
    button_init(BUTTON_PIN);
    power_init_led_pwm(0);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, NULL);

    xTaskCreate(blink_task, "blink_task", 2048, NULL, 10, NULL);
}
