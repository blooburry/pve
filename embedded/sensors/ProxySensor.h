#ifndef PROXYSENSOR_H
#define PROXYSENSOR_H

#include <stdint.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "SensorDataBuffer.h"
#include "../aansturing/StatusControl.h"

class ProxySensor : public Zumo32U4ProximitySensors  {
    public:
        ProxySensor(SensorDataBuffer* datasinkPointer, StatusControl* sc);
        ~ProxySensor();
        void setup();
        bool zieObject();
        void sendToBuffer(); // stuur de data naar de SensorDataBuffer
        
    private:
        const uint8_t sensorThreshold;
        uint8_t leftValue;
        uint8_t rightValue;
        bool proxFrontActive;
        unsigned int readings[2] = {0, 0};
        SensorDataBuffer* datasinkPointer;
        StatusControl* sc;
};

#endif