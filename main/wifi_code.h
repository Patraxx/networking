#ifndef WIFI_CODE_H
#define WIFI_CODE_H

#include "includes.h"

void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void wifi_init_sta();

#endif