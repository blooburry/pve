#include "SensorDataBuffer.h"
#include <Zumo32U4.h>

using Vec3D = Zumo32U4IMU::vector<int>; // de `vector` library struct 
using namespace std;

#ifndef IMUSENSOR_H
#define IMUSENSOR_H


class IMUSensor {
  public:
    /*! 
    constructor waarin gekeken wordt of de IMU geïnitialiseerd is. 
    Als dit niet zo is dan geeft de zumo een foutmelding, 
    anders dan worden de IMU sensoren aangezet met de default config 
    */
    IMUSensor(SensorDataBuffer* datasinkPointer);

    /* deze methodes lezen de verschillende sensoren */
    /*! deze methode leest de gyrosensor */
    const Vec3D leesGyro();
    /*! deze methode leest de magnetometer */
    const Vec3D leesMag();
    /*! deze methode leest de accelerometer */
    const Vec3D leesAcc();
    /*! stuur de data naar de SensorDataBuffer */
    void sendToBuffer(); 

  private:
    /*! een instance van de library klasse */
    Zumo32U4IMU imu; 
    /*! datasink voor alle Sensordata, stuur deze naar de XBee */
    SensorDataBuffer* datasink; 
};

#endif