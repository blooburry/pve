#include "KleurLijnBerekening.h"


KleurLijnBerekening::KleurLijnBerekening() {
  kleurstatus = 0;
}

KleurLijnBerekening::~KleurLijnBerekening() {
}

void KleurLijnBerekening::printkk(unsigned int lsData[4]) {
  static char ruimte[50];
  sprintf(ruimte, "%4d %4d %4d %4d %4d \n",
          lsData[0],
          lsData[1],
          lsData[2],
          lsData[3],
          lsData[4]);
  Serial1.print(ruimte);
}

int KleurLijnBerekening::vindLijnKleurStatus(unsigned int lsData[4]) {
  static int tijds = 0;
  if ((int)(millis() - tijds) >= 500) {
    tijds = millis();
    static char ruimte[50];
    sprintf(ruimte, "%4d %4d %4d %4d %4d \n",
            lsData[0],
            lsData[1],
            lsData[2],
            lsData[3],
            lsData[4]);
    Serial1.print(ruimte);
  }

  bool isWhite = false;
  static int tijd = 0;
  if ((int)(millis() - tijd) >= 500) {
    tijd = millis();
    for (int i = 0; i < 5; i++) {
      if ((lsData[0] && lsData[1] && lsData[2] && lsData[3] && lsData[4]) < thWit) {
        isWhite = true;
        //Serial1.println(lsData[2]);
      }
    }



    if (isWhite) {
      Serial1.println("wit");
      kleurstatus = 2000;
      return kleurstatus;
    }
  }
  //Serial1.println("voor de kleurberekening");
  if ((lsData[0] >= thBruinMin) && (lsData[1] >= thBruinMin) && (lsData[2] >= thBruinMin) && (lsData[3] >= thBruinMin) && (lsData[4] >= thBruinMin)) {
    kleurstatus = 2;
    //Serial1.println("bruin");
    delay(2000);
    return kleurstatus;
  }

  if (((lsData[1] >= thGroenMin) && (lsData[1] <= thGroenMax)) || ((lsData[2] >= thGroenMin) && (lsData[2] <= thGroenMax)) || ((lsData[3] >= thGroenMin) && (lsData[3] <= thGroenMax))) {
    kleurstatus = 3;
    //Serial1.println("groen");
    return kleurstatus;
  }

  if ((lsData[1] >= thZwart) || (lsData[2] >= thZwart) || (lsData[3] >= thZwart)) {
    kleurstatus = 1;
    //Serial1.println("zwart");
    return kleurstatus;
  }


  if ((lsData[0] <= thGrijsMax) && (lsData[0] >= thGrijsMin) && (lsData[4] > thGrijsMax || lsData[4] < thGrijsMin)) {
    kleurstatus = 4;
    Serial1.println("grijslinks");
    return kleurstatus;
  } else if ((lsData[4] <= thGrijsMax) && (lsData[4] >= thGrijsMin) && (lsData[0] > thGrijsMax || lsData[0] < thGrijsMin)) {
    kleurstatus = 4;
    Serial1.println("grijsrechts");
    return kleurstatus;
  } else if ((lsData[0] <= thGrijsMax) && (lsData[0] >= thGrijsMin) && (lsData[4] <= thGrijsMax) && (lsData[4] >= thGrijsMin)) {
    kleurstatus = 4;
    Serial1.println("grijsstoppen");
    return kleurstatus;
  }
}

int KleurLijnBerekening::stuurStatus() {
  return kleurstatus;
}
