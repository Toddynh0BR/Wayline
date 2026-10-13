#include "hardware_status.h"
#include <Arduino.h>
namespace wayline::hardware {
namespace { bool displayOk = false, touchOk = false, gpsBusOk = false; }
void begin() {
  // TODO: integrate exact Waveshare CO5300 QSPI + CST9217 adapter here.
  // Do not install a second I2C driver: touch, RTC, IMU and LC76G share SDA15/SCL14.
  Serial.println("[HW] Waveshare display/touch adapter not integrated yet.");
}
void update() {}
bool displayReady() { return displayOk; }
bool touchReady() { return touchOk; }
bool gpsBusReady() { return gpsBusOk; }
}
