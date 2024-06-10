#include "Motors.h"
#include "KeyInterpreter.h"
#include "ProxySensor.h"


#ifndef STATUSCONTROL_H
#define STATUSCONTROL_H

class StatusControl {
  public: 
    enum Status {
      IDLE,
      CALIBREREN,
      VOLG_LIJN_ZWART,
      VOLG_LIJN_GROEN, // volg de lijn met halve snelheid
      ZOEK_LIJN, // hij kan geen lijn vinden dus hij rijdt langzaam vooruit
      DUW_BLOK,
      HANDMODUS
    };
    enum VolgendeBocht { // als hij moet onthouden dat hij bij het volgende kruispunt naar links of rechts moet
      NONE,
      LINKS,
      RECHTS
    };
    StatusControl(Motors* motors);
    void proxSetSpeeds(int, int);
    void lijnSetSpeeds(int, int);
    void setStatus(Status);
    void besturing(Commando);

  private:
    Status status;
    VolgendeBocht volgendeBocht;
    Motors* motors;
    ProxySensor* prox;
};

#endif