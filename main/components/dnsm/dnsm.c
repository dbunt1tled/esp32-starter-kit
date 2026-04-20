//
// Created by admin on 20.04.2026.
//

#include "dnsm.h"

#include <esp_err.h>
#include <esp_log.h>

#include "mdns.h"

static const char *DNS_TAG = "DNS";

void dnsm_init(void) {
    esp_err_t err = mdns_init();
    if (err != ESP_OK) {
        ESP_LOGE(DNS_TAG, "MDNS init falied: %d", err);
        return;
    }
    ESP_ERROR_CHECK(mdns_hostname_set("s-dev")); //ping s-dev.local
    ESP_ERROR_CHECK(mdns_instance_name_set("BreadBoard ESP32"));
}

void dnsm_stop(void) {
    mdns_free();
}
