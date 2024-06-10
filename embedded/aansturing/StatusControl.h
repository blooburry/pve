#include "Motors.h"

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
      DUW_BLOK
    };
    enum VolgendeBocht { // als hij moet onthouden dat hij bij het volgende kruispunt naar links of rechts moet
      NONE,
      LINKS,
      RECHTS
    };
    StatusControl(Motors* motors);
    void tick();
    void proxSetSpeeds(int, int);
    void lijnSetSpeeds(int, int);
    void setStatus(Status);

  private:
    Status status;
    Status prevStatus; // om bij te houden of hij in deze tick van status is verandert - in feite een P-trigger
    VolgendeBocht volgendeBocht;
    Motors* motors;
    int[] proxInstructions; // wat de Prox wil dat de robot doet
    int[] lijnInstructions; // wat de Lijnsensor wil dat de robot doet.
};

#endif