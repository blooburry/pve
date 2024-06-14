#ifndef LijnSensor_H
#define LijnSensor_H

#include "StatusControl.h"
#include <SimpleVector.h>
#include <Zumo32U4.h>
#include "SensorDataBuffer.h"

#include "KleurLijnBerekening.h"

using namespace std;
using Kleur = KleurLijnBerekening::Kleur;



class LijnSensor : public Zumo32U4LineSensors {
private:
  KleurLijnBerekening ber; //!< dit object wordt gebruikt om de kleur van de lijn te bepalen
  StatusControl* sc; //!< pointer naar Statuscontrol
  SensorDataBuffer* datasink; //!< pointer naar SensorDataBuffer

  // alle PID variabelen
  const float Cpro = 0.7; //!< P van PID
  const float Cint = 0.0; //!< I van PID
  const float Cafg = 6.0; //!< D van PID
  const int dodeHoek = 100; //!< als de error van de PID minder is dan dodeHoek dan wordt het verwaarloost

  int16_t error = 0; //!< error voor PID
  int16_t laatstecompensatie = 0; //!< vorige error voor PID
  int16_t integraal = 0; //!< integraal voor PID
  int16_t afgeleide = 0; //!< afgeleide voor PID
  int16_t output = 0; //!< output is de uiteindelijke waarde die + of - de snelheid van de motors wordt gedaan afhankelijk van de motor
  
  // de snelheden van de motors
  const uint16_t MAX_SPEED = 320; //<! Maximale/zwarte snelheid
  const uint16_t MAX_SPEED_GROEN = 200; //<! Groene snelheid

public:
  unsigned int lsData[5]; //!< array die uitgelezen wordt om de lijn te vinden

  /*! constructor */
  LijnSensor(SensorDataBuffer* datasinkPointer, StatusControl* sc);

  /*! destructor */
  ~LijnSensor();

  /*! deze methode calibreert de lijnsensoren */
  void calibreer();
  /*! deze methode zoekt de lijn, op basis de positie en kleur van de lijn stuurt het een status naar StatusControl */
  void stuurNaarMotor();
  /*! stuurt data naar de Sensordatabuffer klasse */
  void sendToBuffer();
 // int absolute(int);

  /*! deze methode berekend de output waarde doormiddel van een PID */
  void pid(int error, Kleur k, int& links, int& rechts);
};

#endif
