//
// Created by admin on 24.04.2026.
//

#ifndef ESP_START_KIT_LDR_H
#define ESP_START_KIT_LDR_H
#include "esp_adc/adc_cali.h"
#define LDR_PIN ADC_CHANNEL_6 //GPIO_NUM_34

void ldr_init(void);
#endif //ESP_START_KIT_LDR_H
