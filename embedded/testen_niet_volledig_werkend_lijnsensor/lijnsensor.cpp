#include "lijnsensor.h"
#include <Arduino.h>
#include <Zumo32U4.h>

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
    for (int i = 0; i < 3; i++) {
      LSdata[i] = lijnsensordata[i];
    }
    readCalibrated(LSdata);
    static char ruimte[50];
    sprintf(ruimte, "%4d %4d %4d 4%d $4d \n",
            LSdata[2],
            LSdata[1],
            LSdata[0],
            LSdata[3],
            LSdata[4]);
    Serial.print(ruimte);
  }
  int16_t position = readLine(LSdata);
  Serial.println(position);
  
}
