#ifndef KLEURLIJNBEREKENING_H
#define KLEURLIJNBEREKENING_H
//#include <Zumo32U4.h>
#include <Arduino.h>
#include <Zumo32U4.h>

class kleurlijnberekening {
  public:
    enum Kleur {
      WIT, BRUIN, GROEN, ZWART, GRIJS_LINKS, GRIJS_RECHTS, GRIJS_STOP
    };

    //void printkk(unsigned int LSdata[5]);
    kleurlijnberekening();
    ~kleurlijnberekening();
    Kleur vindLijnKleurStatus(unsigned int LSdata[5]);
    int stuurStatus();
    bool tussen(unsigned int, unsigned int, unsigned int);


  private:
    unsigned int thZwart = 700;
    unsigned int thWit = 40;
    unsigned int thGroenMin = 41;
    unsigned int thGroenMax = 299;
    unsigned int thGrijsMin = 50;
    unsigned int thGrijsMax = 400;
    unsigned int thBruinMin = 500;
    unsigned int thBruinMax = 699;
    Kleur kleurstatus;

};
#endif