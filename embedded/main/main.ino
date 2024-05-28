#include <Wire.h>
#include <Zumo32U4.h>
#include "IMUSensor.h"
#include "SensorDataBuffer.h"

Zumo32U4IMU imu;
char report[120];
int i = 0;

void setup()
{

    Wire.begin();

    SensorDataBuffer buffer;

    IMUSensor imu(&buffer);

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

    imu.read();

    snprintf_P(report, sizeof(report),
               PSTR("Accel: %6d %6d %6d    Mag: %6d %6d %6d    Gyro: %6d %6d %6d"),
               imu.a.x, imu.a.y, imu.a.z,
               imu.m.x, imu.m.y, imu.m.z,
               imu.g.x, imu.g.y, imu.g.z);
    Serial.println(report);

    delay(1000);
    i++;
}