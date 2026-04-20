//
// Created by admin on 12.04.2026.
//

#include "oled.h"
#include "driver/i2c_master.h"
#include "ssd1306.h"
#include "esp_log.h"
#include "../icons/icons.h"

static ssd1306_handle_t disp;

static void i2c_init(void) {
    i2c_master_bus_config_t bus_cfg = {
        .i2c_port = I2C_PORT,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus));

    ssd1306_config_t cfg = {
        .bus = SSD1306_I2C,
        .width = OLED_WIDTH,
        .height = OLED_HEIGHT,
        .iface.i2c = {
            .port = I2C_PORT,
            .addr = OLED_ADDR,
            .rst_gpio = -1
        },
    };

    ESP_ERROR_CHECK(ssd1306_new_i2c(&cfg, &disp));
}

void oled_flush(void) {
    ssd1306_display(disp);
}

void oled_clear(void) {
    ssd1306_clear(disp);

}
void oled_clear_area(const int x, const int y, const int w, const int h) {
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            ssd1306_draw_pixel(disp, i, j, false);
        }
    }
}
void oled_clear_line(const int y, const int h) {
    oled_clear_area(0, y, OLED_WIDTH, h);
}

void oled_draw_text(const int x, const  int y, const char *text, const bool on) {
    ssd1306_draw_text(disp, x, y, text, on);
}
void oled_draw_text_big(const int x, const  int y, const char *text, const bool on) {
    ssd1306_draw_text_scaled(disp, x, y, text, on, 2);
}

void oled_draw_text_centered(const int y, const char *text, const bool big, const bool on) {
    int c = 1;
    if (big) {
        c = 2;
    }
    const int max_char = 20 / c;
    const int char_w = 6 * c;
    const int len = strlen(text);
    int x = 0;
    if (len < max_char) {
        x = ((max_char - len) / 2) * char_w;
    }
    if (big) {
        oled_draw_text_big(x, y, text, on);
    } else {
        oled_draw_text(x, y, text, on);
    }
}

void oled_set_icon(uint8_t *icons, const oled_icon_t icon, const bool on) {
    if (on) {
        *icons |= icon;
    } else {
        *icons &= ~icon;
    }
}
void oled_init(void) {
    i2c_init();
    oled_clear();
    oled_flush();
}

void display_draw_icon(const uint8_t x, const uint8_t y, const icon_t *icon, const bool on) {
    for (uint8_t row = 0; row < icon->height; row++) {
        const uint16_t line = ((uint16_t)icon->data[row * 2 + 1] << 8)
                                 | icon->data[row * 2];
        for (uint8_t col = 0; col < icon->width; col++) {
            if (line & (1 << col)) {
                ssd1306_draw_pixel(disp, x + col, y + row, on);
            }
        }
    }
}