#include "ProxySensor.h"

#include <Zumo32U4.h>

ProxySensor proxy;

void setup() {
  proxy.setup();
}

void loop() {
  proxy.ZieObject();
  proxy.printReadingsToSerial();
}
