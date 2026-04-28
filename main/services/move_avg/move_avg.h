//
// Created by admin on 27.04.2026.
//

#ifndef ESP_START_KIT_MOVE_AVG_H
#define ESP_START_KIT_MOVE_AVG_H
#define MA_SIZE 10

typedef struct {
    int buffer[MA_SIZE];
    int index;
    int count;
    int sum;
} moving_avg_t;

void ma_init(moving_avg_t *ma);
int ma_update(moving_avg_t *ma, const int new_val);
#endif //ESP_START_KIT_MOVE_AVG_H
