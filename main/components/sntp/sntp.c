//
// Created by admin on 19.04.2026.
//

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sntp.h"
#include "esp_sntp.h"
#include "esp_log.h"
#include <time.h>
#include "components/bus/bus.h"

#define UPDATE_INTERVAL_MS 100

static void clock_task(void *arg) {
    static char buf[32];
    bus_msg_t m = {
        .action = ACTION_PRINT,
        .param.flag = 1,
        .reg.oled = {
            .type = OLED_BLOCK_MAIN,
        },
    };
    while (true) {
        time_t now = 0;
        struct tm time_info;
        time(&now);
        localtime_r(&now, &time_info);
        strftime(buf, sizeof(buf), "%H:%M:%S", &time_info);
        m.value.text = buf;
        m.param.flag = 1;
        bus_send(m);
    }
}
static void wait_for_time(void) {
    time_t now = 0;
    struct tm time_info = {0};
    while (time_info.tm_year < (2020-1900)) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        time(&now);
        localtime_r(&now, &time_info);
    }
}

void time_sync_init(void) {
    setenv("TZ", "EET-2EEST,M3.5.0/3,M10.5.0/4", 1);
    tzset();

    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_set_sync_interval(3600000);
    esp_sntp_init();

    wait_for_time();
    xTaskCreate(clock_task, "clock", 2048, NULL, 6, NULL);
}