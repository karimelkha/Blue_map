/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <math.h>

int scanTime = 30; //In seconds
float N = 10.0 * 3.3;
float measuredPower = -70.0; // RSSI mesure pour 1m entre 2 esp32

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
      float rssiValue;
      int8_t txValue;
      float distance, measure;
      float mean;//, mean_prec;
      float diff;
      std::string deviceName;
      int i;
      float tab[2];
      Serial.printf("Scanning device ");
      while(1)
      {
        if(strcmp(advertisedDevice.getName().c_str(),"ESP_PE") == 0)
        {
          Serial.println("Device found");
          Serial.println("33333333333333");
          rssiValue   = (float) advertisedDevice.getRSSI();
          deviceName  = advertisedDevice.getServiceUUID().toString();
          txValue     = advertisedDevice.getTXPower();
          Serial.printf("rssi = %f\n",rssiValue);
          Serial.printf("tx = %d\n",txValue);
          measure     = (measuredPower - rssiValue) / N;
          printf("measure = %f\n",measure);
          distance    = powf(10.0, measure);  
          printf("distance = %f\n",distance);
        }
      
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
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
  Serial.println(deviceCount);
  delay(2000);
}
