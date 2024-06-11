#include "IMUSensor.h"
#include "SensorDataBuffer.h"
#include <Zumo32U4.h>
#include <Wire.h>

using Vec3D = Zumo32U4IMU::vector<int>;  // de `vector` library struct
using namespace std;

IMUSensor::IMUSensor(SensorDataBuffer* datasinkPointer)
  : datasink(datasinkPointer) {
  Zumo32U4IMU imu;
  /* check of de imu al is geïnitialiseerd */
  if (!imu.init()) {
    // niet geïnitialiseerd
    ledRed(1);
    while (1) {
      Serial.println(F("Failed to initialize IMU sensors."));
    }
  }
// wel geïnitialiseerd
  imu.enableDefault();

  this->imu = imu;
}

// lees de accelerometer en return een 3d vector met de waardes
const Vec3D IMUSensor::leesAcc() {
  imu.readAcc();
  Vec3D res = { imu.a.x, imu.a.y, imu.a.z };
  return res;
}
// lees de magnetometer en return een 3d vector met de waardes
const Vec3D IMUSensor::leesMag() {
  imu.readMag();
  Vec3D res = { imu.m.x, imu.m.y, imu.m.z };
  return res;
}
// lees de gyrosensor en return een 3d vector met de waardes
const Vec3D IMUSensor::leesGyro() {
  imu.readGyro();
  Vec3D res = { imu.g.x, imu.g.y, imu.g.z };
  return res;
}
// stuur de gevonden data naar de buffer
void IMUSensor::sendToBuffer() {
  SensorDataBuffer::IMUSensorData data = { leesAcc(), leesMag(), leesGyro() };
  datasink->bufferDataIMU(data);
}