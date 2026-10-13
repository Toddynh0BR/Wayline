#include <Arduino.h>
#include "app/screen_manager.h"
#include "hardware/hardware_status.h"

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("\nWAYLINE V1 - firmware bootstrap");
  wayline::hardware::begin();
  wayline::ui::begin();
}

void loop() {
  wayline::ui::update();
  wayline::hardware::update();
  delay(5);
}
