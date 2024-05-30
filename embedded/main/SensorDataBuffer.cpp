#include "SensorDataBuffer.h"
#include <SimpleVector.h>
#include <Wire.h>

using namespace std;

SensorDataBuffer::SensorDataBuffer():  
  imuSensorData(),
  imuNieuweDataIndex(0),
  lijnSensorData(),
  lijnNieuweDataIndex(0),
  proxSensorData(),
  proxNieuweDataIndex(0)
{ };

const void SensorDataBuffer::stuurData() {
  for(size_t i = imuNieuweDataIndex; i < imuSensorData.size(); ++i) { // iterereer door de vector, beginnend bij de eerste index nog niet gestuurd is
    char report[120];
    snprintf_P(report, sizeof(report),
               PSTR("Accel: %6d %6d %6d    Mag: %6d %6d %6d    Gyro: %6d %6d %6d"),
               imuSensorData[i].acc.x, imuSensorData[i].acc.y, imuSensorData[i].acc.z,
               imuSensorData[i].mag.x, imuSensorData[i].mag.y, imuSensorData[i].mag.z,
               imuSensorData[i].gyro.x, imuSensorData[i].gyro.y, imuSensorData[i].gyro.z);
    Serial.println(report);
  }
  imuNieuweDataIndex = imuSensorData.size(); // de cursor wordt verplaatst naar de het einde van de vector, aangezien alles nu gestuurd is

  for(size_t i = lijnNieuweDataIndex; i < lijnSensorData.size(); ++i) {
    char report[120];
    snprintf_P(report, sizeof(report),
               PSTR("Sensor1: %6d    Sensor2: %6d    Sensor3: %6d"),
               lijnSensorData[i].sensor1, lijnSensorData[i].sensor2, lijnSensorData[i].sensor3);
    Serial.println(report);
  }
  lijnNieuweDataIndex = lijnSensorData.size();

  for(size_t i = proxNieuweDataIndex; i < proxSensorData.size(); ++i) {
    char report[120];
    snprintf_P(report, sizeof(report),
               PSTR("ProxSensor: %6d"),
               proxSensorData[i]);
    Serial.println(report);
  }
  proxNieuweDataIndex = proxSensorData.size();
};

void SensorDataBuffer::bufferDataIMU(const IMUSensorData &data) {
  imuSensorData.push_back(data);
};

void SensorDataBuffer::bufferDataLijn(const LijnSensorData &data) {
  lijnSensorData.push_back(data);
};

void SensorDataBuffer::bufferDataProx(const int data) {
  proxSensorData.push_back(data);
};
