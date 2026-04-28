//
// Created by admin on 16.04.2026.
//

#include "bus.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "portmacro.h"
#include "handlers/handlers.h"

#define MAX_HANDLERS 16

static const char *BUS_TAG = "bus";
static QueueHandle_t bus;
static bus_handler_t handlers[MAX_HANDLERS];
static TaskHandle_t bus_task;

static void bus_consumer(void *arg) {
    const bus_cfg_t *cfg = (bus_cfg_t *)arg;
    bus_msg_t msg;
    while (true) {
        if (xQueueReceive(bus, &msg, portMAX_DELAY) == pdTRUE) {
            if (const bus_handler_t handler = handlers[msg.action]) {
                handler(&msg);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(cfg->delay));
    }
}

static void bus_monitor(void *arg) {
    const bus_cfg_t *cfg = (bus_cfg_t *)arg;
    while (true) {
        UBaseType_t const count = uxQueueMessagesWaiting(bus);
        UBaseType_t const stack = uxTaskGetStackHighWaterMark(bus_task);
        if (count > cfg->count) {
            ESP_LOGW(BUS_TAG, "Queue OVERFLOW count: %d, Stack: %d", count, stack);
        }
        if (stack < 100) {
            ESP_LOGW(BUS_TAG, "Queue task stack low: %d bytes", stack);
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}


void bus_init(bus_cfg_t *cfg) {
    bus = xQueueCreate(cfg->count, sizeof(bus_msg_t));
    if (bus == NULL) {
        ESP_LOGE(BUS_TAG, "Failed to create queue");
        return;
    }
    bus_register(ACTION_PRINT, print_handler);
    bus_register(ACTION_WIFI, wifi_handler);
    bus_register(ACTION_MOTION, motion_handler);
    bus_register(ACTION_LDR, ldr_handler);
    bus_register(ACTION_IR, ir_handler);
    bus_register(ACTION_RAIN, rain_handler);
    xTaskCreate(
        bus_consumer,
        "bus_task",
        6144,
        cfg,
        7,
        &bus_task
    );
    xTaskCreate(
        bus_monitor,
        "bus_monitor",
        1024,
        cfg,
        3,
        NULL
    );
    ESP_LOGI(BUS_TAG, "Queue created");
}

void bus_register(bus_action_t action, bus_handler_t handler) {
    if (action < MAX_HANDLERS) {
        handlers[action] = handler;
    }
}

void bus_send(const bus_msg_t msg) {
    const BaseType_t ok = xQueueSend(bus, &msg, portMAX_DELAY);
    if (ok != pdTRUE) {
        ESP_LOGE(BUS_TAG, "Queue Full or Error");
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
}

void bus_send_isr(const bus_msg_t msg) {
    BaseType_t higher_priority_task_woken = pdFALSE;

    xQueueSendFromISR(bus, &msg, &higher_priority_task_woken);
    portYIELD_FROM_ISR(higher_priority_task_woken);
    if (higher_priority_task_woken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}
