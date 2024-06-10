#include "lijnsensor.h"
#include <Arduino.h>
#include <Zumo32U4.h>

int16_t compensatie = 0;
int16_t laatstecompensatie = 0;
int16_t integraal = 0;
int16_t afgeleide = 0;
int16_t output = 0;


const uint16_t max = 300;
const uint16_t maxGreenSpeed = 300;


lijnsensor::lijnsensor() {
  initFiveSensors();
}

lijnsensor::~lijnsensor() {
}

void lijnsensor::vindWaardes() {
  uint16_t i;
  for (i = 0; i < 120; i++) {
    //Serial.println(i);
    if (i > 30 && i <= 90) {
      motors.setSpeeds(-200, 200);
    } else {
      motors.setSpeeds(200, -200);
    }

    calibrate();
  }
  Serial.println(i);

  motors.setSpeeds(0, 0);
}



void lijnsensor::stuurNaarMotor() {
  static int tijd = 0;
  if ((int)(millis() - tijd) >= 500) {
    tijd = millis();
    for (int i = 0; i < 5; i++) {
      LSdata[i] = lijnsensordata[i];
    }
    readCalibrated(LSdata);
    static char ruimte[50];
    sprintf(ruimte, "%4d %4d %4d %4d %4d \n",
            LSdata[0],
            LSdata[1],
            LSdata[2],
            LSdata[3],
            LSdata[4]);
    Serial.print(ruimte);
  }

  int16_t position = readLine(LSdata);
  int16_t compensatie = position - 2000;
  Serial1.println(compensatie);
 /* if (ber.vindLijnKleurStatus(LSdata) == 3){
    compensatie = compensatie - 1000; 
  }*/

  // Bereken de integraal en afgeleide voor de PID-regelaar
  integraal = integraal + compensatie;
  afgeleide = compensatie - laatstecompensatie;

  // Bereken de uitvoer van de PID-regelaar
  output = (Cpro * compensatie) + (Cint * integraal) + Cafg * afgeleide;

  // Pas de motorsnelheden aan op basis van de uitvoer
  int16_t linkssnelheid = (ber.vindLijnKleurStatus(LSdata) == 3) ? (maxGreenSpeed + output) : ((int16_t)max + output);
  int16_t rechtssnelheid = (ber.vindLijnKleurStatus(LSdata) == 3) ? (maxGreenSpeed - output) : ((int16_t)max - output);

  // Controleer of de lijnkleurstatus aangeeft dat er een zwarte of groene lijn is gedetecteerd
  /*if (ber.vindLijnKleurStatus(LSdata) == 2000) {
    motors.setSpeeds(150, 150);
  }*/

  // Stel de compensatie voor de laatste iteratie in
  laatstecompensatie = compensatie;

  ber.vindLijnKleurStatus(LSdata);

  // Beperk de motorsnelheden binnen het toegestane bereik
  linkssnelheid = constrain(linkssnelheid, -100, (int16_t)max);
  rechtssnelheid = constrain(rechtssnelheid, -100, (int16_t)max);

  // Stuur de motors aan met de berekende snelheden
  motors.setSpeeds(linkssnelheid, rechtssnelheid);
}
