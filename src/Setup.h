#ifndef SETUP_H
#define SETUP_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

class Setup{
    private:

    public:
    	bool checkSetup();
        void configAP();



};





#endif