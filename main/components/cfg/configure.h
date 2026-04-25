//
// Created by admin on 22.04.2026.
//

#ifndef ESP_START_KIT_CONFIGURE_H
#define ESP_START_KIT_CONFIGURE_H

#ifdef USE_LOCAL_CONFIG
    #include "configure_loc.h"
#else
    #define WIFI_SSID "ssid"
    #define WIFI_PASSWORD "12345678"
    #define TELEGRAM_URL_SEND_MESSAGE "https://api.telegram.org/bot11111111:token/sendMessage"
    #define TELEGRAM_CHAT_ID "1111111111"
#endif
#endif //ESP_START_KIT_CONFIGURE_H
