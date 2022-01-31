#include <WiFi.h>
#include <HTTPClient.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
//#include <math.h>

int scanTime = 30; //In seconds
float N = 10.0 * 3.3;
float measuredPower = -70.0; // RSSI mesure pour 1m entre 2 esp32
float rssiValue;
float distance, measure;
std::string deviceName;
std::string prenom ("ESP_PE");
const char* ssid = "Redmi Note 10 5G";
const char* password = "mascarpone";
int nrDevice = 0;
WiFiClient wf_client;
std::string curName;
String httpQuery;
int httpResponseCode;

#define SERVER_NAME "http://8acd-37-172-8-127.ngrok.io/data"
const String scanIDJsonField = "S";
const String UIDJsonField = "B";
const String distanceJsonField =  "D";
const String jsonEqual = "\":\"";
const String jsonSeparator  = "\",\"";

String getJSONQuery(String nm, String myID, float distance) {
  char buffD[16];

  String buff = String(distance,3);
  return "{\"" + scanIDJsonField + jsonEqual +  myID
         + jsonSeparator + UIDJsonField + jsonEqual + nm
         + jsonSeparator + distanceJsonField + jsonEqual + buff
         + "\"}";
}



class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
      //Serial.printf("Scanning device ");
      while (1)
      {
        if (prenom.compare(advertisedDevice.getName()) == 0)
        {
          //Serial.println("Device found");
          //Serial.println("33333333333333");
          Serial.println(deviceName.c_str());
          rssiValue   = (float) advertisedDevice.getRSSI();
          deviceName  = advertisedDevice.getServiceUUID().toString();
          Serial.printf("rssi = %f\n",rssiValue);
          //Serial.printf("tx = %d\n",txValue);
          measure     = (measuredPower - rssiValue) / N;
          printf("measure = %f\n",measure);
          distance    = powf(10.0, measure);
          //printf("distance = %f\n",distance);
          if (WiFi.status() == WL_CONNECTED) {
            Serial.println(deviceName.c_str());
            HTTPClient http;
            http.begin( wf_client, SERVER_NAME);
            http.addHeader("Content-Type", "application/json");
            httpQuery = getJSONQuery("SCAN_PE3", deviceName.c_str(),  distance);
            http.POST(httpQuery);
            http.end();
            delay(2000);
          }else{
            Serial.println("Pas connecte  au wifi");
          }
          delay(100);
        }

      }
    }
};
// PE1 : 1,63
// PE2 : 1,80
// PE3 : 3,775





void setup() {
  //Serial.begin(115200);
  //Serial.println("Scanning...");
  WiFi.mode(WIFI_STA);                    //The WiFi is in station mode
  WiFi.begin(ssid, password );
  while (WiFi.status() != WL_CONNECTED);
}

void loop() {
  // put your main code here, to run repeatedly:
  int deviceCount;
  BLEScanResults foundDevices;
  BLEScan* pBLEScan;


  BLEDevice :: init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan -> setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan -> setActiveScan(true); //active scan uses more power, but get results fasterBLEDevice::init("");
  foundDevices = pBLEScan->start(scanTime);
  deviceCount  = foundDevices.getCount();
}
