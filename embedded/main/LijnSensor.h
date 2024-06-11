#ifndef LijnSensor_H
#define LijnSensor_H

#include "StatusControl.h"
#include <SimpleVector.h>
#include <Zumo32U4.h>
#include "SensorDataBuffer.h"

#include "KleurLijnBerekening.h"

using namespace std;
using Kleur = KleurLijnBerekening::Kleur;


/*!
this class handles the calibration of the line sensors 
*/
class LijnSensor : public Zumo32U4LineSensors {
private:
  KleurLijnBerekening ber;
  StatusControl* sc;
  SensorDataBuffer* datasink;
  const float Cpro = 0.35;
  const float Cint = 0.0;
  const float Cafg = 1.5;
  const int dodeHoek = 100;
  int16_t error = 0;
  int16_t laatstecompensatie = 0;
  int16_t integraal = 0;
  int16_t afgeleide = 0;
  int16_t output = 0;
  
  const uint16_t MAX_SPEED = 300;
  const uint16_t MAX_SPEED_GROEN = 150;

public:
  unsigned int lsData[5];

  LijnSensor(SensorDataBuffer* datasinkPointer, StatusControl* sc);

  /*! destructor */
  ~LijnSensor();

  /*! this method handles the calibration of the values found bu the line sensor */
  void calibreer();
  void stuurNaarMotor();
  void sendToBuffer();
  int absolute(int);
  int readLineGroen(unsigned int *sensor_values);
  void pid(int error, Kleur k, int& links, int& rechts);
};

#endif