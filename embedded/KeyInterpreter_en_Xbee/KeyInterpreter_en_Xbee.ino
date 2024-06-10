#include "xbee.h"
#include <SimpleVector.h>
#include "keyinterpreter.h"

Xbee xb;
KeyInterpreter kp(&xb);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  String begin = "beging";
  xb.stuurDataNaarXbee(begin);
}

void loop() {
  kp.keyStatus();
}
