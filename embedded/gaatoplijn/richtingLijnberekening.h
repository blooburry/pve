/*#ifndef RICHTINGLIJNBEREKENING_H
#define RICHTINGLIJNBEREKENING_H

#include "lijnsensor.h"
//#include <string>

class richtinglijnberekening : public Zumo32U4LineSensors{
    private: 
    Zumo32U4Motors motors;
    String richting;
    lijnsensor *lijn;
    int lijnTH = 10;

    public:

    richtinglijnberekening();
    ~richtinglijnberekening();
    void berekenrichting();
    void stuurNaarMotor(String){}
};
#endif*/