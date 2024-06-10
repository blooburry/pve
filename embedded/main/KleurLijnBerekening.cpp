#include "KleurLijnBerekening.h"

using Kleur = KleurLijnBerekening::Kleur;

KleurLijnBerekening::KleurLijnBerekening() {
  kleurstatus = 0;
}

KleurLijnBerekening::~KleurLijnBerekening() {
}

Kleur KleurLijnBerekening::vindLijnKleurStatus(unsigned int lsData[4]) {
  bool isWhite = false;
  static int tijd = 0;

  if ((int)(millis() - tijd) >= 500) { // elke halve seconde
    tijd = millis();
    for (int i = 0; i < 5; i++) {
      if ((lsData[0] < thWit) && (lsData[1] < thWit) && (lsData[2] < thWit) && (lsData[3] < thWit) && (lsData[4]< thWit)) {
        Serial1.println("wit");
        kleurstatus = Kleur::WIT;
        return kleurstatus;
      }
    }
  }

  //Serial1.println("voor de kleurberekening");
  if (
    (tussen(thBruinMin, thBruinMax, lsData[0])) 
    && (tussen(thBruinMin, thBruinMax, lsData[1])) 
    && (tussen(thBruinMin, thBruinMax, lsData[2])) 
    && (tussen(thBruinMin, thBruinMax, lsData[3])) 
    && (tussen(thBruinMin, thBruinMax, lsData[4])) 
  ) {
    kleurstatus = Kleur::BRUIN;
    Serial1.println("bruin");
    delay(2000);
    return kleurstatus;
  }

  if (
    tussen(thGrijsMin, thGrijsMax, lsData[0])
    && (!tussen(thGrijsMin, thGrijsMax, lsData[4]))
  ) {
    kleurstatus = Kleur::GRIJS_LINKS;
    Serial1.println("grijslinks");
    return kleurstatus;
  } 
  else if (
    tussen(thGrijsMin, thGrijsMax, lsData[4])  
    && (!tussen(thGrijsMin, thGrijsMax, lsData[0]))
  ) {
    kleurstatus = Kleur::GRIJS_RECHTS;
    Serial1.println("grijsrechts");
    return kleurstatus;
  } else if ( 
    tussen(thGrijsMin, thGrijsMax, lsData[0])
    && tussen(thGrijsMin, thGrijsMax, lsData[4])
  ) {
    kleurstatus = Kleur::GRIJS_STOP;
    Serial1.println("grijsstoppen");
    return kleurstatus;
  }

  if ( 
    tussen(thGroenMin, thGroenMax, lsData[1])
    || tussen(thGroenMin, thGroenMax, lsData[2]) 
    || tussen(thGroenMin, thGroenMax, lsData[3])
  ) {
    kleurstatus = Kleur::GROEN;
    Serial1.println("groen");
    return kleurstatus;
  }

  if (
    tussen(thZwart, 1000, lsData[1])
    || tussen(thZwart, 1000, lsData[2]) 
    || tussen(thZwart, 1000, lsData[3])
  ) {
    kleurstatus = Kleur::ZWART;
    Serial1.println("zwart");
    return kleurstatus;
  }
}

Kleur KleurLijnBerekening::stuurStatus() {
  return kleurstatus;
}

bool KleurLijnBerekening::tussen(unsigned int min, unsigned int max, unsigned int v) {
  return (v >= min) && (v <= max);
}
