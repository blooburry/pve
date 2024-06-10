#include "Motors.h"

#ifndef STATUSCONTROL_H
#define STATUSCONTROL_H

class StatusControl {
  public: 
    enum Status {
      IDLE, // = 0
      CALIBREREN, // = 1
      VOLG_LIJN_ZWART, // = 2
      VOLG_LIJN_GROEN, // = 3, volg de lijn met halve snelheid
      ZOEK_LIJN, // = 4, hij kan geen lijn vinden dus hij rijdt langzaam vooruit
      DUW_BLOK // = 5
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

  private:
    Status status;
    VolgendeBocht volgendeBocht;
    Motors* motors;
};

#endif