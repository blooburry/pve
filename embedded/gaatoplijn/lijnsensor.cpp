#include "lijnsensor.h"
#include <Arduino.h>
#include <Zumo32U4.h>

using Kleur = kleurlijnberekening::Kleur;

int16_t compensatie = 0;
int16_t laatstecompensatie = 0;
int16_t integraal = 0;
int16_t afgeleide = 0;
int16_t output = 0;

const uint16_t max = 300;
const uint16_t maxGreenSpeed = 125;


lijnsensor::lijnsensor() {
  initFiveSensors();
}

lijnsensor::~lijnsensor() {
}

void lijnsensor::vindWaardes() { // calibratieproces
  Serial1.println("Aan het calibreren...");

  uint16_t i;
  for (i = 0; i < 120; i++) {
    //Serial.println(i);
    if (i > 30 && i <= 90) {
      motor.setSpeeds(-200, 200);
    } else {
      motor.setSpeeds(200, -200);
    }

    calibrate();
  }
  Serial.println(i);

  motor.setSpeeds(0, 0);

  Serial1.println("Calibreren klaar!");
}



void lijnsensor::stuurNaarMotor() {

  readCalibrated(LSdata);
  
  for (int i = 0; i < 3; i++) {
    LSkleur[i] = LSdata[i + 1];
  }

  static int tijd = 0;
  if ((int)(millis() - tijd) >= 500) {
    tijd = millis();

    Serial1.println("lijnsensor data: ");
    static char ruimte[50];
    sprintf(ruimte, "%4d %4d %4d %4d %4d \n",
            LSdata[0],
            LSdata[1],
            LSdata[2],
            LSdata[3],
            LSdata[4]);
    Serial1.print(ruimte);

    Serial1.println("Kleur data: ");
    static char ruimteKleur[50];
    sprintf(ruimte, "%4d %4d %4d \n",
            LSkleur[0],
            LSkleur[1],
            LSkleur[2]);
    Serial1.print(ruimteKleur);
  }

  int16_t position;
  
  Kleur k = ber.vindLijnKleurStatus(LSdata);
  position = readLine(LSdata); // check alleen de drie middelste sensors voor een lijn

  if (((k == Kleur::GROEN) || (k == Kleur::ZWART)) && (position != -1)) { 
    Serial1.println("Lijn gevonden op positie:");
    Serial1.println(position);
      
    // PID shit
    int16_t error = position - 2000;
    Serial1.println(error);
  /* if (ber.vindLijnKleurStatus(LSdata) == 3){
      compensatie = compensatie - 1000; 
    }*/

    // Bereken de integraal en afgeleide voor de PID-regelaar
    integraal = integraal + error;
    afgeleide = error - laatstecompensatie;

    // Bereken de uitvoer van de PID-regelaar
    output = (Cpro * error) + (Cint * integraal) + Cafg * afgeleide;

    // Pas de motorsnelheden aan op basis van de uitvoer
    int16_t linkssnelheid = (k == Kleur::GROEN) ? (maxGreenSpeed + output) : ((int16_t)max + output);
    int16_t rechtssnelheid = (k == Kleur::GROEN) ? (maxGreenSpeed - output) : ((int16_t)max - output);

    // Controleer of de lijnkleurstatus aangeeft dat er een zwarte of groene lijn is gedetecteerd
    /*if (ber.vindLijnKleurStatus(LSdata) == 2000) {
      motors.setSpeeds(150, 150);
    }*/

    // Stel de compensatie voor de laatste iteratie in
    laatstecompensatie = error;

    ber.vindLijnKleurStatus(LSdata);

    // Beperk de motorsnelheden binnen het toegestane bereik
    linkssnelheid = constrain(linkssnelheid, -100, (int16_t)max);
    rechtssnelheid = constrain(rechtssnelheid, -100, (int16_t)max);

    // Stuur de motors aan met de berekende snelheden
    motor.setSpeeds(linkssnelheid, rechtssnelheid);
  } else {
      Serial1.println("Geen lijn gevonden, gaat rechtdoor op groene snelheid");
       motor.setSpeeds(maxGreenSpeed, maxGreenSpeed);
  }
}

int lijnsensor::absolute(int v) {
  return v > 0 ? v : -v;
}

/**
  Zoekt de positie van een lijn, van 0 tot 4000. Als er geen lijn is, geeft hij -1.
*/
/*int lijnsensor::vindLijn(unsigned int* LSdata, Kleur k) {

  Serial1.println("Lijn zoeken op: ");
  Serial1.println(LSdata[1]);
  Serial1.println(LSdata[2]);
  Serial1.println(LSdata[3]);

  int som = 0;
  for (int i = 1; i <= 3; i++) {
    som += LSdata[i];
  }

  int constante = (k == Kleur::ZWART) ? zwarteLijnWaarde : groenLijnWaarde;

  if (som >= constante - 100){
    Serial1.println("Lijn op: ");

    int weighted1 = (LSdata[1] * 1000); 
    int weighted2 = (LSdata[2] * 2000); 
    int weighted3 = (LSdata[3] * 3000);

    Serial1.print("Weighted 1: ");
    Serial1.println(weighted1);
    Serial1.print("Weighted 2: ");
    Serial1.println(weighted2);
    Serial1.print("Weighted 3: ");
    Serial1.println(weighted3);

    int totalWeighted = weighted1 + weighted2 + weighted3;
    Serial1.print("Total weighted: ");
    Serial1.println(totalWeighted);

    int totalMeasured = (LSdata[1] + LSdata[2] + LSdata[3]);

    Serial1.print("Total measured: ");
    Serial1.println(totalMeasured);

    int res = totalWeighted / totalMeasured;

    Serial1.print("Res: ");
    Serial1.println(res);

    return res;
  }

  return -1;

} */

