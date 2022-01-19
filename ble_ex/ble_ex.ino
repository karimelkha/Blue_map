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
float N = 10 * 4.0;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
      int rssiValue;
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
        for(i = 0; i < 2; i++)
      {
        if(strcmp(advertisedDevice.getName().c_str(),"ESP_PE") == 0)
        {
          Serial.println("Device found");
          rssiValue   = advertisedDevice.getRSSI();
          deviceName  = advertisedDevice.getServiceUUID().toString();
          txValue     = advertisedDevice.getTXPower();
          measure     = (txValue*10 - rssiValue) / N;
          distance    = pow(10, measure);
          tab[i]      = distance;
        }
      }
      if(tab[0] > 10.00000 && tab[1] > 10.00000)
      {
        Serial.printf("tab[0] : %f\n",tab[0]);
        Serial.printf("tab[1] : %f\n",tab[1]);
        mean = (tab[0] + tab[1])/2;
        //mean_prec = mean;
        Serial.printf("mean : %f mm\n",mean);
        //Serial.printf("mean_prec : %f\n",mean_prec);
        Serial.printf("\n");
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
