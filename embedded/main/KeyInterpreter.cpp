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
  
  if (input.equals("Y")) { // schakel over naar handmodus
    keystatus = Commando::BEGIN_MET_XBEE_GEBRUIK;
    sc->besturing(keystatus);
    return;
  }

  if (input.equals("w")) { // rechtdoor
    keystatus = Commando::RECHTDOOR;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("s")) { // achteruit
    keystatus = Commando::ACHTERUIT;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("a")) { // linksaf
    keystatus = Commando::BOCHT_LINKS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("d")) { // rechtsaf
    keystatus = Commando::BOCHT_RECHTS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("W")) { // Max speed rechtdoor
    keystatus = Commando::SNEL_RECHTDOOR;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("S")) { // Max speed achteruit
    keystatus = Commando::SNEL_ACHTERUIT;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("q")) {  // scherpe bocht naar links
    keystatus = Commando::SCHERPE_BOCHT_LINKS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("e")) { // scherpe bocht naar rechts
    keystatus = Commando::SCHERPE_BOCHT_RECHTS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("b")) { // initialiseer de proxysensor
    keystatus = Commando::ZET_PROXYSENSORS_AAN;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("f")) { // stop de motoren
    keystatus = Commando::STOP_MOTORS;
    sc->besturing(keystatus);
    return;
  } else if (input.equals("x")) { // schakel over naar zelfrijdende modus
    keystatus = Commando::STOP_MET_XBEE_GEBRUIK;
    sc->besturing(keystatus);
    return;
  }
}
