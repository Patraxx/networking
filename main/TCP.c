#include "TCP.h"


int socket_create(int socket_type){
    if(socket_type != UDP_SOCKET && socket_type != TCP_SOCKET){
        ESP_LOGE("socket_create", "Invalid socket type");
        return -1;
    }
    int sock = socket(AF_INET, socket_type == UDP_SOCKET ? SOCK_DGRAM : SOCK_STREAM, 0);
    if(sock < 0){
        ESP_LOGE("socket_create", "Failed to create socket");
        close(sock);
        return -1;
    }
    ESP_LOGI("socket_create", "Socket created: %d", sock);
    return sock;
}

int setup_address(struct sockaddr_in *server_address, const char *ip, int port){
   memset(server_address, 0, sizeof(*server_address));
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(port);
   // inet_ntoa(server_address->sin_addr, addr.str, sizeof(addr.str) -1);

    if (ip == NULL || inet_pton(AF_INET, ip, &server_address->sin_addr) <= 0){
        if(ip != NULL){
            ESP_LOGE("setup_address", "Invalid address/ Address not supported: %s", ip);
            return -1;
        } 
        server_address->sin_addr.s_addr = htonl(INADDR_ANY);
        return 0;
    } 
    return 0;
}

void socket_bind(int socket, struct sockaddr_in *server_address, const char *device_ip){
    if(bind(socket, (struct sockaddr *)server_address, sizeof(*server_address)) < 0){
        ESP_LOGE("socket_bind", "Failed to bind socket");
        close(socket);      
    }
}

void TCP_Server_Task(void* pvParameters){

    struct sockaddr_in server_address;

    int err = setup_address(&server_address, ip, PORT);

    for(;;){

        int socket = socket_create(TCP_SOCKET);









    }

    
}


/*

void createTCPReciever(void *pvParameters){
    
    char addr_str[128];
    char recv_buf[64];

    int addr_family;
    int ip_protocol;

    while(1) //create the first loop that continuously tries to create a new socket if the connection fails and has to restart
    {
        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(SERVER_PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;
        inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);

        int sock = socket(addr_family, SOCK_STREAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TCP_TAG, "Unable to create socket: errno %d", errno);
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            continue;
        }
        ESP_LOGI(TCP_TAG, "Socket created, connecting to %s:%d", SERVER_IP, SERVER_PORT);

        int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err != 0) {
            ESP_LOGE(TCP_TAG, "Socket unable to connect: errno %d", errno);
            close(sock);
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            continue;
        }
        ESP_LOGI(TCP_TAG, "Successfully connected");


            while(1)
            {

                
                int len = recv(sock, recv_buf, sizeof(recv_buf) - 1, 0);
                if (len < 0) {
                    ESP_LOGE(TCP_TAG, "recv failed: errno %d", errno);
                    break;
                } else if (len == 0) {
                    ESP_LOGW(TCP_TAG, "Connection closed");
                    break;
                } else {
                    send(sock, "ACK", strlen("ACK"),0);
                    recv_buf[len] = 0; // Null-terminate whatever we received and treat like a string
                  //  ESP_LOGI(TCP_TAG, "Received: %s", recv_buf);
                    esp_log_timestamp();
                    blinker(recv_buf);
                }            
            }

    }
}


*/