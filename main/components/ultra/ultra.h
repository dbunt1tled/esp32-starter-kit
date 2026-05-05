//
// Created by admin on 05.05.2026.
//

#ifndef ESP_START_KIT_ULTRA_H
#define ESP_START_KIT_ULTRA_H
#include "driver/gpio.h"
#define ULTRA_TRIG_PIN GPIO_NUM_12
#define ULTRA_ECHO_PIN GPIO_NUM_13
void ultra_init(void);
#endif //ESP_START_KIT_ULTRA_H
