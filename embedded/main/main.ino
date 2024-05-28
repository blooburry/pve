#include <Wire.h>
#include <Zumo32U4.h>
#include "IMUSensor.h"
#include "SensorDataBuffer.h"

int i = 0;
SensorDataBuffer buffer;
IMUSensor imu(&buffer);

void setup()
{

    Wire.begin();

    while (!Serial)
    {
    } // block the thread until Serial is initialized

    i = 0;
    Serial.begin(9600); // baud rate
}

void loop()
{

    if (i == 0)
    {
        Serial.println(F("======================================="));
        Serial.println(F("Program start!"));
    }

    Serial.print(F("t="));
    Serial.print(i);
    Serial.println(F("s"));

    imu.sendToBuffer();

    if(i % 10 == 0) { buffer.stuurData(); } // elke 10 seconden

    delay(1000);
    i++;
}