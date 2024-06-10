#include "LijnSensor.h"
#include "SensorDataBuffer.h"
#include "KleurLijnBerekening.h"
#include "StatusControl.h"
#include <Arduino.h>
#include <Zumo32U4.h>

int16_t compensatie = 0;
int16_t laatstecompensatie = 0;
int16_t integraal = 0;
int16_t afgeleide = 0;
int16_t output = 0;

using Status = StatusControl::Status;

const uint16_t max = 300;
const uint16_t maxGreenSpeed = 300;


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
    //Serial.println(i);
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

  static char ruimte[50];
  sprintf(ruimte, "%4d %4d %4d %4d %4d \n",
          lsData[0],
          lsData[1],
          lsData[2],
          lsData[3],
          lsData[4]);
  Serial.print(ruimte);
  
  int16_t position = readLine(lsData);
  int16_t compensatie = position - 2000;
  Serial1.println(compensatie);
 /* if (ber.vindLijnKleurStatus(lsData) == 3){
    compensatie = compensatie - 1000; 
  }*/

  // Bereken de integraal en afgeleide voor de PID-regelaar
  integraal = integraal + compensatie;
  afgeleide = compensatie - laatstecompensatie;

  // Bereken de uitvoer van de PID-regelaar
  output = (Cpro * compensatie) + (Cint * integraal) + Cafg * afgeleide;

  // Pas de motorsnelheden aan op basis van de uitvoer
  int16_t linkssnelheid = (ber.vindLijnKleurStatus(lsData) == 3) ? (maxGreenSpeed + output) : ((int16_t)max + output);
  int16_t rechtssnelheid = (ber.vindLijnKleurStatus(lsData) == 3) ? (maxGreenSpeed - output) : ((int16_t)max - output);

  // Controleer of de lijnkleurstatus aangeeft dat er een zwarte of groene lijn is gedetecteerd
  /*if (ber.vindLijnKleurStatus(lsData) == 2000) {
    motors.setSpeeds(150, 150);
  }*/

  // Stel de compensatie voor de laatste iteratie in
  laatstecompensatie = compensatie;

  ber.vindLijnKleurStatus(lsData);

  // Beperk de motorsnelheden binnen het toegestane bereik
  linkssnelheid = constrain(linkssnelheid, -100, (int16_t)max);
  rechtssnelheid = constrain(rechtssnelheid, -100, (int16_t)max);

  // Stuur de motors aan met de berekende snelheden
  sc->lijnSetSpeeds(linkssnelheid, rechtssnelheid);
}

void LijnSensor::sendToBuffer() {
  readCalibrated(lsData);

  SensorDataBuffer::LijnSensorData data = { (int) lsData[0], (int) lsData[1], (int) lsData[2], (int) lsData[3], (int) lsData[4]};
  datasink->bufferDataLijn(data);
}