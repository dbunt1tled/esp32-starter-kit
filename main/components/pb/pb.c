//
// Created by admin on 25.04.2026.
//

#include "pb.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *PB_TAG = "pb";

void pb_init(void) {
   ledc_timer_config_t timer = {
      .speed_mode = LEDC_MODE,
      .timer_num = LEDC_TIMER,
      .duty_resolution = LEDC_TIMER_10_BIT,
      .freq_hz = 2000,
      .clk_cfg = LEDC_AUTO_CLK,
   };
   ledc_timer_config(&timer);
   ledc_channel_config_t channel = {
      .speed_mode = LEDC_MODE,
      .channel = LEDC_CHANNEL,
      .timer_sel = LEDC_TIMER,
      .gpio_num = PB_PIN,
      .duty = 0,
      .hpoint = 0,
   };
   ledc_channel_config(&channel);
   ESP_LOGI(PB_TAG, "PB inited");
}

void gamma_p(void) {
   for (int i = 0; i < 7; i++) {
      const uint32_t notes[] = {262, 294, 330, 349, 392, 440, 494};
      buzzer_tone(notes[i], 300);
      buzzer_rest(50);
   }
}

void bip(void) {
   buzzer_tone(1000, 100);
   buzzer_rest(100);
}

void alert(void) {
   for (int i = 0; i < 3; i++) {
      buzzer_tone(1000, 100);
      buzzer_rest(100);
   }
}

void buzzer_tone(const uint32_t freq_hz, const uint32_t duration_ms) {
   ledc_set_freq(LEDC_MODE, LEDC_TIMER, freq_hz);
   ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
   ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

   vTaskDelay(pdMS_TO_TICKS(duration_ms));

   ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
   ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void buzzer_rest(const uint32_t duration_ms) {
   vTaskDelay(pdMS_TO_TICKS(duration_ms));
}