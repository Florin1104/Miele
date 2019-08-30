#ifndef _HTTP_SERVER_H
#define _HTTP_SERVER_H


#include "esp_http_server.h"
#include "motor.h"

    class Http_server
    {
        private:
            

        public:
            void setServer(char* SSID, char* PASSWORD);
            Http_server(){};
            ~Http_server(){};
    };



#endif
