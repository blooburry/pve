#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;

// A sensors reading must be greater than or equal to this
// threshold in order for the program to consider that sensor as
// seeing an object.
const uint8_t sensorThreshold = 5;

#define LEFT 0
#define RIGHT 1

// True if the robot is turning left (counter-clockwise).
bool turningLeft = false;

// True if the robot is turning right (clockwise).
bool turningRight = false;

// If the robot is turning, this is the speed it will use. 400 is
// full speed.
uint16_t turnSpeed = 350;

// The time, in milliseconds, when an object was last seen.
uint16_t lastTimeObjectSeen = 0;

bool proxFrontActive;

void setup()
{
  proxSensors.initFrontSensor();

  // Wait for the user to press A before driving the motors.
  Serial.print(F("Press A"));
  buttonA.waitForButton();
}

void turnRight()
{
  motors.setSpeeds(turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void turnLeft()
{
  motors.setSpeeds(-turnSpeed, turnSpeed);
  turningLeft = true;
  turningRight = false;
}

void stop()
{
  motors.setSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}

// Prints a line with all the sensor readings to the serial
// monitor.
void printReadingsToSerial()
{
  static char buffer[80];
  sprintf(buffer, "%d %d  %d\n",
    proxSensors.countsFrontWithLeftLeds(),
    proxSensors.countsFrontWithRightLeds(),
    proxFrontActive
  );
  Serial.print(buffer);
}

void loop()
{
  // Read the front proximity sensor and gets its left value (the
  // amount of reflectance detected while using the left LEDs)
  // and right value.
  proxSensors.read();
  uint8_t leftValue = proxSensors.countsFrontWithLeftLeds();
  uint8_t rightValue = proxSensors.countsFrontWithRightLeds();

  // Determine if an object is visible or not.
  bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;


  if (objectSeen)
  {
    // An object is seen.
    ledYellow(1);

    lastTimeObjectSeen = millis();

    if (leftValue < rightValue)
    {
      // The right value is greater, so the object is probably
      // closer to the robot's right LEDs. Turn to the left to try to
      // avoid it
      turnLeft();
    }
    else if (leftValue > rightValue)
    {
      // The left value is greater, so turn to the right.
      turnRight();
    }
    else
    {
      // The values are equal, meaning the object is in the middle and
      // so it doesnt matter which way to turn to avoid the object. I made it turn right by default.
      turnRight();
    }
  }
  else
  {
    // No object is seen, so stop
    ledYellow(0);

    stop();
  }

  /*Serial.print(leftValue);
  Serial.print(' ');
  Serial.print(rightValue);
  Serial.print(turningRight ? 'R' : (turningLeft ? 'L' : ' '));
  Serial.print(' ');
  Serial.print(turnSpeed);
  Serial.print(' ');
  Serial.print(' ');
  */
  proxFrontActive = proxSensors.readBasicFront();
  printReadingsToSerial();
}
