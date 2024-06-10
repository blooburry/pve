/*#ifndef STATUSCONTROL_H
#define STATUSCONTROL_H
#include "lijnsensor.h"
#include "kleurLijnBerekening.h"

class Statuscontrol {
  private:

   Zumo32U4Motors motors;
  const float Cpro = 0.7;
  const float Cint = 0.0;
  const float Cafg = 6.0;
  int16_t compensatie;
  int16_t laatstecompensatie;
  int16_t integraal;
  int16_t afgeleide;
  int16_t output;


  const uint16_t max = 300;
  const uint16_t maxGreenSpeed = 125;
  int16_t linkssnelheid;
  int16_t rechtssnelheid;
  
  const int dodeHoek = 100;
  kleurlijnberekening ber;
  PID_berekening(int16_t);

  public:

  Statuscontrol(float, float, float);
  ~Statuscontrol();
  PID_Update(int16_t, uint16_t, uint16_t, uint16_t *LSkleur);
}*/
