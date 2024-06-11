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
  /*! constructor */
  KeyInterpreter(Xbee* xbPtr, StatusControl* sc);

  /*! destructor */
  ~KeyInterpreter();
  /*! methode die het toetsenbord checkt voor input en stuurt deze door naar de statuscontrol klasse */
  void keyStatus();
private:

  
  Xbee* xb; //!< Xbee pointer
  String input; //!< object dat de input toetsen bevat
  Commando keystatus; //<! object die de commands aan de motors bevat
  StatusControl* sc; //!< statuscontrol pointer
};

#endif
