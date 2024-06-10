#include "HardwareSerial.h"
#include <Arduino.h>
//#include <cstdio> // Voor sprintf
#include <stdint.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "ProxySensor.h"

ProxySensor::ProxySensor() {}
ProxySensor::~ProxySensor() {}

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;

// A sensors reading must be greater than or equal to this
// threshold in order for the program to consider that sensor as
// seeing an object.
//const uint8_t sensorThreshold = 6;

// The maximum speed to drive the motors while turning.  400 is
// full speed.
const uint16_t turnSpeedMax = 300;

// The minimum speed to drive the motors while turning.  400 is
// full speed.
const uint16_t turnSpeedMin = 150;

// The amount to decrease the motor speed by during each cycle
// when an object is seen.
const uint16_t deceleration = 10;

// The amount to increase the speed by during each cycle when an
// object is not seen.
const uint16_t acceleration = 10;

#define LEFT 0
#define RIGHT 1

// Stores the last indication from the sensors about what
// direction to turn to face the object.  When no object is seen,
// this variable helps us make a good guess about which direction
// to turn.
bool senseDir = RIGHT;

// True if the robot is turning left (counter-clockwise).
bool turningLeft = false;

// True if the robot is turning right (clockwise).
bool turningRight = false;

// If the robot is turning, this is the speed it will use.
uint16_t turnSpeed = turnSpeedMax;


void turnRight() {
  motors.setSpeeds(turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void turnLeft() {
  motors.setSpeeds(-turnSpeed, turnSpeed);
  turningLeft = true;
  turningRight = false;
}

void stop() {
  motors.setSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}

void ProxySensor::setup() {
  initFrontSensor();
  buttonA.waitForButton();
}

bool ProxySensor::ZieObject() {
  read();
  uint8_t leftValue = countsFrontWithLeftLeds();
  uint8_t rightValue = countsFrontWithRightLeds();
  // Determine if an object is visible or not.
  bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;
  bool zekerweten = leftValue == rightValue;
  // return zekerweten;

  if (objectSeen) {
    // An object is visible, so we will start decelerating in
    // order to help the robot find the object without
    // overshooting or oscillating.
    turnSpeed -= deceleration;
  } else {
    // An object is not visible, so we will accelerate in order
    // to help find the object sooner.
    turnSpeed += acceleration;
  }

  // Constrain the turn speed so it is between turnSpeedMin and
  // turnSpeedMax.
  turnSpeed = constrain(turnSpeed, turnSpeedMin, turnSpeedMax);

  if (objectSeen) {
    // An object seen.
    ledYellow(1);

    if (leftValue < rightValue) {
      // The right value is greater, so the object is probably
      // closer to the robot's right LEDs, which means the robot
      // is not facing it directly.  Turn to the right to try to
      // make it more even.
      turnRight();
      senseDir = RIGHT;
    } else if (leftValue > rightValue) {
      // The left value is greater, so turn to the left.
      turnLeft();
      senseDir = LEFT;
    } else if (zekerweten) {
      // The values are equal, so go straight to push object.
      bool zien = true;
      while (zien) {
        motors.setSpeeds(175, 175);
        delayMicroseconds(1000000);
        read();  // Update sensor readings
        leftValue = countsFrontWithLeftLeds();
        rightValue = countsFrontWithRightLeds();
        zekerweten = leftValue == rightValue;  // Update zekerweten
        if (!zekerweten) {
          zien = false;
        }
      }
    }
  } else {
    // No object is seen, so just keep turning in the direction
    // that we last sensed the object.
    ledYellow(0);

    if (senseDir == RIGHT) {
      turnRight();
    } else {
      turnLeft();
    }
  }
}

void ProxySensor::printReadingsToSerial() {
  read();
  leftValue = countsFrontWithLeftLeds();
  rightValue = countsFrontWithRightLeds();
  Readings[0] = leftValue;
  Readings[1] = rightValue;
  proxFrontActive = readBasicFront();
  // Prints a line with all the sensor readings to the serial
  // monitor.
  static char buffer[80];
  sprintf(buffer, "%d %d  %d\n",
          Readings[0],
          Readings[1],
          proxFrontActive);
  Serial.print(buffer);
}
