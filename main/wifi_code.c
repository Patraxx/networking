#include "wifi_code.h"
#define SSID "Cedelerium"
#define PASSWORD "kaffemongo"

static const char *TAG = "wifi_code";

void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    ESP_LOGI(TAG, "event_id=%" PRId32, event_id);

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED)
    {
        ESP_LOGI("wifi_event_handler", "Connected to AP");
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
       // ESP_LOGI("wifi_event_handler", "Disconnected from AP");
       // xTaskDelay(5000 / portTICK_PERIOD_MS);
        esp_wifi_connect();
    }
    else if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP )
    {   
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        char ip_address[16];
        esp_ip4addr_ntoa(&event->ip_info.ip, ip_address, sizeof(ip_address));
        ESP_LOGI(TAG,"Got IP: %s", ip_address);
    }
}
void wifi_init_sta()
{   
    esp_err_t ret = nvs_flash_init();    
    ESP_ERROR_CHECK(esp_netif_init());
     ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    esp_netif_create_default_wifi_sta();
   
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = SSID,
            .password = PASSWORD,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}