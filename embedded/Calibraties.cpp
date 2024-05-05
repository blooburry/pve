#include "Calibraties.h"
/*
this constuctor takes a reference to the lijnsensor object as an argument so that it can be used in the calibratiereken method 
*/
Calibraties::Calibraties(Zumo32U4LineSensors& lijnsensor) : lijnsensor(lijnsensor) {} 

Calibraties::~Calibraties() {}

/* 
this method calibrates the line sensors for about 12.5 seconds and stores the calibrated values. 
every 2.5 seconds the message "bezig met calibreren" is shown on the serial monitor.
*/

void Calibraties::calibratiereken() {
    for (uint32_t i = 0; i < 500; i++) {
        lijnsensor.calibrate(); 
        if ((i % 100) == 0) {
        Serial.print(F("Bezig met calibreren"));
        }
        
    }
}
