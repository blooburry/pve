#include <SimpleVector.h>
#include <Zumo32U4.h>

using namespace std;
using Vec3D = Zumo32U4IMU::vector<int>; // de `vector` library struct 

#ifndef SENSORDATABUFFER_H
#define SENSORDATABUFFER_H

//! Slaat een geschiedenis op van de data van alle sensoren, en stuurt deze periodiek om naar de XBee
class SensorDataBuffer {  
public:
  /*! struct met de IMU data */
  struct IMUSensorData {
    Vec3D mag;
    Vec3D gyro;
    Vec3D acc;
  };
   
  /*! struct met de data van de vijf lijnsensoren */
  struct LijnSensorData {
    int sensor1;
    int sensor2;
    int sensor3;
    int sensor4;
    int sensor5;
  };

  /*! struct met de data van de ProximitySensor */
  struct ProxSensorData {
    int left;
    int right;
  };
  /*! constructor die alle data pakt */
  SensorDataBuffer();
  /*! methode die de IMUdata aan de IMU vector toevoegd */
  void bufferDataIMU(const IMUSensorData& data);
  /*! methode die ProximitySensor data aan de Proximity vector toevoegd */
  void bufferDataProx(const ProxSensorData& data);
  /*! methode die lijnsensordata aan de lijnsensor vector toevoegd */
  void bufferDataLijn(const LijnSensorData& data);
  /*! deze methode formatteert en de data en stuurt deze naar de xbee */
  const void stuurData();

private:
  SimpleVector<IMUSensorData> imuSensorData; //!< vector van IMU data
  SimpleVector<LijnSensorData> lijnSensorData; //!< vector van lijnsensordata
  SimpleVector<ProxSensorData> proxSensorData; //!< vector met proximity sensor data
};

#endif