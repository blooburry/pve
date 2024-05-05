#ifndef SERIALPRINTER_H
#define SERIALPRINTER_H

#include <stdint.h>


/* 
this class is used to print the calibrated values into an array
*/
class SerialPrinter
{   
public:
    SerialPrinter(); // constructor
    ~SerialPrinter(); // destructor
    void printje(uint16_t* lijnSensorWaardes); // the print function takes a pointer to the array that was initialised in 'lijnsensor.ino' as an argument.
};

#endif
