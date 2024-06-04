#include "StatusControl.h"
#include <Zumo32U4.h>

#ifndef MOTORS_H
#define MOTORS_H

// Beheert de encoder en motor klassen uit de Zumo library.
class Motors {
  public:
    Motors(int snelheid, StatusControl* statusPointer);
    void update(); // zet de status van StatusControl over naar de motoren

    static const int MEDIUM_SPEED = 200;
    static const int SLOW_SPEED = 100;
    static const int MAX_SPEED = 400;

  private:
    StatusControl* status;
    int snelheid;
    Zumo32U4Motors motors;
};

#endif