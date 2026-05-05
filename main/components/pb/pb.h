//
// Created by admin on 25.04.2026.
//

#ifndef ESP_START_KIT_PB_H
#define ESP_START_KIT_PB_H
#include "driver/gpio.h"

#define NOTE_C4   262
#define NOTE_D4   294
#define NOTE_E4   330
#define NOTE_F4   349
#define NOTE_G4   392
#define NOTE_A4   440
#define NOTE_B4   494

// 5-я октава
#define NOTE_C5   523
#define NOTE_D5   587
#define NOTE_E5   659
#define NOTE_F5   698
#define NOTE_G5   784
#define NOTE_A5   880
#define NOTE_B5   988

// Длительности (мс) для BPM=120
#define BPM         120
#define WHOLE       (60000 / BPM * 4)
#define HALF        (60000 / BPM * 2)
#define QUARTER     (60000 / BPM)
#define EIGHTH      (60000 / BPM / 2)
#define SIXTEENTH   (60000 / BPM / 4)

#define REST        0



#define PB_PIN GPIO_NUM_18
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_1
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_DUTY 512

typedef struct {
    uint32_t freq;
    uint32_t duration;
} Note;

void pb_init(void);
void gamma_p(void);
void alert(void);
void bip(void);
void buzzer_rest(const uint32_t duration_ms);
void buzzer_tone(const uint32_t freq_hz, const uint32_t duration_ms);
void buzzer_play_tone(const uint32_t freq_hz, const uint32_t duration_ms);
void play_melody(const Note *melody, size_t len);
#endif //ESP_START_KIT_PB_H
