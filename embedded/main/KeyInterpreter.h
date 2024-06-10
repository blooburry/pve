#include <Zumo32U4.h>

#include <SimpleVector.h>

#include "Xbee.h"

using namespace std;


#ifndef KEYINTERPRETER_H
#define KEYINTERPRETER_H


class KeyInterpreter {
public:
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

  KeyInterpreter(Xbee* xbPtr);
  ~KeyInterpreter();
  Commando keyStatus();
private:
  Xbee* xb;
  String input;
  Commando keystatus;

};

#endif
