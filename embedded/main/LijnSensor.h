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

  /*! reference to the LijnSensor object */
  const float Cpro = 0.7;
  const float Cint = 0.0;
  const float Cafg = 6.0;
  const int dodeHoek = 100;
  SensorDataBuffer* datasink;
 // const int bufferSize = 5;  // Size of the buffer to store sensor readings
  //SimpleVector<unsigned int> LijnSensordataBuffer[5];  // Buffer to store sensor readings

public:
  unsigned int lsData[5];

  LijnSensor(SensorDataBuffer* datasinkPointer, StatusControl* sc);

  /*! destructor */
  ~LijnSensor();

  /*! this method handles the calibration of the values found bu the line sensor */
  void calibreer();
  void stuurNaarMotor();
  void sendToBuffer();
};

#endif