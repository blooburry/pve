#ifndef KLEURLIJNBEREKENING_H
#define KLEURLIJNBEREKENING_H

#include <Zumo32U4.h>
#include <SimpleVector.h>

class KleurLijnBerekening {
public:

  /*! de verschillende kleuren die gevonden kunnen worden */
  enum Kleur {
    ZWART, WIT, GROEN, GRIJS_LINKS, GRIJS_RECHTS, GRIJS_STOP, BRUIN
  };

  /*! constructor */
  KleurLijnBerekening();
  /* destructor */
  ~KleurLijnBerekening();
  /*! deze methode kijkt of de data due op de lijnsensors gevonden wordt tussen een Min- en Max waarde van een kleur zitten om zo de kleur van de lijn te vinden */
  Kleur vindLijnKleurStatus(unsigned int lsData[5]);

  /*! stuur de status naar de statuscontrol klasse */
  Kleur stuurStatus();
  Kleur kleurZeker = Kleur::ZWART; //!< kleurwaarde die de laatste 5 gemeten waardes in rekening neemt en alleen verandert als die allemaal overeenkomen

private:

  /*! methode die checkt of de gevonden lijnsensorwaardes tussen de thresholds liggen */
  bool tussen(unsigned int, unsigned int, unsigned int);

  /* alle thresholds van kleuren (0-1000) */
  unsigned int thZwart = 700; //!< threshold van zwart
  unsigned int thWit = 40; //!< threshold van wit
  unsigned int thGroenMin = 41; //!< minimum threshold van groen
  unsigned int thGroenMax = 100; //!< maximum threshold van groen
  unsigned int thGrijsMin = 151; //!< minimum threshold van grijs
  unsigned int thGrijsMax = 250; //!< maximum threshold van grijs
  unsigned int thBruinMin = 251; //!< minimum threshold van bruin
  unsigned int thBruinMax = 699; //!< maximum threshold van bruin
  Kleur kleurstatus; //!< object dat gebruikt wordt om de 

  
  SimpleVector<Kleur> geschiedenis; //!< de vector houdt de laatste 5 waardes ook bij, als die hetzelfde zijn dan weet hij zeker wat de kleur is
 
  int laatsteIndex;  //!< laatste index van de geschiedenis waarnaar is geschreven 
  //! voegt iets toe aan de geschiedenis en schuift de laatsteIndex op
  void pushGeschiedenis(Kleur); 
};
#endif