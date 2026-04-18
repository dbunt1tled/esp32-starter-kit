 //
// Created by admin on 12.04.2026.
//

#ifndef HELLO_WORLD_ESP_OLED_H
#define HELLO_WORLD_ESP_OLED_H

#include "driver/i2c_master.h"
#include "../icons/icons.h"

#define I2C_PORT I2C_NUM_0
#define SDA_PIN 21
#define SCL_PIN 22

#define OLED_ADDR 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define HEADER_H 8
#define TITLE_H 8
#define FOOTER_H 8
#define MAIN_H 16

typedef enum {
    OLED_BLOCK_HEADER,
    OLED_BLOCK_TITLE,
    OLED_BLOCK_MAIN,
    OLED_BLOCK_FOOTER,
} oled_block_t;

typedef enum {
    OLED_ICON_WIFI = 1 << 0,
    OLED_ICON_BLE  = 1 << 1,
    OLED_ICON_BATT = 1 << 2,
} oled_icon_t;

typedef struct {
    oled_block_t type;
    struct {
        uint8_t set;
        uint8_t clear;
    } icons;
} oled_msg_t;

void oled_init(void);
void oled_clear(void);
void test_ol(void);
void oled_flush(void);
void oled_set_icons(const uint8_t icons);
void oled_draw_text(const int x, const  int y, const char *text, const bool on);
void oled_draw_text_big(const int x, const  int y, const char *text, const bool on);
void display_draw_icon(const uint8_t x, const uint8_t y, const icon_t *icon, const bool on);

void oled_set_header(bool wifi, bool ble, bool battery);
void oled_set_text(oled_block_t block, const char *text);
void oled_clear_line(const int y, const int h);
void oled_clear_area(const int x, const int y, const int w, const int h);
void oled_render(void);
#endif //HELLO_WORLD_ESP_OLED_H
