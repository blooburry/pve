#include "Motors.h"
#include <Zumo32U4.h>
#include "StatusControl.h"

Motors::Motors(int snelheid, StatusControl* statusControlPointer): snelheid(snelheid), status(statusControlPointer), motors() { }

void Motors::update() {

  Serial.print(F("StatusControl waardes: "));
  Serial.println(status->getLinks());
  Serial.println(status->getRechts());

  motors.setSpeeds(
    status->getLinks() ? snelheid : 0, 
    status->getRechts() ? snelheid : 0
  );
}