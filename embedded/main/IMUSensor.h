#include "SensorDataBuffer.h"
#include <Zumo32U4.h>

using namespace std;

#ifndef IMUSENSOR_H
#define IMUSENSOR_H

// Wrapper klasse voor de Zumo32U4IMU library klasse. Hij s
class IMUSensor {
  public:
    struct Point3D {
    float x;
    float y;
    float z;
  };

  struct IMUSensorData {
    Point3D mag;
    Point3D gyro;
    Point3D acc;
  };

    IMUSensor(SensorDataBuffer* datasinkPointer);

    const SensorDataBuffer::Point3D leesGyro();
    const SensorDataBuffer::Point3D leesMag();
    const SensorDataBuffer::Point3D leesAcc();

  private:
    Zumo32U4IMU imu; // een instance van de library klasse
    SensorDataBuffer* datasink; // datasink voor alle Sensordata, stuur deze naar de XBee
};

#endif