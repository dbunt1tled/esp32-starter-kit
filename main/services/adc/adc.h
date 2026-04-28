//
// Created by admin on 28.04.2026.
//

#ifndef ESP_START_KIT_ADC_H
#define ESP_START_KIT_ADC_H
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_oneshot.h"
#include "services/move_avg/move_avg.h"

#define ADC_MAX_CHANNELS 8
#define ADC_CHANNEL_MAX (ADC_CHANNEL_9 + 1)

typedef struct {
    adc_channel_t channel;
    moving_avg_t ma;
} adc_channel_ctx_t;;

void adc_service_init(void);
void adc_service_add_channel(adc_channel_t ch);
int adc_service_read(adc_channel_t ch);
int adc_service_read_avg(adc_channel_t ch);

int adc_service_read_mv(const adc_channel_t ch);
int adc_service_read_avg_mv(const adc_channel_t ch);
#endif //ESP_START_KIT_ADC_H
