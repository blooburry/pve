#include "SensorDataBuffer.h"
#include <SimpleVector.h>
#include <Wire.h>

using namespace std;

SensorDataBuffer::SensorDataBuffer():  
  imuSensorData(),
  lijnSensorData(),
  proxSensorData()
{ };

const void SensorDataBuffer::stuurData() {
  for(size_t i = 0; i < imuSensorData.elements(); ++i) { // iterereer door de vector, beginnend bij de eerste index nog niet gestuurd is
    char report[120];
    snprintf_P(report, sizeof(report),
               PSTR("Accel: %6d %6d %6d    Mag: %6d %6d %6d    Gyro: %6d %6d %6d"),
               imuSensorData[i].acc.x, imuSensorData[i].acc.y, imuSensorData[i].acc.z,
               imuSensorData[i].mag.x, imuSensorData[i].mag.y, imuSensorData[i].mag.z,
               imuSensorData[i].gyro.x, imuSensorData[i].gyro.y, imuSensorData[i].gyro.z);
    Serial1.println(report);
  }

  imuSensorData.clear();

  for(size_t i = 0; i < lijnSensorData.elements(); ++i) {
    char report[120];
    snprintf_P(report, sizeof(report),
               PSTR("LineSensor1: %6d    LineSensor2: %6d    LineSensor3: %6d,     LineSensor4: %6d,     LineSensor5: %6d"),
               lijnSensorData[i].sensor1, lijnSensorData[i].sensor2, lijnSensorData[i].sensor3, lijnSensorData[i].sensor4, lijnSensorData[i].sensor5);
    Serial1.println(report);
  }

  lijnSensorData.clear();

  for(size_t i = 0; i < proxSensorData.elements(); ++i) {
    char report[120];
    snprintf_P(report, sizeof(report),
               PSTR("ProxSensorLeft: %6d    ProxSensorRight: %6d"),
               proxSensorData[i].left, proxSensorData[i].right);
    Serial1.println(report);
  }

  proxSensorData.clear();
};

void SensorDataBuffer::bufferDataIMU(const IMUSensorData &data) {
  imuSensorData.push_back(data);
};

void SensorDataBuffer::bufferDataLijn(const LijnSensorData &data) {
  lijnSensorData.push_back(data);
};

void SensorDataBuffer::bufferDataProx(const ProxSensorData &data) {
  proxSensorData.push_back(data);
};
