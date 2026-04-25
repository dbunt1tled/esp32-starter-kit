//
// Created by admin on 22.04.2026.
//

#ifndef ESP_START_KIT_H_CLIENT_H
#define ESP_START_KIT_H_CLIENT_H
#include <esp_err.h>

typedef struct {
    char *buffer;
    int max_len;
    int length;
    bool overflow;
} http_response_t;

esp_err_t http_get_req(const char *base_url, const char *query, char *out_buffer, const int out_buffer_size);
esp_err_t http_post_req(const char *url, const char *data, const char *content_type, char *out_buffer,const int out_buffer_size);
#endif //ESP_START_KIT_H_CLIENT_H
