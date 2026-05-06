//
// Created by admin on 13.04.2026.
//

#ifndef ESP_START_KIT_ICONS_H
#define ESP_START_KIT_ICONS_H
#include <stdint.h>

#define ICON_SIZE_8  8
#define ICON_SIZE_16 16

typedef struct {
    const uint8_t *data;
    uint8_t width;
    uint8_t height;
} icon_t;

extern const icon_t ICON_WIFI;
extern const icon_t ICON_WIFI_OFF;
extern const icon_t ICON_BLUETOOTH;
extern const icon_t ICON_BATTERY_FULL;
extern const icon_t ICON_BATTERY_EMPTY;
extern const icon_t ICON_BATTERY_HALF;
extern const icon_t ICON_BATTERY_LOW;
extern const icon_t ICON_BATTERY_CHARGING ;
extern const icon_t ICON_SIGNAL_FULL;
extern const icon_t ICON_SIGNAL_HALF;
extern const icon_t ICON_SIGNAL_NO;
extern const icon_t ICON_SUN;
extern const icon_t ICON_CLOUD_RAIN;
extern const icon_t ICON_RAIN;
extern const icon_t ICON_FIRE;
extern const icon_t ICON_FIRE_C;

#endif //ESP_START_KIT_ICONS_H
