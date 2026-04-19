//
// Created by admin on 16.04.2026.
//

#include "wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "lwip/ip_addr.h"
#include <string.h>
#include "esp_log.h"

#include "components/bus/bus.h"

static void wifi_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    }

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED) {
        const bus_msg_t msg = {
            .action = ACTION_WIFI,
            .reg.wifi_event = WIFI_EVENT_CONNECTED,
        };
        bus_send(msg);
    }

    if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        const ip_event_got_ip_t *ip = (ip_event_got_ip_t *) event_data;
        char ip_str[16];  // max "255.255.255.255"
        snprintf(ip_str, sizeof(ip_str), IPSTR, IP2STR(&ip->ip_info.ip));
        const bus_msg_t msg = {
            .action = ACTION_WIFI,
            .reg.wifi_event = WIFI_EVENT_GOT_IP,
            .value.text = ip_str,
        };
        bus_send(msg);
    }

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        const bus_msg_t msg = {
            .action = ACTION_WIFI,
            .reg.wifi_event = WIFI_EVENT_DISCONNECTED,
        };
        bus_send(msg);
    }
}

void wifi_init(const char *ssid, const char *password) {
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);

    wifi_config_t wifi_config = {};
    strncpy((char *) wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid));
    strncpy((char *) wifi_config.sta.password, password, sizeof(wifi_config.sta.password));
    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();
}