#ifndef KLEURLIJNBEREKENING_H
#define KLEURLIJNBEREKENING_H
//#include <Zumo32U4.h>
#include <Zumo32U4.h>


class KleurLijnBerekening {
public:
  enum Kleur {
    ZWART, WIT, GROEN, GRIJS_LINKS, GRIJS_RECHTS, GRIJS_STOP, BRUIN
  };
  KleurLijnBerekening();
  ~KleurLijnBerekening();
  Kleur vindLijnKleurStatus(unsigned int lsData[4]);
  Kleur stuurStatus();
  bool tussen(unsigned int, unsigned int, unsigned int);

private:
  unsigned int thZwart = 700;
  unsigned int thWit = 40;
  unsigned int thGroenMin = 41;
  unsigned int thGroenMax = 299;
  unsigned int thGrijsMin = 300;
  unsigned int thGrijsMax = 399;
  unsigned int thBruinMin = 400;
  unsigned int thBruinMax = 699;
  unsigned int kleurstatus = 0;

};
#endif