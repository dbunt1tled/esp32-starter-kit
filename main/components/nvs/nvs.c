//
// Created by admin on 19.04.2026.
//

#include "nvs.h"
#include "nvs_flash.h"
#include "esp_err.h"

void nvs_init(void) {
    const esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }
}