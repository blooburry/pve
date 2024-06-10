#include <Zumo32U4.h>

#ifndef MOTORS_H
#define MOTORS_H

// Beheert de encoder en motor klassen uit de Zumo library.
class Motors {
  public:
    Motors();

    static const int MEDIUM_SPEED = 200;
    static const int SLOW_SPEED = 100;
    static const int MAX_SPEED = 400;

    void setSpeeds(int, int);

  private:
    Zumo32U4Motors motors;
};

#endif