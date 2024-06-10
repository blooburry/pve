#include <Wire.h>
#include <Zumo32U4.h>
#include "IMUSensor.h"
#include "ProxySensor.h"
#include "SensorDataBuffer.h"
#include "Xbee.h"
#include "KeyInterpreter.h"
#include "StatusControl.h"
#include "Motors.h"
#include "LijnSensor.h"

using Status = StatusControl::Status;

int i = 0;
Motors motors;
StatusControl sc(&motors);
SensorDataBuffer buffer;
IMUSensor imu(&buffer);
ProxySensor prox(&buffer, &sc);
LijnSensor* lijnPtr;

Xbee xb;
KeyInterpreter kp(&xb);

Zumo32U4ButtonA buttonA;

void setup()
{

    Wire.begin();

    while (!Serial)
    {
    } // block the thread until Serial is initialized

    i = 0;
    Serial.begin(9600); // baud rate
    
    Serial1.print(F("Press A"));
    buttonA.waitForButton();
}

void loop()
{

    if (i == 0)
    {
        Serial.println(F("======================================="));
        Serial.println(F("Program start!"));
        Serial.print(F("Battery voltage: "));
        Serial.println(readBatteryMillivolts());
      
        LijnSensor lijn(&buffer, &sc);
        lijnPtr = &lijn;
        lijnPtr->calibreer();
    }

    if(millis() % 10000 < 100){ // elke 10 seconden (ongeveer)
        Serial.print(F("t="));
        Serial.print(i);
        Serial.println(F("s"));

        // Stuur sensor data naar XBee
        imu.sendToBuffer();
        prox.zieObject();
        prox.sendToBuffer();
        lijnPtr->stuurNaarMotor();
        
        if(i % 10 == 0) { buffer.stuurData(); } // elke 10 seconden
    }

    i++;
}
