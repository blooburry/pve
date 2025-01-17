#include "HardwareSerial.h"
#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "ProxySensor.h"
#include "Motors.h"
#include "SensorDataBuffer.h"

ProxySensor::ProxySensor(SensorDataBuffer* datasinkPointer, StatusControl* sc):
  datasink(datasinkPointer),
  sc(sc)
{}

ProxySensor::~ProxySensor() {}

// A sensors reading must be greater than or equal to this
// threshold in order for the program to consider that sensor as
// seeing an object.
// In de ProxySensor.h file is al een waarde gegeven aan de threshold dus vandaar dat het uitgecomment is.
// const uint8_t sensorThreshold = 5;

// The maximum speed to drive the motors while turning.  400 is
// full speed.
const uint16_t turnSpeedMax = 350;

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


void ProxySensor::turnRight() {
  sc->proxSetSpeeds(turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void ProxySensor::turnLeft() {
  sc->proxSetSpeeds(-turnSpeed, turnSpeed);
  turningLeft = true;
  turningRight = false;
}

void ProxySensor::stop() {
  sc->proxSetSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}

void ProxySensor::setup() {
  initFrontSensor();
}

bool ProxySensor::zieObject() {
  read();
  uint8_t leftValue = countsFrontWithLeftLeds();
  uint8_t rightValue = countsFrontWithRightLeds();
  // Determine if an object is visible or not.
  bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;
  bool zekerweten = leftValue == rightValue;

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
    // An object is seen.
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
        sc->proxSetSpeeds(200, 200);
        delayMicroseconds(3000000);
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

void ProxySensor::sendToBuffer() {
  read();
  leftValue = countsFrontWithLeftLeds();
  rightValue = countsFrontWithRightLeds();
  readings[0] = leftValue;
  readings[1] = rightValue;

  SensorDataBuffer::ProxSensorData data = { readings[0], readings[1]};
  datasink->bufferDataProx(data);
}
