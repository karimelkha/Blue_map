/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 30; //In seconds

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    
    {
        int rssi_pe,tx_pe;
        std::string uid_pe;
      if (strcmp(advertisedDevice.getName().c_str(), "ESP_PE") == 0)
      {
        Serial.println("We found a device named esp32_pe");
        rssi_pe = advertisedDevice.getRSSI();
        uid_pe  = advertisedDevice.getServiceUUID().toString();
        tx_pe = advertisedDevice.getTXPower();
        Serial.printf("rssi : %d\n",rssi_pe);
        Serial.printf("uid : %s\n",uid_pe);
        Serial.printf("tx_power : %d\n",tx_pe);
      }else{
        Serial.println("pas device fdp");
      }
      //Serial.printf("Advertised Device: %s", advertisedDevice.toString().c_str());
      //Serial.print(" RSSI: ");
      //Serial.println(advertisedDevice.getRSSI());
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  

  
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("test");
  BLEDevice::init("");
  Serial.println("test1");
  BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
  Serial.println("test2");
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  Serial.println("test3");
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results fasterBLEDevice::init("");
  Serial.println("test4");
  BLEScanResults foundDevices = pBLEScan->start(scanTime);
  Serial.println("test5");
  int deviceCount = foundDevices.getCount();
  Serial.println("test6");
  Serial.println(deviceCount);
//  for (uint32_t i = 0; i < deviceCount; i++)
//  {
//    BLEAdvertisedDevice device = foundDevices.getDevice(i);
//
//
//    if (strcmp(device.getName().c_str(), "Mi Band 3") == 0)
//    {
//      Serial.println("We found a device named esp32_pe");
//      rssi_pe = device.getRSSI();
//      Serial.printf("rssi : %d",rssi_pe);
//    }else{
//       Serial.println("pas device fdp");
//      }
//  }
  
  //delay(10000);
  delay(2000);
}
