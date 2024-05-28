#include "SensorDataBuffer.h"
#include <Vector.h>
#include <Wire.h>

using namespace std;

SensorDataBuffer::SensorDataBuffer() {
  imuSensordata;
  lineSensorData;
  proxSensorData;
};

const void SensorDataBuffer::stuurData() {
  for(IMUSensorData row : imuSensordata) {
    char report[120];
    snprintf_P(report, sizeof(report),
               PSTR("Accel: %6d %6d %6d    Mag: %6d %6d %6d    Gyro: %6d %6d %6d"),
               row.acc.x, row.acc.y, row.acc.z,
               row.mag.x, row.mag.y, row.mag.z,
               row.gyro.x, row.gyro.y, row.gyro.z);
    Serial.println(report);
  }
};

void SensorDataBuffer::bufferDataIMU(const IMUSensorData &data) {
  imuSensordata.push_back(data);
};

