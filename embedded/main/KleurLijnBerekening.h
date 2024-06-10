#ifndef KLEURLIJNBEREKENING_H
#define KLEURLIJNBEREKENING_H
//#include <Zumo32U4.h>
#include <Zumo32U4.h>


class KleurLijnBerekening {
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

public:
  void printkk(unsigned int lsData[4]);
  KleurLijnBerekening();
  ~KleurLijnBerekening();
  int vindLijnKleurStatus(unsigned int lsData[4]);
  int stuurStatus();
};
#endif