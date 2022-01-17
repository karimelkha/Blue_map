#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <WebServer.h>
#include <sstream>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

/*const char* ssid = "Vincent";
const char* password = "mqtt2021";*/
const char* ssid = "SFR-1df8";
const char* password = "Y5UJNCPHDE99XSQYFS4G";
const char* serverName = "http://6d2f-85-68-13-183.ngrok.io";

String scanIDJsonField = "Id";
String UIDJsonField = "Name";
String distanceJsonField = "L";

HTTPClient http;
// Better device management is possible
const int myId = 1;

int scanTime = 30; //In seconds

void setup() {
  Serial.begin(115200);
}

String getJSONQuery(String nm,int myID, int distance){
  std::ostringstream  myIDS , distanceS;
  myIDS << myID ;
  distanceS << distance;
  
  return "{\"" + scanIDJsonField + "\":\"" +  myIDS.str().c_str()
    + "\",\"" + UIDJsonField + "\":\"" + nm
    +"\",\"" + distanceJsonField + "\":\"" + distanceS.str().c_str()
    + "\"}";
}
void loop() {
    char buffer[2048]={0};
    int httpReponseCode ;
    int nrDevice = 0;
    BLEAdvertisedDevice curDevice;
    std::string curName;
    HTTPClient http; 
    
    String httpQuery ; 
    BLEDevice::init("");
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    BLEScanResults foundDevices = pBLEScan->start(scanTime);
    nrDevice = foundDevices.getCount();

    for(uint32_t i = 0 ; i < nrDevice; i++){
      curDevice = foundDevices.getDevice(i);
      curName = curDevice.getName();
      if(!curName.compare("ESP_PE")){
        httpQuery = getJSONQuery(curName.c_str(),myId,curDevice.getRSSI());
        Serial.print(httpQuery);
        // http.addHeader("Content-Type", "application/json");  
        // int httpResponseCode = http.POST(httpQuery);
      }
    }

  
    delay(5000);
}
