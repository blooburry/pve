#ifndef PROXYSENSOR_H
#define PROXYSENSOR_H

#include <stdint.h>
#include <Wire.h>
#include <Zumo32U4.h>

class ProxySensor : public Zumo32U4ProximitySensors  {
public:
    ProxySensor();
    ~ProxySensor();
    void setup();
    void ReadSensor();
    bool ZieObject();
    void printReadingsToSerial();
private:
    const uint8_t sensorThreshold = 5;
    uint8_t leftValue;
    uint8_t rightValue;
    bool proxFrontActive;
    unsigned int Readings[2] = {0, 0};
};

#endif