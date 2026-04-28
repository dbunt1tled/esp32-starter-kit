//
// Created by admin on 27.04.2026.
//

#ifndef ESP_START_KIT_RAIN_H
#define ESP_START_KIT_RAIN_H
#include "driver/gpio.h"

#define RAIN_PIN ADC_CHANNEL_7

void rain_init(void);

#endif //ESP_START_KIT_RAIN_H
