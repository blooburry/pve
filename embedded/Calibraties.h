#ifndef CALIBRATIES_H
#define CALIBRATIES_H

#include <Zumo32U4.h>


/*
this class handles the calibration of the line sensors 
*/
class Calibraties
{
private:
    Zumo32U4LineSensors& lijnsensor; // reference to the lijnsensor object
public:
    Calibraties(Zumo32U4LineSensors& lijnsensor); // constructor which takes a reference to the lijnsensor object as an argument
    ~Calibraties(); // destructor
    void calibratiereken(); // this method handles the calibration of the values found bu the line sensor
};

#endif
