#ifndef LIJNSENSOR_H
#define LIJNSENSOR_H

#include <SimpleVector.h>
#include <Zumo32U4.h>

#include "kleurLijnBerekening.h"

using namespace std;
using Kleur = kleurlijnberekening::Kleur;


/*!
this class handles the calibration of the line sensors 
*/
class lijnsensor : public Zumo32U4LineSensors {
private:
  /*! reference to the lijnsensor object */
  Zumo32U4Motors motor;
  const float Cpro = 1.5;
  const float Cint = 0.0;
  const float Cafg = 6.0;
  const int dodeHoek = 100;

  // Verwachte waardes voor een zwarte en groene lijn
  const int zwarteLijnWaarde = 1500;
  const int groenLijnWaarde = 400;

  kleurlijnberekening ber;
  int16_t position;
 // const int bufferSize = 5;  // Size of the buffer to store sensor readings
  //SimpleVector<unsigned int> lijnsensordataBuffer[5];  // Buffer to store sensor readings
  Kleur k;
public:
  /*! constructor which takes a reference to the lijnsensor object as an argument */
  unsigned int LSdata[5];
  unsigned int LSkleur[3];


  lijnsensor();

  /*! destructor */
  ~lijnsensor();

  /*! this method handles the calibration of the values found bu the line sensor */
  void vindWaardes();
  void stuurNaarMotor();
  int vindLijn(unsigned int* LSdata, Kleur k);
  int absolute(int);
};

#endif