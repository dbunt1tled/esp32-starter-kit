//
// Created by admin on 27.04.2026.
//
#include <string.h>
#include "move_avg.h"

void ma_init(moving_avg_t *ma) {
    ma->index = 0;
    ma->count = 0;
    ma->sum = 0;
    memset(ma->buffer, 0, MA_SIZE);
}

int ma_update(moving_avg_t *ma, const int new_val) {
    ma->sum -= ma->buffer[ma->index];

    ma->buffer[ma->index] = new_val;
    ma->sum += new_val;

    ma->index = (ma->index + 1) % MA_SIZE;

    if (ma->count < MA_SIZE) {
        ma->count++;
    }

    return ma->sum / ma->count;
}