#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Name of the Setup AP
const char *apSSID = "Setup_your_WOL_Stick";
//Setup password is not needed but can be set
const char *apPassword = "";
//Setup IP
IPAddress apIP(192,168,4,1);

int debbug_level = 0;

void setup() {
  //Setup via AP
  Serial.begin(115200);
  delay(10);
  //Check if already connected to a Wifi
  if(WiFi.status()==WL_CONNECTED){
    if(debbug_level>=1){
      Serial.println("Already connected");
      Serial.print("Connectet IP: ");
      Serial.println(WiFi.localIP());
    }
    return;
  }

  if(debbug_level>=1){
      Serial.print("AP IP: ");
      Serial.println(WiFi.softAPIP());
    }

}

void loop() {
  // put your main code here, to run repeatedly:
}