#include "LijnSensor.h"
#include "SensorDataBuffer.h"
#include "KleurLijnBerekening.h"
#include "StatusControl.h"
#include <Arduino.h>
#include <Zumo32U4.h>

using Kleur = KleurLijnBerekening::Kleur;
using Status = StatusControl::Status;

LijnSensor::LijnSensor(SensorDataBuffer* datasink, StatusControl* sc):
  ber(),
  sc(sc),
  datasink(datasink)
{
  initFiveSensors();
}

LijnSensor::~LijnSensor() {
}

void LijnSensor::calibreer() {

  sc->setStatus(Status::CALIBREREN);

  uint16_t i;
  for (i = 0; i < 120; i++) {
    if (i > 30 && i <= 90) {
      sc->lijnSetSpeeds(-200, 200);
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

  Kleur k = ber.vindLijnKleurStatus(lsData);
  
  int position;
  if(k == Kleur::ZWART) {
    position = readLine(lsData);
  } else { // hij is groen
    position = readLineGroen(lsData);
  }

  if((position == 0) || (position == 4000)) { // geen lijn gevonden
    switch(k) {
      case Kleur::WIT :
        sc->setStatus(Status::ZOEK_LIJN);
        break;
      case Kleur::BRUIN :
        sc->setStatus(Status::DUW_BLOK);
        break;
    }
  } else { // wel een lijn gevonden

    int16_t error = position - 2000;
    int linkssnelheid, rechtssnelheid;
    pid(error, Kleur::ZWART, linkssnelheid, rechtssnelheid);
    switch(ber.kleurZeker) {
      case Kleur::ZWART :
        sc->setStatus(Status::VOLG_LIJN_ZWART);
        sc->lijnSetSpeeds(linkssnelheid, rechtssnelheid);
        break;
      case Kleur::GROEN :
        pid(error, Kleur::GROEN, linkssnelheid, rechtssnelheid);

        sc->setStatus(Status::VOLG_LIJN_GROEN);
        sc->lijnSetSpeeds(linkssnelheid, rechtssnelheid);
    }
  }
}

void LijnSensor::sendToBuffer() {
  readCalibrated(lsData);

  SensorDataBuffer::LijnSensorData data = { (int) lsData[0], (int) lsData[1], (int) lsData[2], (int) lsData[3], (int) lsData[4]};
  datasink->bufferDataLijn(data);
}

int LijnSensor::absolute(int v) {
  return v > 0 ? v : -v;
}

void LijnSensor::pid(int error, Kleur k, int& linkssnelheid, int& rechtssnelheid) {
  
  integraal = integraal + error;
  afgeleide = error - laatstecompensatie;

  output = (Cpro * error) + (Cint * integraal) + Cafg * afgeleide;

  // Pas de motorsnelheden aan op basis van de uitvoer
  linkssnelheid = (k == Kleur::GROEN) ? (MAX_SPEED_GROEN + output) : ((int16_t)MAX_SPEED + output);
  rechtssnelheid = (k == Kleur::GROEN) ? (MAX_SPEED_GROEN - output) : ((int16_t)MAX_SPEED - output);

  // Stel de compensatie voor de laatste iteratie in
  laatstecompensatie = error;
  // Beperk de motorsnelheden binnen het toegestane bereik
  linkssnelheid = constrain(linkssnelheid, -100, (int16_t) MAX_SPEED);
  rechtssnelheid = constrain(rechtssnelheid, -100, (int16_t) MAX_SPEED);
}

int LijnSensor::readLineGroen(unsigned int *sensor_values)
{
    unsigned char readMode = QTR_EMITTERS_ON;
    bool white_line = true;

    unsigned char i, on_line = 0;
    unsigned long avg; // this is for the weighted total, which is long
                       // before division
    unsigned int sum; // this is for the denominator which is <= 64000

    readCalibrated(sensor_values, readMode);

    avg = 0;
    sum = 0;

    for(i=0;i<_numSensors;i++) {
        int value = sensor_values[i];
        if(white_line)
            value = 1000-value;

        // keep track of whether we see the line at all
        if(value > 51) {
            on_line = 1;
        }

        // only average in values that are above a noise threshold
        if(value > 50) {
            avg += (long)(value) * (i * 1000);
            sum += value;
        }
    }

    if(!on_line)
    {
        // If it last read to the left of center, return 0.
        if(_lastValue < (_numSensors-1)*1000/2)
            return 0;

        // If it last read to the right of center, return the MAX_SPEED.
        else
            return (_numSensors-1)*1000;
    }

    _lastValue = avg/sum;

    return _lastValue;
}