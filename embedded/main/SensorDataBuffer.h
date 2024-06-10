#include <SimpleVector.h>
#include <Zumo32U4.h>

using namespace std;
using Vec3D = Zumo32U4IMU::vector<int>; // de `vector` library struct 

#ifndef SENSORDATABUFFER_H
#define SENSORDATABUFFER_H

// Slaat een geschiedenis op van de data van alle sensoren, en stuurt deze periodiek om naar de XBee
class SensorDataBuffer {  // mock klasse voor testing
public:
  struct IMUSensorData {
    Vec3D mag;
    Vec3D gyro;
    Vec3D acc;
  };

  struct LijnSensorData {
    int sensor1;
    int sensor2;
    int sensor3;
    int sensor4;
    int sensor5;
  };

  struct ProxSensorData {
    int left;
    int right;
  };

  SensorDataBuffer();
  void bufferDataIMU(const IMUSensorData& data);
  void bufferDataProx(const ProxSensorData& data);
  void bufferDataLijn(const LijnSensorData& data);
  const void stuurData();

private:
  SimpleVector<IMUSensorData> imuSensorData;
  SimpleVector<LijnSensorData> lijnSensorData;
  SimpleVector<ProxSensorData> proxSensorData;
};

#endif