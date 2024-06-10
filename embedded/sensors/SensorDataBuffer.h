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
  };

  struct ProxSensorData {
    int left;
    int right;
  }

  SensorDataBuffer();
  void bufferDataIMU(const IMUSensorData& data);
  void bufferDataProx(const ProxSensorData& data);
  void bufferDataLijn(const LijnSensorData& data);
  const void stuurData();

private:
  SimpleVector<IMUSensorData> imuSensorData;
  int imuNieuweDataIndex; // deze int houdt bij wat de index was van de eerste rij sensorData die nog niet doorgestuurd is naar de XBee
  SimpleVector<LijnSensorData> lijnSensorData;
  int lijnNieuweDataIndex;
  SimpleVector<ProxSensorData> proxSensorData;
  int proxNieuweDataIndex;
};

#endif