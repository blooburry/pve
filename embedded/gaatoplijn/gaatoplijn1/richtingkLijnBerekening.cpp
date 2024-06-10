#include "richtingLijnberekening.h"
#include <Zumo32U4.h>
#include "lijnsensor.h"




richtinglijnberekening::richtinglijnberekening() {}

richtinglijnberekening::~richtinglijnberekening() {}

void richtinglijnberekening::berekenrichting() {
  const uint16_t maxSpeed = 150;
  int16_t lastError = 0;

  unsigned int data[3];
  for (int i = 0; i < 3; i++) {
    data[i] = lijn->lijnsensordata[i];
  }
  int16_t position = readLine(data);
  Serial.println(position);
  static char ruimte[50];
  sprintf(ruimte, "%4d %4d %4d 4%d $4d \n",
          data[2],
          data[1],
          data[0],
          data[3],
          data[4]);
  Serial.print(ruimte);





  // Our "error" is how far we are away from the center of the
  // line, which corresponds to position 2000.
  int16_t error = position - 200;

  // Get motor speed difference using proportional and derivative
  // PID terms (the integral term is generally not very useful
  // for line following).  Here we are using a proportional
  // constant of 1/4 and a derivative constant of 6, which should
  // work decently for many Zumo motor choices.  You probably
  // want to use trial and error to tune these constants for your
  // particular Zumo and line course.
  int16_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error;

  // Get individual motor speeds.  The sign of speedDifference
  // determines if the robot turns left or right.
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  // Constrain our motor speeds to be between 0 and maxSpeed.
  // One motor will always be turning at maxSpeed, and the other
  // will be at maxSpeed-|speedDifference| if that is positive,
  // else it will be stationary.  For some applications, you
  // might want to allow the motor speed to go negative so that
  // it can spin in reverse.
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
  /*bool lijnGezien = true;
  String kleur = "";
  


  for (unsigned int n : lijn->lijnsensordata) {
    Serial1.println("forloop begin");
    if (n >= lijnTH) {
      lijnGezien = true;
      Serial1.println("lijngezien");
      break;
      

    }
    break;
  }

  if (!lijnGezien) {
    Serial1.println("geenlijn");
    richting = "geenlijn";
    motors.setSpeeds(-200, 200);

  } else {
    

      if (lijn->lijnsensordata[1] >= lijnTH) {
        Serial1.println("vooruiit");
        richting = "rechtdoor";
        motors.setSpeeds(100, 100);
      } else {
         if ((lijn ->lijnsensordata[0] >= lijnTH) && (lijn->lijnsensordata[2] < lijnTH)) {
          Serial1.println("vooruit");
          richting = "rechtdoor";
          motors.setSpeeds(100, 100);
        }
        else {
        if ((lijn->lijnsensordata[0] >= lijnTH) && (lijn->lijnsensordata[2] < lijnTH)) {
          Serial1.println("links");
          richting = "linksaf";
          motors.setSpeeds(100, -100);
        }

        if ((lijn->lijnsensordata[2] >= lijnTH) && (lijn->lijnsensordata[0] < lijnTH)) {
          Serial1.println("rechts");
          richting = "rechtsaf";
          motors.setSpeeds(-100, 100);

        }
        }
      }
      }*/
}
