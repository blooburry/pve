#include "KleurLijnBerekening.h"

using Kleur = KleurLijnBerekening::Kleur;

KleurLijnBerekening::KleurLijnBerekening() {
}

KleurLijnBerekening::~KleurLijnBerekening() {
}

Kleur KleurLijnBerekening::vindLijnKleurStatus(unsigned int lsData[4]) {

  if ((lsData[0] < thWit) && (lsData[1] < thWit) && (lsData[2] < thWit) && (lsData[3] < thWit) && (lsData[4]< thWit)) { // wit gevonden
    //Serial1.println("wit");
    kleurstatus = Kleur::WIT;
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  }    

  //Serial1.println("voor de kleurberekening");
  if (
    (tussen(thBruinMin, thBruinMax, lsData[0])) 
    && (tussen(thBruinMin, thBruinMax, lsData[1])) 
    && (tussen(thBruinMin, thBruinMax, lsData[2])) 
    && (tussen(thBruinMin, thBruinMax, lsData[3])) 
    && (tussen(thBruinMin, thBruinMax, lsData[4])) 
  ) { // bruin gevonden
    kleurstatus = Kleur::BRUIN;
    //Serial1.println("bruin");
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  }

  if (
    tussen(thGrijsMin, thGrijsMax, lsData[0])
    && (!tussen(thGrijsMin, thGrijsMax, lsData[4]))
  ) { // grijs op links gevonden
    kleurstatus = Kleur::GRIJS_LINKS;
    // Serial1.println("grijslinks");
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  } 
  else if ( // grijs op rechts gevonden
    tussen(thGrijsMin, thGrijsMax, lsData[4])  
    && (!tussen(thGrijsMin, thGrijsMax, lsData[0]))
  ) { // grijs op rechts gevonden
    kleurstatus = Kleur::GRIJS_RECHTS;
    // Serial1.println("grijsrechts");
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  } else if ( // grijs aan beide kanten gevonden
    tussen(thGrijsMin, thGrijsMax, lsData[0])
    && tussen(thGrijsMin, thGrijsMax, lsData[4])
  ) {
    kleurstatus = Kleur::GRIJS_STOP;
    // Serial1.println("grijsstoppen");
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  }

  if ( 
    tussen(thGroenMin, thGroenMax, lsData[1])
    || tussen(thGroenMin, thGroenMax, lsData[2]) 
    || tussen(thGroenMin, thGroenMax, lsData[3])
  ) { // groen gevonden
    kleurstatus = Kleur::GROEN;
   // Serial1.println("groen");
    pushGeschiedenis(kleurstatus);
    return kleurstatus;
  }

  if (
    tussen(thZwart, 1500, lsData[1])
    || tussen(thZwart, 1500, lsData[2]) 
    || tussen(thZwart, 1500, lsData[3])
  ) { // zwart gevonden
    kleurstatus = Kleur::ZWART;
    //Serial1.println("zwart");
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
