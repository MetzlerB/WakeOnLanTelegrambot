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

ESP8266WebServer server(80);

int debbug_level = 2;

void APSetup(){
  if(debbug_level>=1){
      Serial.println("Starting access point");
    }
  //Start AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP,IPAddress(255,255,255,0));
  WiFi.softAP(apSSID,apPassword);

  if(debbug_level>=1){
      Serial.print("AP IP: ");
      Serial.println(WiFi.softAPIP());
    }

  server.on("/", []() {
    String html = "<html><body>";
    html += "<h1>WiFi Configuration</h1>";
    html += "<form action='/connect' method='post'>";
    html += "SSID: <input type='text' name='ssid'><br>";
    html += "Password: <input type='text' name='password'><br>";
    html += "<input type='submit' value='Connect'>";
    html += "</form></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/connect",[](){
    String ssid = server.arg("ssid");
    String password = server.arg("password");
    WiFi.begin(ssid.c_str(),password.c_str());
    while(WiFi.status() != WL_CONNECTED){
      delay(1000);
      if (WiFi.status() != WL_CONNECTED){
      APSetup();
      break;
      }
    }
    server.send(200, "text/plain","Wifi is now connected");
    String html = "<html><body>";
    html += "<form action='/TelegramSetup' method='post'>";
    html += "<input type='submit' value='Connect'>";
    html += "</form></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/TelegramSetup", []() {
    String html = "<html><body>";
    html += "<h1>Telegram Setup</h1>";
    html += "BOT_TOKEN: <input type='text' name='bot_token'><br>";
    html += "ALLOWED_ID: <input type='text' name='allowed_id'><br>";
    html += "MAC_ADDRESS: <input type='text' name='mac_address'><br>";
    html += "<input type='submit' value='Connect'>";
    html += "</form></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/connect",[](){
    String BOT_TOKEN = server.arg("bot_token");
    String ALLOWED_ID = server.arg("allowed_id");
    String MAC_ADDRESS = server.arg("mac_address");
    if(debbug_level >=1){
      Serial.println("Got Telegram Info");
    }
    server.send(200, "text/plain","Telegram Info collected");
  });
  server.begin();

}

void setup() {
  //Setup via AP
  Serial.begin(115200);
  delay(10);
  //Check if already connected to a Wifi
  if(WiFi.status()!=WL_CONNECTED){
    APSetup();
  }else{
    if(debbug_level>=1){
      Serial.println("Already connected");
      Serial.print("Connectet IP: ");
      Serial.println(WiFi.localIP());
    }
    return;
  }

}

void loop() {
  server.handleClient();
}