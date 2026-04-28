//
// Created by admin on 28.04.2026.
//

#include "adc.h"
#include <string.h>
#include "esp_log.h"
#include "services/move_avg/move_avg.h"

static const char* ADC_TAG = "ADC";

static adc_cali_handle_t cali_handle;
static adc_oneshot_unit_handle_t adc_handle;

static int ch_index_map[ADC_CHANNEL_MAX];
static adc_channel_ctx_t channels[ADC_MAX_CHANNELS];
static int channel_count = 0;

static adc_channel_ctx_t* get_channel_ctx(const adc_channel_t ch) {
    int const idx = ch_index_map[ch];
    if (idx < 0) {
        return NULL;
    }

    return &channels[idx];
}

void adc_service_init(void) {
    const adc_oneshot_unit_init_cfg_t init_cfg = {
        .unit_id = ADC_UNIT_1
    };
    const esp_err_t err = adc_oneshot_new_unit(&init_cfg, &adc_handle);
    if (err != ESP_OK) {
        ESP_LOGE(ADC_TAG, "ADC init error: %d\n", err);
        return;
    }
    memset(channels, 0, sizeof(channels));

    for (int i = 0; i < ADC_CHANNEL_MAX; i++) {
        ch_index_map[i] = -1;
    }
    const adc_cali_line_fitting_config_t cali_config = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    adc_cali_create_scheme_line_fitting(&cali_config, &cali_handle);
}

void adc_service_add_channel(const adc_channel_t ch) {
    if (channel_count >= ADC_MAX_CHANNELS) {
        ESP_LOGE(ADC_TAG, "ADC: too many channels");
        return;
    }

    const adc_oneshot_chan_cfg_t cfg = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    adc_oneshot_config_channel(adc_handle, ch, &cfg);


    channels[channel_count].channel = ch;
    ch_index_map[ch] = channel_count;
    ma_init(&channels[channel_count].ma);
    channel_count++;
}

int adc_service_read(const adc_channel_t ch) {
    int val = 0;
    const esp_err_t err = adc_oneshot_read(adc_handle, ch, &val);
    if (err != ESP_OK) {
        ESP_LOGE(ADC_TAG, "ADC read error: %d", err);
        return -1;
    }
    return val;
}

int adc_service_read_avg(const adc_channel_t ch) {
    adc_channel_ctx_t* ctx = get_channel_ctx(ch);
    if (ctx == NULL) {
        return -1;
    }
    const int raw = adc_service_read(ch);
    if (raw < 0) {
        return -1;
    }
    return ma_update(&ctx->ma, raw);
}

int adc_service_read_mv(const adc_channel_t ch) {
    const int raw = adc_service_read(ch);
    int mv = 0;
    adc_cali_raw_to_voltage(cali_handle, raw, &mv);
    return mv;
}

int adc_service_read_avg_mv(const adc_channel_t ch) {
    const int raw = adc_service_read_avg(ch);
    int mv = 0;
    adc_cali_raw_to_voltage(cali_handle, raw, &mv);
    return mv;
}
