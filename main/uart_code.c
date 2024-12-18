#include "uart_code.h"
// Include the FreeRTOS configuration header

uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
};


    // uart_param_config(UART_NUM_0, &uart_config);
    // uart_driver_install(UART_NUM_0, 1024, 1024, 0, NULL, 0);

char* read_uart_data(uint8_t* data, char* input_buffer, int* buffer_index) {

    int len = uart_read_bytes(UART_NUM_0, data, 128, pdMS_TO_TICKS(100));  //nått kan va knas här med pdms
    if (len > 0) {
        for (int i = 0; i < len; i++) {
            if (data[i] == '\n' || data[i] == '\r') {  // End of input
                input_buffer[*buffer_index] = '\0';   // Null-terminate
               // printf("Received: %s\n", input_buffer);
                *buffer_index = 0;                   // Reset index
                return input_buffer;                // Return the string
            } else {
                if (*buffer_index < 127) {
                    input_buffer[*buffer_index] = data[i];
                    (*buffer_index)++;
                } else {
                    // Buffer overflow
                    printf("Error: Input buffer overflow. Resetting.\n");
                    *buffer_index = 0;               // Reset index
                }
            }
        }
    }
    return NULL;  // No complete line received yet
}


/*

void task_5(void* pvParameters){

    uint8_t data[128];
    char input_buffer[128] = {0};
    int buffer_index = 0;

    while (1) {
        char* input_string = read_uart_data(data, input_buffer, &buffer_index);
        if (input_string != NULL) {
            // Process the received string here
            printf("Processed: %s\n", input_string);
        }
        vTaskDelay(pdMS_TO_TICKS(100));  // Optional delay
    }
    vTaskDelete(NULL);
}


*/