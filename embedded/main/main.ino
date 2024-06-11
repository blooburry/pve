#include <Wire.h>
#include <Zumo32U4.h>
// #include "IMUSensor.h"
#include "ProxySensor.h"
#include "SensorDataBuffer.h"
#include "Xbee.h"
#include "KeyInterpreter.h"
#include "StatusControl.h"
#include "Motors.h"
#include "LijnSensor.h"

using Status = StatusControl::Status;

int tijd = 0;
int tijd2 = 0;
Motors motors;
StatusControl sc(&motors);
SensorDataBuffer buffer;
// IMUSensor imu(&buffer);
ProxySensor prox(&buffer, &sc);
LijnSensor lijn(&buffer, &sc);

Xbee xb;
KeyInterpreter kp(&xb, &sc);

Zumo32U4ButtonA buttonA;

void setup() {
  Wire.begin();
  Serial.begin(9600);  // baud rate
  Serial1.begin(9600);

  Serial1.println(F("Press A"));
  buttonA.waitForButton();

  Serial1.println(F("======================================="));
  Serial1.println(F("Program start!"));
  Serial1.print(F("Battery voltage: "));
  Serial1.println(readBatteryMillivolts());

  lijn.calibreer();
  Serial1.println("Setup klaar!");
}

void loop() {
  kp.keyStatus();
  lijn.stuurNaarMotor();
  prox.zieObject();

  if ((int)(millis() - tijd2) >= 1000) {  // elke seconde (ongeveer)
    tijd2 = millis();
    // Stuur sensor data naar XBee
    // imu.sendToBuffer();
    prox.sendToBuffer();
    lijn.sendToBuffer();
  }

  if ((int)(millis() - tijd) >= 10000) {  // elke 10 seconden (ongeveer)
    tijd = millis();

    Serial1.print(F("t="));
    Serial1.print(millis() / 1000);
    Serial1.println(F("s"));

    buffer.stuurData();
  }
}
