//
// Created by admin on 22.04.2026.
//

#include "h_client.h"

#include <esp_http_client.h>
#include "esp_log.h"
#include "esp_crt_bundle.h"

static const char *HC_TAG = "http_client";

static esp_err_t http_response_handler(esp_http_client_event_t *evt) {
    http_response_t * resp = (http_response_t *)evt->user_data;

    switch (evt->event_id) {
        case HTTP_EVENT_ON_DATA:
            if (!esp_http_client_is_chunked_response(evt->client)) {
                int copy_len = evt->data_len;
                if (resp->length + copy_len >= resp->max_len) {
                    copy_len = resp->max_len - resp->length - 1;
                }
                if (copy_len > 0) {
                    memcpy(resp->buffer + resp->length, evt->data, copy_len);
                    resp->length += copy_len;
                    resp->buffer[resp->length] = '\0';
                }
            }
            break;
        default:
            break;
    }
    return ESP_OK;
}

esp_err_t http_get_req(
    const char *base_url,
    const char *query,
    char *out_buffer,
    const int out_buffer_size
) {
    char url[256];
    if (query && strlen(query) > 0) {
        snprintf(url, sizeof(url), "%s?%s", base_url, query);
    } else {
        strncpy(url, base_url, sizeof(url));
    }
    http_response_t resp = {
        .buffer = out_buffer,
        .max_len = out_buffer_size,
        .length = 0,
        .overflow = false
    };
    out_buffer[0]='\0';


    const esp_http_client_config_t cfg = {
        .url = url,
        .method = HTTP_METHOD_GET,
        .event_handler = http_response_handler,
        .skip_cert_common_name_check = true,
        .use_global_ca_store = false,
        .cert_pem = NULL,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .user_data = &resp,
        .timeout_ms = 5000,
    };
    const esp_http_client_handle_t client = esp_http_client_init(&cfg);
    const esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(HC_TAG,"GET Status = %d, overflow=%d", esp_http_client_get_status_code(client),resp.overflow);
    } else {
        ESP_LOGE(HC_TAG, "GET request failed: %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);

    return err;
}

esp_err_t http_post_req(
    const char *url,
    const char *data,
    const char *content_type,
    char *out_buffer,
    const int out_buffer_size
) {
    http_response_t resp = {
        .buffer = out_buffer,
        .max_len = out_buffer_size,
        .length = 0,
        .overflow = false,
    };
    out_buffer[0]='\0';

    const esp_http_client_config_t cfg = {
        .url = url,
        .method = HTTP_METHOD_POST,
        .skip_cert_common_name_check = true,
        .use_global_ca_store = false,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .cert_pem = NULL,
        .timeout_ms = 5000,
    };
    const esp_http_client_handle_t client = esp_http_client_init(&cfg);
    if (content_type) {
        esp_http_client_set_header(client, "Content-Type", content_type);
    }
    if (data) {
        esp_http_client_set_post_field(client, data, strlen(data));
    }
    const esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(HC_TAG, "POST Status = %d, overflow=%d", esp_http_client_get_status_code(client), resp.overflow);
    } else {
        ESP_LOGE(HC_TAG, "POST failed: %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
    return err;
}