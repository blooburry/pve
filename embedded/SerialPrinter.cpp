#include "SerialPrinter.h"
#include <Arduino.h>

SerialPrinter::SerialPrinter(){}

SerialPrinter::~SerialPrinter(){}

/* 
this method prints the values found within the lijnSensorWaardes array
into a formatted string which is then shown on the serial monitor 
*/

void SerialPrinter::printje(uint16_t* lijnSensorWaardes){
    static char ruimte[50];
    sprintf(ruimte, "%4d %4d %4d\n",
    lijnSensorWaardes[0],
    lijnSensorWaardes[1],
    lijnSensorWaardes[2]);
    Serial.print(ruimte); 
}
