#include <WiFi.h>
#include <HTTPClient.h>
#include <BLEDevice.h>
#include <BLEScan.h>

//const char* ssid = "SFR-1df8";
//const char* password = "Y5UJNCPHDE99XSQYFS4G";

const char* ssid = "Redmi Note 10 5G";
const char* password = "mascarpone" ;
#define SERVER_NAME "http://4d9b-37-164-175-26.ngrok.io/data"
const String scanIDJsonField = "S";
const String UIDJsonField = "B";
const String distanceJsonField =  "D";
const String jsonEqual = "\":\"";
const String jsonSeparator  = "\",\"";
const String my_id {"scanner_1"};
void setup() {

  WiFi.mode(WIFI_STA);                    //The WiFi is in station mode
  WiFi.begin(ssid, password );
  while (WiFi.status() != WL_CONNECTED);
  BLEDevice::init("");
}

String getJSONQuery(String nm, int distance) {
  char buffD[8];
  itoa(distance, buffD, 10);
  return "{\"" + scanIDJsonField + jsonEqual +  my_id
         + jsonSeparator + UIDJsonField + jsonEqual + nm
         + jsonSeparator + distanceJsonField + jsonEqual + buffD
         + "\"}";
}



void loop() {

  WiFiClient wf_client;

  BLEScan* pBLEScan = BLEDevice::getScan();
  HTTPClient http;
  int nrDevice = 0;
  int httpResponseCode;
  BLEAdvertisedDevice curDevice;

  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster

  BLEScanResults foundDevices = pBLEScan->start(10);
  nrDevice = foundDevices.getCount();
  if (WiFi.status() == WL_CONNECTED) {
    for (uint32_t i = 0 ; i < nrDevice; i++) {
      Serial.println(nrDevice);
      if (!foundDevices.getDevice(i).getName().compare("ESP_PE")) {
        
        http.begin( wf_client, SERVER_NAME);
        http.addHeader("Content-Type", "application/json");
        http.POST(getJSONQuery("ESP_PE",  1));
        http.end();
      }
    }
  }
  http.begin( wf_client, SERVER_NAME);
  http.addHeader("Content-Type", "application/json");
  http.POST(getJSONQuery("EE",  1));
  http.end();
  delay(5000);
}
