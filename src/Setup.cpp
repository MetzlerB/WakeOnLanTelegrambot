#include "Setup.h"

bool Setup::checkSetup(){
    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return false;
    }
  
  File ApConfig = LittleFS.open("/ApConfig.txt", "r");
    if(!ApConfig){
        Serial.println("Failed to open ApConfig for reading");
        return false;
    }
  
    Serial.println("File Content:");
    while(ApConfig.available()){
        Serial.println(ApConfig.readStringUntil('\n'));
    }
    ApConfig.close();
    return true;
}

void Setup::configAP(){
    
}