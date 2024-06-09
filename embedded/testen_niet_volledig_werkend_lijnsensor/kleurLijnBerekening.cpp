#include "kleurLijnBerekening.h"

kleurlijnberekening::kleurlijnberekening() {
  kleurstatus = 0;
}

kleurlijnberekening::~kleurlijnberekening() {
}

/*void kleurlijnberekening::vindLijnKleurStatus( ) {
  if (!(lijn->lijnsensordata[0] && lijn->lijnsensordata[1] && lijn->lijnsensordata[2]) <= thWit) {
    for (int n : lijn->lijnsensordata) {
      if (lijn->lijnsensordata[n] >= thZwart) {
        kleurstatus = 1;
        Serial.println("zwart");
      } else if ((lijn->lijnsensordata[n] <= thBruinMax) && (lijn->lijnsensordata[n] >= thBruinMin)) {
        kleurstatus = 2;
        Serial.println("bruin");
      } else if ((lijn->lijnsensordata[n] <= thGroenMax) && (lijn->lijnsensordata[n] >= thGroenMin)) {
        kleurstatus = 3;
        Serial.println("groen");
      } else if ((lijn->lijnsensordata[n] <= thRoodMax) && (lijn->lijnsensordata[n] >= thRoodMin)) {
        kleurstatus = 4;
        Serial.println("rood");
      }
    }
  } else {
    kleurstatus = 100;
    Serial.println("wit");
  }

  //return kleurstatus;
  Serial.println();
}

void kleurlijnberekening::stuurStatus(int x) {
  kleurstatus = x;
  // code voor sturen hier zetten.
}*/