#include "Calibraties.h"

Calibraties::Calibraties(Zumo32U4LineSensors& lijnsensor) : lijnsensor(lijnsensor) {}

Calibraties::~Calibraties() {}

void Calibraties::calibratiereken() {
    for (uint32_t i = 0; i < 500; i++) {
        lijnsensor.calibrate(); 
        if ((i % 100) == 0) {
        Serial.print(F("Bezig met calibreren"));
        }
        
    }
}
