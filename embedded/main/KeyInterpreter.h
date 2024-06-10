#include <Zumo32U4.h>

#include <SimpleVector.h>

#include "StatusControl.h"
#include "Xbee.h"

using namespace std;
using Commando = StatusControl::Commando;

#ifndef KEYINTERPRETER_H
#define KEYINTERPRETER_H


class KeyInterpreter {
public:
  KeyInterpreter(Xbee* xbPtr, StatusControl* sc);
  ~KeyInterpreter();
  void keyStatus();
private:
  Xbee* xb;
  String input;
  Commando keystatus;
  StatusControl* sc;
};

#endif
