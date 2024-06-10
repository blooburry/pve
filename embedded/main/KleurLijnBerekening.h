#ifndef KLEURLIJNBEREKENING_H
#define KLEURLIJNBEREKENING_H
//#include <Zumo32U4.h>
#include <Zumo32U4.h>
#include <SimpleVector.h>

class KleurLijnBerekening {
public:
  enum Kleur {
    ZWART, WIT, GROEN, GRIJS_LINKS, GRIJS_RECHTS, GRIJS_STOP, BRUIN
  };
  KleurLijnBerekening();
  ~KleurLijnBerekening();
  Kleur vindLijnKleurStatus(unsigned int lsData[4]);
  Kleur stuurStatus();
  Kleur kleurZeker = Kleur::ZWART; // kleurwaarde die de laatste 5 gemeten waardes in rekening neemt en alleen verandert als die allemaal overeenkomen

private:
  bool tussen(unsigned int, unsigned int, unsigned int);
  unsigned int thZwart = 700;
  unsigned int thWit = 40;
  unsigned int thGroenMin = 41;
  unsigned int thGroenMax = 299;
  unsigned int thGrijsMin = 300;
  unsigned int thGrijsMax = 399;
  unsigned int thBruinMin = 400;
  unsigned int thBruinMax = 699;
  Kleur kleurstatus;

  // Hij houdt de laatste 5 waardes ook bij, als die hetzelfde zijn dan weet hij zeker wat de kleur is
  SimpleVector<Kleur> geschiedenis;
  int laatsteIndex; // laatste index van de geschiedenis waarnaar is geschreven
  void pushGeschiedenis(Kleur); // voegt iets toe aan de geschiedenis en schuift de laatsteIndex op
};
#endif