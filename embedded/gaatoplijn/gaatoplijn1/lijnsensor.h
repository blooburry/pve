#ifndef LIJNSENSOR_H
#define LIJNSENSOR_H

#include <SimpleVector.h>
#include <Zumo32U4.h>

#include "kleurLijnBerekening.h"

using namespace std;


/*!
this class handles the calibration of the line sensors 
*/
class lijnsensor : public Zumo32U4LineSensors {
private:
  /*! reference to the lijnsensor object */
  Zumo32U4Motors motors;
  const float Cpro = 0.7;
  const float Cint = 0.0;
  const float Cafg = 6.0;
  const int dodeHoek = 100;
  kleurlijnberekening ber;
 // const int bufferSize = 5;  // Size of the buffer to store sensor readings
  //SimpleVector<unsigned int> lijnsensordataBuffer[5];  // Buffer to store sensor readings


public:
  /*! constructor which takes a reference to the lijnsensor object as an argument */
  SimpleVector<unsigned int> lijnsensordata;
  unsigned int LSdata[5];


  lijnsensor();

  /*! destructor */
  ~lijnsensor();

  /*! this method handles the calibration of the values found bu the line sensor */
  void vindWaardes();
  void stuurNaarMotor();
};

#endif