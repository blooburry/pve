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
      DUW_BLOK, // = 5
      HANDMODUS // = 6
    };
    enum VolgendeBocht { // als hij moet onthouden dat hij bij het volgende kruispunt naar links of rechts moet
      NONE,
      LINKS,
      RECHTS
    };
    enum Commando {
      RECHTDOOR,
      SNEL_RECHTDOOR,
      BOCHT_RECHTS,
      SCHERPE_BOCHT_RECHTS,
      BOCHT_LINKS,
      SCHERPE_BOCHT_LINKS,
      ACHTERUIT,
      SNEL_ACHTERUIT,
      ZET_PROXYSENSORS_AAN,
      STOP_MOTORS,
      STOP_MET_XBEE_GEBRUIK,
      BEGIN_MET_XBEE_GEBRUIK
    };
    StatusControl(Motors* motors);
    void proxSetSpeeds(int, int);
    void lijnSetSpeeds(int, int);
    void setStatus(Status);
    void besturing(Commando);
    void setLijnPositie(int);

  private:
    Status status;
    VolgendeBocht volgendeBocht;
    Motors* motors;
    int lijnPositie;
    int* pid();
    const float Cpro = 0.35;
    const float Cint = 0.0;
    const float Cafg = 1.5;
    const int dodeHoek = 100;
};

#endif