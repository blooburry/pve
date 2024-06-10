#include "kleurLijnBerekening.h"


kleurlijnberekening::kleurlijnberekening() {
}

kleurlijnberekening::~kleurlijnberekening() {
}

/*void kleurlijnberekening::printkk(unsigned int LSdata[5]) {
  Serial1.println("LSdata: ");
  static char ruimte[50];
  sprintf(ruimte, "%4d %4d %4d %4d %4d \n",
          LSdata[0],
          LSdata[1],
          LSdata[2],
          LSdata[3],
          LSdata[4]);
  Serial1.print(ruimte);
}*/

kleurlijnberekening::Kleur kleurlijnberekening::vindLijnKleurStatus(unsigned int LSdata[5]) {
  bool isWhite = false;
  static int tijd = 0;

  if ((int)(millis() - tijd) >= 500) { // elke halve seconde
    tijd = millis();
    for (int i = 0; i < 5; i++) {
      if ((LSdata[0] < thWit) && (LSdata[1] < thWit) && (LSdata[2] < thWit) && (LSdata[3] < thWit) && (LSdata[4]< thWit)) {
        Serial1.println("wit");
        kleurstatus = Kleur::WIT;
        return kleurstatus;
      }
    }
  }

  //Serial1.println("voor de kleurberekening");
  if (
    (tussen(thBruinMin, thBruinMax, LSdata[0])) 
    && (tussen(thBruinMin, thBruinMax, LSdata[1])) 
    && (tussen(thBruinMin, thBruinMax, LSdata[2])) 
    && (tussen(thBruinMin, thBruinMax, LSdata[3])) 
    && (tussen(thBruinMin, thBruinMax, LSdata[4])) 
  ) {
    kleurstatus = Kleur::BRUIN;
    Serial1.println("bruin");
    delay(2000);
    return kleurstatus;
  }

  if (
    tussen(thGrijsMin, thGrijsMax, LSdata[0])
    && (!tussen(thGrijsMin, thGrijsMax, LSdata[4]))
  ) {
    kleurstatus = Kleur::GRIJS_LINKS;
    Serial1.println("grijslinks");
    return kleurstatus;
  } 
  else if (
    tussen(thGrijsMin, thGrijsMax, LSdata[4])  
    && (!tussen(thGrijsMin, thGrijsMax, LSdata[0]))
  ) {
    kleurstatus = Kleur::GRIJS_RECHTS;
    Serial1.println("grijsrechts");
    return kleurstatus;
  } else if ( 
    tussen(thGrijsMin, thGrijsMax, LSdata[0])
    && tussen(thGrijsMin, thGrijsMax, LSdata[4])
  ) {
    kleurstatus = Kleur::GRIJS_STOP;
    Serial1.println("grijsstoppen");
    return kleurstatus;
  }

  if ( 
    tussen(thGroenMin, thGroenMax, LSdata[1])
    || tussen(thGroenMin, thGroenMax, LSdata[2]) 
    || tussen(thGroenMin, thGroenMax, LSdata[3])
  ) {
    kleurstatus = Kleur::GROEN;
    Serial1.println("groen");
    return kleurstatus;
  }

  if (
    tussen(thZwart, 1000, LSdata[1])
    || tussen(thZwart, 1000, LSdata[2]) 
    || tussen(thZwart, 1000, LSdata[3])
  ) {
    kleurstatus = Kleur::ZWART;
    Serial1.println("zwart");
    return kleurstatus;
  }
}

int kleurlijnberekening::stuurStatus() {
  return kleurstatus;
}

bool kleurlijnberekening::tussen(unsigned int min, unsigned int max, unsigned int v) {
  return (v >= min) && (v <= max);
}
