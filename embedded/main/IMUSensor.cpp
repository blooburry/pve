#include "IMUSensor.h"
#include "SensorDataBuffer.h"
#include <Zumo32U4.h>
#include <Wire.h>

using namespace std;

IMUSensor::IMUSensor(SensorDataBuffer* datasinkPointer): datasink(datasinkPointer) {
  Zumo32U4IMU imu;
  
  if (!imu.init()){
    // Failed to detect the inertial sensors.
    ledRed(1);
    while(1)
    {
      Serial.println(F("Failed to initialize IMU sensors."));
    }
  }

  imu.enableDefault();

  this->imu = imu;
}

const SensorDataBuffer::Point3D IMUSensor::leesAcc() {
  SensorDataBuffer::Point3D res = {imu.a.x, imu.a.y, imu.a.z};
  return res;
}

const SensorDataBuffer::Point3D IMUSensor::leesMag() {
  SensorDataBuffer::Point3D res = {imu.m.x, imu.m.y, imu.m.z};
  return res;
}

const SensorDataBuffer::Point3D IMUSensor::leesGyro() {
  SensorDataBuffer::Point3D res = {imu.g.x, imu.g.y, imu.g.z};
  return res;
}