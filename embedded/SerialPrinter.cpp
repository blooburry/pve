#include "SerialPrinter.h"
#include <Arduino.h>

SerialPrinter::SerialPrinter(){}

SerialPrinter::~SerialPrinter(){}

void SerialPrinter::printje(uint16_t* lijnSensorWaardes){
    static char ruimte[50];
    sprintf(ruimte, "%4d %4d %4d\n",
    lijnSensorWaardes[0],
    lijnSensorWaardes[1],
    lijnSensorWaardes[2]);
    Serial.print(ruimte); 
}
