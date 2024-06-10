#include "StatusControl.h"
#include "Motors.h"

using Status = StatusControl::Status;
using VolgendeBocht = StatusControl::VolgendeBocht;

StatusControl::StatusControl(Motors* motors): 
    motors(motors), 
    status(Status::IDLE),
    volgendeBocht(VolgendeBocht::NONE)
{ }

void StatusControl::proxSetSpeeds(int left, int right) {
  if(status == Status::DUW_BLOK) {
    motors->setSpeeds(left, right);
  }
}

void StatusControl::lijnSetSpeeds(int left, int right) {
  if(status == Status::VOLG_LIJN_GROEN 
    || status == Status::VOLG_LIJN_ZWART
    || status == Status::CALIBREREN
  ) {
    motors->setSpeeds(left, right);
  }
}

void StatusControl::setStatus(Status s) {
  status = s;
  Serial1.print("Status changed to: ");
  Serial1.println(s);
}