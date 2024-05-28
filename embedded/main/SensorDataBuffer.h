#include <Vector.h>

using namespace std;

#ifndef SENSORDATABUFFER_H
#define SENSORDATABUFFER_H

// Slaat een geschiedenis op van de data van alle sensoren, en stuurt deze periodiek om naar de XBee
class SensorDataBuffer {  // mock klasse voor testing
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

  struct LineSensorData {
    int sensor1;
    int sensor2;
    int sensor3;
  };
  void bufferDataIMU(const IMUSensorData& data);
  SensorDataBuffer();

private:
  Vector<IMUSensorData> imuSensordata;
  Vector<LineSensorData> lineSensorData;
  Vector<int> proxSensorData;
  const void stuurData();
};

#endif