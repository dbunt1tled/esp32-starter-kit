//
// Created by admin on 16.04.2026.
//

#ifndef ESP_START_KIT_WIFI_H
#define ESP_START_KIT_WIFI_H

typedef enum {
    WIFI_EVENT_CONNECTED,
    WIFI_EVENT_DISCONNECTED,
    WIFI_EVENT_GOT_IP
} wifi_ev;

void wifi_init(const char *ssid, const char *password);
bool wifi_is_connected(void);
#endif //ESP_START_KIT_WIFI_H
