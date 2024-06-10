#ifndef LijnSensor_H
#define LijnSensor_H

#include "StatusControl.h"
#include <SimpleVector.h>
#include <Zumo32U4.h>
#include "SensorDataBuffer.h"

#include "KleurLijnBerekening.h"

using namespace std;


/*!
this class handles the calibration of the line sensors 
*/
class LijnSensor : public Zumo32U4LineSensors {
private:
  KleurLijnBerekening ber;
  StatusControl* sc;
  SensorDataBuffer* datasink;

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
};

#endif