#include <iostream>
#include "MqttService.h"
#include <Wire.h>
#include <Zumo32U4.h>
#include <ArduinoJson.h>

int setup()
{

    Wire.begin();

    if (!imu.init())
    {
        // Failed to detect the compass.
        ledRed(1);
        while (1)
        {
            Serial.println(F("Failed to initialize IMU sensors."));
            delay(100);
        }
    }

    imu.enableDefault();

    while (!Serial)
    {
    } // block the thread until Serial is initialized

    i = 0;
    Serial.begin(9600); // baud rate

    MqttService mqttService; // initialise the MQTT connection

    return 0;
}

void loop
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


    // Create JSON objects for sensor data
    StaticJsonDocument<100> magJson;
    StaticJsonDocument<100> accJson;
    StaticJsonDocument<100> gyroJson;

    // Fill JSON objects with sensor data
    magJson["x"] = imu.m.x;
    magJson["y"] = imu.m.y;
    magJson["z"] = imu.m.z;

    accJson["x"] = imu.a.x;
    accJson["y"] = imu.a.y;
    accJson["z"] = imu.a.z;

    gyroJson["x"] = imu.g.x;
    gyroJson["y"] = imu.g.y;
    gyroJson["z"] = imu.g.z;

    // Convert JSON objects to strings
    String magData;
    String accData;
    String gyroData;

    serializeJson(magJson, magData);
    serializeJson(accJson, accData);
    serializeJson(gyroJson, gyroData);

    // Send JSON data via MQTT
    mqttService.sendMagData(magData.c_str());
    mqttService.sendAccData(accData.c_str());
    mqttService.sendGyroData(gyroData.c_str());

    std::cout << "Data sent successfully\n";

    delay(1000);
    i++;
}