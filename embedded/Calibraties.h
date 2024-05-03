#ifndef CALIBRATIES_H
#define CALIBRATIES_H

#include <Zumo32U4.h>



class Calibraties
{
private:
    Zumo32U4LineSensors& lijnsensor;
public:
    Calibraties(Zumo32U4LineSensors& lijnsensor);
    ~Calibraties();
    void calibratiereken();
};

#endif