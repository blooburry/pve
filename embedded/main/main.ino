#include <Wire.h>
#include <Zumo32U4.h>
#include "../sensors/IMUSensor.h"
#include "../sensors/ProxySensor.h"
#include "../sensors/SensorDataBuffer.h"
#include "../remote/Xbee.h"
#include "../remote/KeyInterpreter.h"
#include "../aansturing/StatusControl.h"
#include "../aansturing/Motors.h"

int i = 0;
SensorDataBuffer buffer;
IMUSensor imu(&buffer);
ProxySensor prox(&buffer);

Xbee xb;
KeyInterpreter kp(&xb);
Motors motors;
StatusControl sc(&motors);

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
    }

    sc.tick();

    if(millis() % 10000 < 100){ // elke 10 seconden (ongeveer)
        Serial.print(F("t="));
        Serial.print(i);
        Serial.println(F("s"));

        // Stuur sensor data naar XBee
        imu.sendToBuffer();
        prox.zieObject();
        prox.sendToBuffer();
        
        if(i % 10 == 0) { buffer.stuurData(); } // elke 10 seconden
    }

    i++;
}
