//
// Created by admin on 25.04.2026.
//

#ifndef ESP_START_KIT_PB_H
#define ESP_START_KIT_PB_H
#include "driver/gpio.h"

#define PB_PIN GPIO_NUM_18
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_1
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_DUTY 512

void pb_init(void);
void gamma_p(void);
void alert(void);
void bip(void);
void buzzer_rest(const uint32_t duration_ms);
void buzzer_tone(const uint32_t freq_hz, const uint32_t duration_ms);
#endif //ESP_START_KIT_PB_H
