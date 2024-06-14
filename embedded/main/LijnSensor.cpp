#include "LijnSensor.h"
#include "SensorDataBuffer.h"
#include "KleurLijnBerekening.h"
#include "StatusControl.h"
#include <Arduino.h>
#include <Zumo32U4.h>

using Kleur = KleurLijnBerekening::Kleur;
using Status = StatusControl::Status;

LijnSensor::LijnSensor(SensorDataBuffer* datasink, StatusControl* sc)
  : ber(),
    sc(sc),
    datasink(datasink) {
  initFiveSensors();
}

LijnSensor::~LijnSensor() {
}

void LijnSensor::calibreer() {

  sc->setStatus(Status::CALIBREREN);

  uint16_t i;
  for (i = 0; i < 120; i++) {
    if (i > 30 && i <= 90) {
      sc->lijnSetSpeeds(-200, 200); // draaien zodat calibratie wit en zwart kan zien waardoor de waardes beter worden geset
    } else {
      sc->lijnSetSpeeds(200, -200);
    }

    calibrate();
  }

  sc->lijnSetSpeeds(0, 0);
  sc->setStatus(Status::VOLG_LIJN_ZWART);
}

void LijnSensor::stuurNaarMotor() {
  readCalibrated(lsData);

  Kleur k = ber.vindLijnKleurStatus(lsData); // vind de kleur van de lijn

  int position = 0;
  /*if (k == Kleur::ZWART) {
    position = readLine(lsData);   //readLineGroen(lsData);  //was eerste readLine(lsData);
  } else if (k == Kleur::GROEN) {  // hij is groen
    position = readLine(lsData);
  }*/
  position = readLine(lsData);


  if ((position == 0) || (position == 4000)) {  // geen lijn gevonden
    switch (ber.kleurZeker) { 
      case Kleur::WIT: // kleur is wit
        sc->setStatus(Status::ZOEK_LIJN);
        break;
      case Kleur::BRUIN: // kleur is bruin
        sc->setStatus(Status::DUW_BLOK);
        break;
    }
  } else {  // wel een lijn gevonden
    //Serial1.println(position);
    int16_t error = position - 2000;
    int linkssnelheid, rechtssnelheid;
    pid(error, Kleur::ZWART, linkssnelheid, rechtssnelheid);
    switch (ber.kleurZeker) {
      case Kleur::ZWART: // kleur is zwart
        sc->setStatus(Status::VOLG_LIJN_ZWART);
        sc->lijnSetSpeeds(linkssnelheid, rechtssnelheid);
        break;
      case Kleur::GROEN: // kleur is groen
        pid(error, Kleur::GROEN, linkssnelheid, rechtssnelheid);

        sc->setStatus(Status::VOLG_LIJN_GROEN);
        sc->lijnSetSpeeds(linkssnelheid, rechtssnelheid);
        break;

      case Kleur::BRUIN: //kleur is bruin
        sc->setStatus(Status::DUW_BLOK);
        break;
    }
  }
}


void LijnSensor::sendToBuffer() {
  readCalibrated(lsData);

  SensorDataBuffer::LijnSensorData data = { (int)lsData[0], (int)lsData[1], (int)lsData[2], (int)lsData[3], (int)lsData[4] };
  datasink->bufferDataLijn(data);
}

/*int LijnSensor::absolute(int v) {
  return v > 0 ? v : -v;
} */

void LijnSensor::pid(int error, Kleur k, int& linkssnelheid, int& rechtssnelheid) {

  // integraal = integraal + error;
  //afgeleide = error - laatstecompensatie;

  output = (Cpro * error) + (Cint * integraal) + Cafg * afgeleide; // Pid berekening

  // Pas de motorsnelheden aan op basis van de uitvoer
  linkssnelheid = (k == Kleur::GROEN) ? (MAX_SPEED_GROEN + output) : ((int16_t)MAX_SPEED + output); 
  rechtssnelheid = (k == Kleur::GROEN) ? (MAX_SPEED_GROEN - output) : ((int16_t)MAX_SPEED - output);

  // Stel de compensatie voor de laatste iteratie in
  laatstecompensatie = error;
  // Beperk de motorsnelheden binnen het toegestane bereik
  linkssnelheid = constrain(linkssnelheid, -400, (int16_t)MAX_SPEED);
  rechtssnelheid = constrain(rechtssnelheid, -400, (int16_t)MAX_SPEED);
}

