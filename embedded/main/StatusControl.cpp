#include "StatusControl.h"
#include "Motors.h"
#include "ProxySensor.h"

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
    delay(500);
    
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
  
  }
}

void StatusControl::setStatus(Status status)
{
  if(this->status == Status::HANDMODUS) { // als hij in handmodus staat, kan hij er niet uit met `setStatus`
    return;
  }

  if(this->status == Status::DUW_BLOK){
    //proxy->zieObject();
    Status::DUW_BLOK;
    proxSetSpeeds(150,150);
  }

  if(this->status != status) { // als de huidige status niet hetzelfde is al de variabele status dan wordt deze gelijkgesteld.
    this->status = status;
    
  }

  switch (status) { // switchcase met de lijnvolgende statussen
    case Status::VOLG_LIJN_ZWART :
    case Status::VOLG_LIJN_GROEN :
      break;
    case Status::ZOEK_LIJN: // indien geen lijn, gaat de zumo langzaam vooruit
      motors->setSpeeds(maxGroen, maxGroen); 
      break;
    
  }
}

void StatusControl::besturing(Commando c)
{
  if (c == Commando::BEGIN_MET_XBEE_GEBRUIK) // stop de motors als handmodus wordt aangezet
  {
    motors->setSpeeds(0, 0);
    status = Status::HANDMODUS;
  }

  if (status == Status::HANDMODUS) // als de handmodus aanstaat kan de zumo reageren op toetsenbord commando's
  {
    if (c == Commando::RECHTDOOR) // vooruit rijden
    {
      motors->setSpeeds(Motors::MEDIUM_SPEED, Motors::MEDIUM_SPEED);
    }
    if (c == Commando::ACHTERUIT) // achteruit rijden
    {
      motors->setSpeeds(-(Motors::MEDIUM_SPEED), -(Motors::MEDIUM_SPEED));
    }

    if (c == Commando::BOCHT_LINKS) // naar links afslaan
    {
      motors->setSpeeds(0, Motors::MEDIUM_SPEED);
    }

    if (c == Commando::BOCHT_RECHTS) // naar rechts afslaan
    {
      motors->setSpeeds(Motors::MEDIUM_SPEED, 0);
    }

    if (c == Commando::SNEL_RECHTDOOR) // snel rechtdoor rijden
    {
      motors->setSpeeds(Motors::MAX_SPEED, Motors::MAX_SPEED);
    }

    if (c == Commando::SNEL_ACHTERUIT) // snel achteruit rijden
    {
      motors->setSpeeds(-(Motors::MAX_SPEED), -(Motors::MAX_SPEED));
    }

    if (c == Commando::SCHERPE_BOCHT_LINKS) // snel naar links afslaan
    {
      motors->setSpeeds(0, Motors::MAX_SPEED);
    }

    if (c == Commando::SCHERPE_BOCHT_RECHTS) // snel naar rechts afslaan
    {
      motors->setSpeeds(Motors::MAX_SPEED, 0);
    }

    if (c == Commando::ZET_PROXYSENSORS_AAN)  // ga op zoek naar het blok om te duwen
    {
      status = Status::DUW_BLOK;
    }

    if (c == Commando::STOP_MOTORS)  // stop de motoren
    {
      motors->setSpeeds(0, 0);
    }

    if (c == Commando::STOP_MET_XBEE_GEBRUIK) // als de handmodus wordt uitgeschakeld wordt de zumo IDLE
    {
      status = Status::IDLE;
    }
  } else { // als de handmodus uit staat maar er wordt een commando ingevoerd
    Serial1.println("Niet in handmodus, commando wordt genegeerd");
  }
}

Status StatusControl::SCStatus(){
  return status;
}
