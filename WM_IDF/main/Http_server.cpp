
#include "Http_server.h"
#include <esp_log.h>
#include "esp_wifi.h"
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "nvs_flash.h"
#include "tcpip_adapter.h"
#include "esp_eth.h"
#include "string.h"
#include "esp_http_server.h"
#include "esp_event.h"
#include "string"
#include "esp_eth.h"
#include "driver/gpio.h"
#include "cJSON_Utils.h"
#include "cJSON.h"


using namespace std;

void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        //cout << "\n\nStation connected to HttpServer AP";
        //printf("\nStation: " MACSTR " joined, Device nr: %d ", MAC2STR(event->mac), event->aid);
        //printf("\n");
    }
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
        //cout << "\n\nStation disconnected from HttpServer AP";
       // printf("\nStation: " MACSTR " leaved, Device nr: %d ", MAC2STR(event->mac), event->aid);
        //printf("\n");
    }
}

esp_err_t led_handler(httpd_req_t *req) {
    char content[100];

    size_t recv_size = MIN(req->content_len, sizeof(content));

    int ret = httpd_req_recv(req, content, recv_size);

    if (ret <= 0)
    {
        /* 0 return value indicates connection closed */
        if (ret == HTTPD_SOCK_ERR_TIMEOUT)
        {

            //sending error 408 in case of connection timeout
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }

    gpio_pad_select_gpio(GPIO_NUM_17);
    gpio_set_direction(GPIO_NUM_17, GPIO_MODE_OUTPUT);


    cJSON *root = cJSON_Parse(content);
    int state = cJSON_GetObjectItem(root, "state")->valueint;

    const char resp_ON[] = "LED ON";
    const char resp_OFF[] = "LED OFF";

    if (state == 1)
    {
        gpio_set_level(GPIO_NUM_17, 1);
        httpd_resp_send(req, resp_ON, strlen(resp_ON));
    }
    else if (state == 0) 
    {   
        gpio_set_level(GPIO_NUM_17, 0);
        httpd_resp_send(req, resp_OFF, strlen(resp_OFF));
    }
    
    

return ESP_OK;    
}

esp_err_t motor_handler(httpd_req_t *req)
{
    char content[100];
    static bool init = true;
    static ledc_channel_config_t motor_config;
    static ledc_timer_config_t timer_config;
    static  Motor* motor;
    if (init)
    {
        motor = new Motor(12);
        motor->initMotor(motor_config, timer_config);
        init = false;
    }
    size_t recv_size = MIN(req->content_len, sizeof(content));

    int ret = httpd_req_recv(req, content, recv_size);

    if (ret <= 0)
    {
        /* 0 return value indicates connection closed */
        if (ret == HTTPD_SOCK_ERR_TIMEOUT)
        {

            //sending error 408 in case of connection timeout
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }

    cJSON *root = cJSON_Parse(content);
    int state = cJSON_GetObjectItem(root, "state")->valueint;
    uint8_t speed = cJSON_GetObjectItem(root, "speed")->valueint;

    const char resp_ON[] = "Starting motor";
    const char resp_OFF[] = "Stopping motor";

    if (speed <= 100 && state != 0)
    {

        motor->setSpeed(motor_config, speed);
        httpd_resp_send(req, resp_ON, strlen(resp_ON));
    }
    else if (state == 0)
    {
        motor->stopMotor(motor_config);
        httpd_resp_send(req, resp_OFF, strlen(resp_OFF));
    }

    return ESP_OK;
}

httpd_uri_t motor_uri = {
    .uri = "/motor",
    .method = HTTP_POST,
    .handler = motor_handler,
    .user_ctx = NULL};

httpd_uri_t led_uri = {
    .uri = "/led",
    .method = HTTP_POST,
    .handler = led_handler,
    .user_ctx = NULL};




static httpd_handle_t start_server(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_handle_t server = NULL;

    // Start the httpd server on port 80
   
    if (httpd_start(&server, &config) == ESP_OK)
    {
      
        int motor = ESP_OK;
        int led = ESP_OK;

        // Set URI handlers
        led = httpd_register_uri_handler(server, &led_uri);
        motor = httpd_register_uri_handler(server, &motor_uri);
      
        if (motor == ESP_OK && led == ESP_OK)
        {
        //    cout << "Thre only print i`m using, PROMISE" << endl; 
        }

        return server;
    }
    return NULL;
}

static void stop_server(httpd_handle_t server)
{

    if (server)
    {
       
        httpd_stop(server);
    }
}

static void disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{

    httpd_handle_t *server = (httpd_handle_t *)arg;

    if (*server)
    {
        
        stop_server(*server);
        *server = NULL;
    }

   
}

static void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    httpd_handle_t *server = (httpd_handle_t *)arg;

    if (*server == NULL)
    {

        *server = start_server();
    }
}

void Http_server::setServer(char *SSID, char *PASSWORD)
{

    static httpd_handle_t server = NULL;

    nvs_flash_init();

    tcpip_adapter_init();

    esp_event_loop_create_default();

    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server);
    esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server);

    wifi_init_config_t wifiConfig = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifiConfig);

    esp_wifi_set_storage(WIFI_STORAGE_FLASH);

    esp_wifi_set_mode(WIFI_MODE_AP);

    //setting wifi configuration for AP
    wifi_config_t ap_config;
    strcpy((char *)ap_config.ap.ssid, SSID);
    strcpy((char *)ap_config.ap.password, PASSWORD);
    ap_config.ap.channel = 0;
    ap_config.ap.ssid_len = strlen(SSID);
    ap_config.ap.authmode = WIFI_AUTH_WPA2_PSK;
    ap_config.ap.max_connection = 4;
    ap_config.ap.beacon_interval = 100;

    esp_wifi_set_config(ESP_IF_WIFI_AP, &ap_config);

    esp_wifi_start();
  



    //starting server after setting AP settings
    server = start_server();
}

