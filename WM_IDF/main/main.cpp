extern "C"{
void app_main(void);
}

#include "freertos/FreeRTOS.h"
#include <stdio.h>
#include "Http_server.h"


 


//defining AP details
    char ssid[] = "Http_server_ESP32";
    char password[] = "12345678910";

void app_main() {

    Http_server server;
    server.setServer(ssid, password);

    while (1)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}