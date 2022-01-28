#include <WiFi.h>
#include <HTTPClient.h>

#ifndef ble_on
#define ble_on 0
#endif
#if ble_on
#include <BLEDevice.h>
#include <BLEScan.h>
#else

#endif

const char* ssid = "SFR-1df8";
const char* password = "Y5UJNCPHDE99XSQYFS4G";

#define SERVER_NAME "http://245a-85-68-13-183.ngrok.io/data"
const String scanIDJsonField = "S";
const String UIDJsonField = "B";
const String distanceJsonField =  "D";
const String jsonEqual = "\":\"";
const String jsonSeparator  = "\",\"";


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);                    //The WiFi is in station mode
  WiFi.begin(ssid,password );
  while (WiFi.status() != WL_CONNECTED);

}

String getJSONQuery(String nm, int myID, int distance) {
  char buff[16];
  char buffD[16];
  itoa(myID, buff, 10);
  itoa(distance, buffD, 10);
  return "{\"" + scanIDJsonField + jsonEqual +  buff
         + jsonSeparator + UIDJsonField + jsonEqual + nm
         + jsonSeparator + distanceJsonField + jsonEqual + buffD
         + "\"}";
}


void loop() {

  int nrDevice = 0;
  WiFiClient wf_client;
  
#if ble_on
  BLEAdvertisedDevice curDevice;
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  BLEScanResults foundDevices = pBLEScan->start(10);
  nrDevice = foundDevices.getCount();
#endif
  std::string curName;
  String httpQuery;
  int httpResponseCode;

  if (WiFi.status() == WL_CONNECTED) {
#if ble_on
//
//      for (uint32_t i = 0 ; i < nrDevice; i++) {
//        curDevice = foundDevices.getDevice(i);
//        curName = curDevice.getName();
//        if (!curDevice.getName().compare("ESP_PE")) {
//
//          
//          }
//        }
//      }
//#else

#endif
      
      /*SEND GET TO CHECK*/
      http.addHeader("Content-Type", "application/json");
      httpQuery = getJSONQuery("ESP_PE", 1, 1);
    
      httpResponseCode = http.POST(httpQuery);
      Serial.println(httpResponseCode);
      Serial.println(httpQuery);
      http.end();

    
  }
  delay(5000);
}
