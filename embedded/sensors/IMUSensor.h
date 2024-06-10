#include "SensorDataBuffer.h"
#include <Zumo32U4.h>

using Vec3D = Zumo32U4IMU::vector<int>; // de `vector` library struct 
using namespace std;

#ifndef IMUSENSOR_H
#define IMUSENSOR_H

// Wrapper klasse voor de Zumo32U4IMU library klasse. Hij s
class IMUSensor {
  public:
    IMUSensor(SensorDataBuffer* datasinkPointer);

    const Vec3D leesGyro();
    const Vec3D leesMag();
    const Vec3D leesAcc();
    void sendToBuffer(); // stuur de data naar de SensorDataBuffer

  private:
    Zumo32U4IMU imu; // een instance van de library klasse
    SensorDataBuffer* datasink; // datasink voor alle Sensordata, stuur deze naar de XBee
};

#endif