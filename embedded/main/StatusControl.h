#include "Motors.h"
#include "ProxySensor.h"

#ifndef STATUSCONTROL_H
#define STATUSCONTROL_H

class ProxySensor;

class StatusControl {
public:
  /*! deze enum bevat alle mogelijke statussen die de zumo kan hebben */
  enum Status {
    IDLE,             // = 0
    CALIBREREN,       // = 1
    VOLG_LIJN_ZWART,  // = 2
    VOLG_LIJN_GROEN,  // = 3, volg de lijn met halve snelheid
    ZOEK_LIJN,        // = 4, hij kan geen lijn vinden dus hij rijdt langzaam vooruit
    DUW_BLOK,         // = 5
    HANDMODUS         // = 6
  };

  /*! deze enum onthoudt een richting die de zumo bij het volgende kruispunt moet volgen */
  enum VolgendeBocht {  
    NONE,                 // geen richting/ rechtdoor
    LINKS,                // sla linksaf
    RECHTS                // sla rechtsaf
  };

  /*! deze enum bevat alle mogelijke commando's die gegeven kunnen worden in de handmatige modus */
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

  /*! constructor met pointer naar motors zodat deze aangestuurd kunnen worden */
  StatusControl(Motors* motors);
  /*! methode die de motors aanstuurt als de proxysensor actief is */
  void proxSetSpeeds(int, int);
  /*! methode die de motors aanstuurt tijdens het volgen van de lijn */
  void lijnSetSpeeds(int, int);
  /*! methode die de status veranderd en op basis van de status de snelheid van de motoren bepaald */
  void setStatus(Status);
  /*! methode die alle motorbesturing in de handmodus regelt op basis van de toetsen die worden doorgestuurd in KeyInterpreter */
  void besturing(Commando);
  /*! methode die de huidige status returned */
  Status SCStatus();

private:
  Status status; //!< object die de huidige status bevat
  VolgendeBocht volgendeBocht; //!< object met instructies voor het volgende kruispunt
  Motors* motors; //!< pointer naar motors, dit is nodig om de motors aan te sturen
  

  int lijnPositie;
};

#endif