#include "Motors.h"
#include <Zumo32U4.h>
#include "StatusControl.h"

Motors::Motors(): motors() { }

void Motors::setSpeeds(int left, int right) {
  motors.setSpeeds(left, right);
}