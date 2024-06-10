#include "KeyInterpreter.h"
#include "Xbee.h"

using Commando = KeyInterpreter::Commando;

KeyInterpreter::KeyInterpreter(Xbee* xbPtr)
  : xb(xbPtr) {
  Serial.begin(9600);
  Serial1.begin(9600);
}
KeyInterpreter::~KeyInterpreter() {}

Commando KeyInterpreter::keyStatus() {  //leeste data van de xbee en geeft een bijbehorende return eraan

  input = xb->leesDataIn();
  if (input.equals("Y")) {
    keyStatus = Commando::BEGIN_MET_XBEE_GEBRUIK;
    return keystatus;
  }
  if (input.equals("w")) {
    keystatus = Commando::RECHTDOOR;
    return keystatus;
  } else if (input.equals("s")) {
    keystatus = Commando::ACHTERUIT;
    return keystatus;
  } else if (input.equals("a")) {
    keystatus = Commando::BOCHT_LINKS;
    return keystatus;
  } else if (input.equals("d")) {
    keystatus = Commando::BOCHT_RECHTS;
    return keystatus;
  } else if (input.equals("W")) {
    keystatus = Commando::SNEL_RECHTDOOR;
    return keystatus;
  } else if (input.equals("S")) {
    keystatus = Commando::SNEL_ACHTERUIT;
    return keystatus;
  } else if (input.equals("q")) {  // scherpe bocht naar links
    keystatus = Commando::SCHERPE_BOCHT_LINKS;
    return keystatus;
  } else if (input.equals("e")) {
    keystatus = Commando::SCHERPE_BOCHT_RECHTS;
    return keystatus;
  } else if (input.equals("b")) {
    keystatus = Commando::ZET_PROXYSENSORS_AAN;
    return keystatus;
  } else if (input.equals("f")) {
    keystatus = Commando::STOP_MOTORS;
    return keystatus;
  } else if (input.equals("x")) {
    keystatus = Commando::STOP_MET_XBEE_GEBRUIK;
    return keystatus;
  }
}
