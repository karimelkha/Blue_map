#include <WiFi.h>
#include <HTTPClient.h>
#include <BLEDevice.h>
#include <BLEScan.h>

//const char* ssid = "SFR-1df8";
//const char* password = "Y5UJNCPHDE99XSQYFS4G";

const char* ssid = "Redmi Note 10 5G";
const char* password = "mascarpone" ;
#define SERVER_NAME "http://3d2d-37-172-171-104.ngrok.io/data/SCANNER_3"
const String scanIDJsonField = "S";
const String UIDJsonField = "B";
const String distanceJsonField =  "D";
const String jsonEqual = "\":\"";
const String jsonSeparator  = "\",\"";
const String my_id {"scanner_2"};
std::string deviceName;
std::string prenom ("ESP_PE");
int scanTime = 30; //In seconds
float N = 10.0 * 3.3;
float measuredPower = -70.0; // RSSI mesure pour 1m entre 2 esp32
float rssiValue;
float distance, measure;
String httpQuery;
void setup() {

  WiFi.mode(WIFI_STA);                    //The WiFi is in station mode
  WiFi.begin(ssid, password );
  while (WiFi.status() != WL_CONNECTED);
  BLEDevice::init("");
  Serial.begin(115200);
  Serial.println("Scanning...");
}

String getJSONQuery(String nm, float distance) {
  String message = "{\"" + scanIDJsonField + jsonEqual +  my_id
         + jsonSeparator + UIDJsonField + jsonEqual + nm
         + jsonSeparator + distanceJsonField + jsonEqual + String(distance)
         + "\"}";
  Serial.println(message);
  return "{\"" + scanIDJsonField + jsonEqual +  my_id
         + jsonSeparator + UIDJsonField + jsonEqual + nm
         + jsonSeparator + distanceJsonField + jsonEqual + String(distance)
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
      //Serial.println(nrDevice);
      if (!foundDevices.getDevice(i).getName().compare("ESP_PE")) {
        rssiValue   = (float) foundDevices.getDevice(i).getRSSI();
        deviceName  = foundDevices.getDevice(i).getName();
        Serial.println(deviceName.c_str());
        Serial.printf("rssi = %f\n", rssiValue);
        measure     = (measuredPower - rssiValue) / N;
        distance    = powf(10.0, measure);
        http.begin( wf_client, SERVER_NAME);
        http.addHeader("Content-Type", "application/json");
        httpQuery = getJSONQuery(deviceName.c_str(),  distance);
        http.POST(httpQuery);
        http.end();
      }
    }
  }

  delay(2000);
}
