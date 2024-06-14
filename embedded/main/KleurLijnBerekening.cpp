#include "KleurLijnBerekening.h"

using Kleur = KleurLijnBerekening::Kleur;

KleurLijnBerekening::KleurLijnBerekening() {
}

KleurLijnBerekening::~KleurLijnBerekening() {
}

Kleur KleurLijnBerekening::vindLijnKleurStatus(unsigned int lsData[4]) {

  if ((lsData[0] < thWit) && (lsData[1] < thWit) && (lsData[2] < thWit) && (lsData[3] < thWit) && (lsData[4]< thWit)) { // wit gevonden
    kleurstatus = Kleur::WIT;
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  }    

  if (
    (tussen(thBruinMin, thBruinMax, lsData[0])) 
    && (tussen(thBruinMin, thBruinMax, lsData[1])) 
    && (tussen(thBruinMin, thBruinMax, lsData[2])) 
    && (tussen(thBruinMin, thBruinMax, lsData[3])) 
    && (tussen(thBruinMin, thBruinMax, lsData[4])) 
  ) { // bruin gevonden
    kleurstatus = Kleur::BRUIN;
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  }

  if (
    tussen(thGrijsMin, thGrijsMax, lsData[0])
    && (!tussen(thGrijsMin, thGrijsMax, lsData[4]))
  ) { // grijs op links gevonden
    kleurstatus = Kleur::GRIJS_LINKS;
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  } 
  else if ( // grijs op rechts gevonden
    tussen(thGrijsMin, thGrijsMax, lsData[4])  
    && (!tussen(thGrijsMin, thGrijsMax, lsData[0]))
  ) { // grijs op rechts gevonden
    kleurstatus = Kleur::GRIJS_RECHTS;
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  } else if ( // grijs aan beide kanten gevonden
    tussen(thGrijsMin, thGrijsMax, lsData[0])
    && tussen(thGrijsMin, thGrijsMax, lsData[4])
  ) {
    kleurstatus = Kleur::GRIJS_STOP;
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  }

  if ( 
    tussen(thGroenMin, thGroenMax, lsData[1])
    || tussen(thGroenMin, thGroenMax, lsData[2]) 
    || tussen(thGroenMin, thGroenMax, lsData[3])
  ) { // groen gevonden
    kleurstatus = Kleur::GROEN;
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  }

  if (
    tussen(thZwart, 1500, lsData[1])
    || tussen(thZwart, 1500, lsData[2]) 
    || tussen(thZwart, 1500, lsData[3])
  ) { // zwart gevonden
    kleurstatus = Kleur::ZWART;
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  }
}

Kleur KleurLijnBerekening::stuurStatus() {
  return kleurstatus;
}

/* returnt true als de waarde die gevonden is door de sensor tussen de thresholds zit */
bool KleurLijnBerekening::tussen(unsigned int min, unsigned int max, unsigned int v) {
  return (v >= min) && (v <= max);
}


void KleurLijnBerekening::pushGeschiedenis(Kleur value) {
  geschiedenis[laatsteIndex] = value; // pak de waarde
  laatsteIndex = (laatsteIndex + 1) % 5; // houdt laatsteIndex in de array

  bool allEqual = true;
  for (size_t i = 1; i < 5; ++i) {
    if (geschiedenis[i] != geschiedenis[0]) { // check of de waardes gelijk zijn
      allEqual = false;
      break;
    }
  }

  if (allEqual) { // zet de basiswaarde van een kleur gelijk aan de eerste waarde uit de array
    kleurZeker = geschiedenis[0];
  }
}
