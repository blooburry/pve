#ifndef LIJNSENSOR_H
#define LIJNSENSOR_H

#include "../aansturing/StatusControl.h"
#include <SimpleVector.h>
#include <Zumo32U4.h>
#include "SensorDataBuffer.h"

#include "../berekeningen/KleurLijnBerekening.h"

using namespace std;


/*!
this class handles the calibration of the line sensors 
*/
class Lijnsensor : public Zumo32U4LineSensors {
private:
  KleurLijnBerekening ber;
  StatusControl* sc;

  /*! reference to the lijnsensor object */
  Zumo32U4Motors motors;
  const float Cpro = 0.7;
  const float Cint = 0.0;
  const float Cafg = 6.0;
  const int dodeHoek = 100;
  KleurLijnBerekening ber;
  SensorDataBuffer* datasink;
 // const int bufferSize = 5;  // Size of the buffer to store sensor readings
  //SimpleVector<unsigned int> lijnsensordataBuffer[5];  // Buffer to store sensor readings

public:
  unsigned int lsData[5];

  Lijnsensor(SensorDataBuffer* datasinkPointer, StatusControl* sc);

  /*! destructor */
  ~Lijnsensor();

  /*! this method handles the calibration of the values found bu the line sensor */
  void vindWaardes();
  void stuurNaarMotor();
  void sendToBuffer();
};

#endif