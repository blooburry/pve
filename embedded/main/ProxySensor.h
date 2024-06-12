#ifndef PROXYSENSOR_H
#define PROXYSENSOR_H

#include <stdint.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "SensorDataBuffer.h"
#include "StatusControl.h"

class ProxySensor : public Zumo32U4ProximitySensors {
public:
  /*! constructor met pointers naar Statuscontrol en Sensordatabuffer */
  ProxySensor(SensorDataBuffer* datasinkPointer, StatusControl* sc);
  /*! constructor met pointer naar Statuscontrol */
  ProxySensor(StatusControl* sc);
  /*! constructor */
  ProxySensor();
  /*! destructor */
  ~ProxySensor();
  /*! deze methode initialiseert de ProximityFrontsensor */
  void setup();
  /*! deze methode wordt gebruikt om een object te vinden en deze weg te duwen */
  bool zieObject();
  /*! stuur data naar de sensordatabuffer klasse */
  void sendToBuffer(); 

private:
  StatusControl* sc; //!< statuscontrol pointer die gebruikt wordt om de snelheden van de motoren aan te passen
  SensorDataBuffer* datasink; //!< Sensordatabuffer pointer voor het sturen van sensordata
  const uint8_t sensorThreshold = 5; //!< threshold voor het zien van een object
  uint8_t leftValue; //!< sensorwaarde van de frontsensor met de linker IR-led
  uint8_t rightValue; //!< sensorwaarde van de frontsensor met de rechter IR-led
  
  //bool proxFrontActive;  
  unsigned int readings[2] = { 0, 0 }; //!< array waarin de proximitywaardes worden opgeslagen
  /*! methode om naar links te draaien */
  void turnLeft();
  /*! methode om naar rechts te draaien */
  void turnRight();
  /*! methode om te stoppen */
  void stop();
};

#endif
