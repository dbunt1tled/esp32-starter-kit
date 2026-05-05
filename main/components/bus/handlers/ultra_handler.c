//
// Created by admin on 17.04.2026.
//
#include "freertos/FreeRTOS.h"
#include "handlers.h"
#include <stdio.h>
#include <driver/gpio.h>
#include "esp_log.h"
#include "components/bus/bus.h"
#include "components/pb/pb.h"


// static const char* ULTRAH_TAG = "ULTRA_H";
void ultra_handler(const bus_msg_t *msg) {
    if (msg->value.valf < 10.0f) {
        uint32_t freqs[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5};
        for (int i = 0; i < 4; i++) {
            buzzer_play_tone(freqs[i], EIGHTH);
        }
    }
}
