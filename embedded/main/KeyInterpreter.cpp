#include "KeyInterpreter.h"
#include "Xbee.h"
#include "StatusControl.h"

using Commando = StatusControl::Commando;

KeyInterpreter::KeyInterpreter(Xbee* xbPtr, StatusControl* sc)
  : xb(xbPtr), sc(sc) {
  Serial.begin(9600);
  Serial1.begin(9600);
}
KeyInterpreter::~KeyInterpreter() {}

void KeyInterpreter::keyStatus() {  //leeste data van de xbee en geeft een bijbehorende return eraan
  input = xb->leesDataIn();
  
  if (input.equals("Y")) {
    keystatus = Commando::BEGIN_MET_XBEE_GEBRUIK;
    sc->besturing(keystatus);
    return;
  }

  if (input.equals("w")) {
    keystatus = Commando::RECHTDOOR;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("s")) {
    keystatus = Commando::ACHTERUIT;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("a")) {
    keystatus = Commando::BOCHT_LINKS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("d")) {
    keystatus = Commando::BOCHT_RECHTS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("W")) {
    keystatus = Commando::SNEL_RECHTDOOR;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("S")) {
    keystatus = Commando::SNEL_ACHTERUIT;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("q")) {  // scherpe bocht naar links
    keystatus = Commando::SCHERPE_BOCHT_LINKS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("e")) {
    keystatus = Commando::SCHERPE_BOCHT_RECHTS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("b")) {
    keystatus = Commando::ZET_PROXYSENSORS_AAN;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("f")) {
    keystatus = Commando::STOP_MOTORS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("x")) {
    keystatus = Commando::STOP_MET_XBEE_GEBRUIK;
    sc->besturing(keystatus);
    return;
  }
}
