#include "SensorDataBuffer.h"
#include <Vector.h>

using namespace std;

SensorDataBuffer::SensorDataBuffer() {
  imuSensordata;
  lineSensorData;
  proxSensorData;
};

const void SensorDataBuffer::stuurData() {

};

void SensorDataBuffer::bufferDataIMU(const IMUSensorData &data) {};

