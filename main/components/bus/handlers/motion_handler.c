//
// Created by admin on 17.04.2026.
//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "handlers.h"
#include <stdio.h>
#include <driver/gpio.h>

#include "components/cfg/configure.h"
#include "esp_log.h"
#include "components/bus/bus.h"
#include "components/http/client/h_client.h"


static const char* MH_TAG = "MH";
static TickType_t last_trigger = 0;
void motion_handler(const bus_msg_t *msg) {
    //char response[512];
    const TickType_t DEBOUNCE_MS = pdMS_TO_TICKS(500);
    const TickType_t now = xTaskGetTickCount();

    if ((now - last_trigger) < DEBOUNCE_MS) {
        return;
    }
    last_trigger = now;
    if (msg->value.val == 1) {
        // http_post_req(
        //     TELEGRAM_URL_SEND_MESSAGE,
        //     "{\"chat_id\": 307851817, \"text\": \"Motion detected!!!\"}",
        //     "application/json",
        //     response,
        //     sizeof(response)
        // );
        // ESP_LOGI(MH_TAG, "Motion response: %d", level);
        ESP_LOGI(MH_TAG, "Motion response: %d", msg->value.val);
    }

}
