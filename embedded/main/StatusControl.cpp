#include "StatusControl.h"
#include "Motors.h"

using Status = StatusControl::Status;
using VolgendeBocht = StatusControl::VolgendeBocht;
using Commando = KeyInterpreter::Commando;

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
  if(status == Status::VOLG_LIJN_GROEN || status == Status::VOLG_LIJN_ZWART) {
    motors->setSpeeds(left, right);
  }
}

void StatusControl::setStatus(Status s) {
  status = s;
}

void StatusControl::besturing(Commando c, Status s)
{

  if (c == BEGIN_MET_XBEE_GEBRUIK){
    s = HANDMODUS;
    }
    if (s == HANDMODUS)
    {
      if (c == RECHTDOOR)
      {
        motors->setSpeeds(MEDIUM_SPEED, MEDIUM_SPEED);
      }
      if (c == ACHTERUIT)
      {
        motors->setSpeeds(-(MEDIUM_SPEED), -(MEDIUM_SPEED));
      }

      if (c == BOCHT_LINKS)
      {
        motors->setSpeeds(0, MEDIUM_SPEED);
      }

      if (c == BOCHT_RECHTS)
      {
        motors->setSpeeds(MEDIUM_SPEED, 0);
      }

      if (c == SNEL_RECHTDOOR)
      {
        motors->setSpeeds(MAX_SPEED, MAX_SPEED);
      }

      if (c == SNEL_ACHTERUIT)
      {
        motors->setSpeeds(-(MAX_SPEED), -(MAX_SPEED));
      }

      if (c == SCHERPE_BOCHT_LINKS)
      {
        motors->setSpeeds(0, MAX_SPEED);
      }

      if (c == SCHERPE_BOCHT_RECHTS)
      {
        motors->setSpeeds(MAX_SPEED, 0);
      }

      if (c == ZET_PROXYSENSOR_AAN)
      {
        prox->setup();
      }

      if (c == STOP_MOTORS)
      {
        motors->setSpeeds(0, 0);
      }

      if (c == STOP_MET_XBEE_GEBRUIK)
      {
        s = IDLE;
      }
    }
}