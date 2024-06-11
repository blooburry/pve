#include "StatusControl.h"
#include "Motors.h"

using Status = StatusControl::Status;
using VolgendeBocht = StatusControl::VolgendeBocht;
using Commando = StatusControl::Commando;

const int max = 300;
const int maxGroen = 150;

StatusControl::StatusControl(Motors *motors) : motors(motors),
                                               status(Status::IDLE),
                                               volgendeBocht(VolgendeBocht::NONE)
{
}

void StatusControl::proxSetSpeeds(int left, int right)
{
  if (status == Status::DUW_BLOK)
  {
    motors->setSpeeds(left, right);
  }
}

void StatusControl::lijnSetSpeeds(int left, int right)
{
  if (
    status == Status::VOLG_LIJN_GROEN 
    || status == Status::VOLG_LIJN_ZWART 
    || status == Status::CALIBREREN 
    || status == Status::ZOEK_LIJN
  )
  {
    motors->setSpeeds(left, right);
  } else {
    // Serial1.print("Status is ");
    // Serial1.print(status);
    // Serial1.println(", ignoring instruction.");
  }
}

void StatusControl::setStatus(Status status)
{
  if(this->status == Status::HANDMODUS) { // als hij in handmodus staat, kan hij er niet uit met `setStatus`
    return;
  }

  this->status = status;
  Serial1.println(status);

  switch (status) {
    case Status::VOLG_LIJN_ZWART :
    case Status::VOLG_LIJN_GROEN :
      break;
    case Status::ZOEK_LIJN: 
      motors->setSpeeds(maxGroen, maxGroen);
      break;
  }
}

void StatusControl::besturing(Commando c)
{
  if (c == Commando::BEGIN_MET_XBEE_GEBRUIK)
  {
    motors->setSpeeds(0, 0);
    status = Status::HANDMODUS;
  }

  if (status == Status::HANDMODUS)
  {
    if (c == Commando::RECHTDOOR)
    {
      motors->setSpeeds(Motors::MEDIUM_SPEED, Motors::MEDIUM_SPEED);
    }
    if (c == Commando::ACHTERUIT)
    {
      motors->setSpeeds(-(Motors::MEDIUM_SPEED), -(Motors::MEDIUM_SPEED));
    }

    if (c == Commando::BOCHT_LINKS)
    {
      motors->setSpeeds(0, Motors::MEDIUM_SPEED);
    }

    if (c == Commando::BOCHT_RECHTS)
    {
      motors->setSpeeds(Motors::MEDIUM_SPEED, 0);
    }

    if (c == Commando::SNEL_RECHTDOOR)
    {
      motors->setSpeeds(Motors::MAX_SPEED, Motors::MAX_SPEED);
    }

    if (c == Commando::SNEL_ACHTERUIT)
    {
      motors->setSpeeds(-(Motors::MAX_SPEED), -(Motors::MAX_SPEED));
    }

    if (c == Commando::SCHERPE_BOCHT_LINKS)
    {
      motors->setSpeeds(0, Motors::MAX_SPEED);
    }

    if (c == Commando::SCHERPE_BOCHT_RECHTS)
    {
      motors->setSpeeds(Motors::MAX_SPEED, 0);
    }

    if (c == Commando::ZET_PROXYSENSORS_AAN)
    {
      status = Status::DUW_BLOK;
    }

    if (c == Commando::STOP_MOTORS)
    {
      motors->setSpeeds(0, 0);
    }

    if (c == Commando::STOP_MET_XBEE_GEBRUIK)
    {
      status = Status::IDLE;
    }
  } else {
    Serial1.println("Niet in handmodus, commando wordt genegeerd");
  }
}