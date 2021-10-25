#include <M5StickC.h>
#include "BLEDevice.h"
 
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define SERVER_NAME         "M5Stack"
 
static BLEUUID  serviceUUID(SERVICE_UUID);
static BLEUUID  charUUID(CHARACTERISTIC_UUID);

static BLEAddress *pServerAddress;
static boolean doConnect = false;
static boolean connected = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
  ;
}
bool connectToServer(BLEAddress pAddress) {
    BLEClient*  pClient  = BLEDevice::createClient();
    pClient->connect(pAddress);
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      return false;
    }
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      return false;
    }
    pRemoteCharacteristic->registerForNotify(notifyCallback);
}
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if(advertisedDevice.getName()==SERVER_NAME){ //
      advertisedDevice.getScan()->stop();
      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      doConnect = true;
    }
  }
};
void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.MPU6886.Init();
  M5.Lcd.println("Start!");
  
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(10);
}
void loop() {
  M5.update();
  if(M5.BtnB.isPressed()){
    pRemoteCharacteristic->writeValue("Btn B!");
  }
  if (doConnect == true) {
    if (connectToServer(*pServerAddress)) {
      M5.Lcd.println("connected!");
      connected = true;
    } else {
      connected = false;
    }
    doConnect = false;
  }
  if (connected) {
    std::string value = pRemoteCharacteristic->readValue();
    String strVal=value.c_str();
    M5.Lcd.println(strVal);
  } else{
    doConnect = true;
  }
  delay(2000);
}
