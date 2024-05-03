#ifndef SERIALPRINTER_H
#define SERIALPRINTER_H

#include <stdint.h>

class SerialPrinter
{   
public:
    SerialPrinter();
    ~SerialPrinter();
    void printje(uint16_t* lijnSensorWaardes);
};

#endif
