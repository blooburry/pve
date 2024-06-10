#include "Motors.h"

#ifndef STATUSCONTROL_H
#define STATUSCONTROL_H

class StatusControl {
  public: 
    enum Status {
      IDLE,
      VOLG_LIJN_ZWART,
      VOLG_LIJN_GROEN, // volg de lijn met halve snelheid
      ZOEK_LIJN, // hij kan geen lijn vinden dus hij rijdt langzaam vooruit
      DUW_BLOK
    };
    enum VolgendeBocht { // als hij moet onthouden dat hij bij het volgende kruispunt naar links of rechts moet
      NONE,
      LINKS,
      RECHTS
    };
    StatusControl(Motors* motors);

  private:
    Status status;
    VolgendeBocht volgendeBocht;
    Motors* motors;
};

#endif