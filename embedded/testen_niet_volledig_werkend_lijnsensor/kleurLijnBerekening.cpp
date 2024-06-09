#include "kleurLijnBerekening.h"


kleurlijnberekening::kleurlijnberekening() {
  kleurstatus = 0;
}

kleurlijnberekening::~kleurlijnberekening() {
}

void kleurlijnberekening::printkk(unsigned int LSdata[4]) {
  static char ruimte[50];
  sprintf(ruimte, "%4d %4d %4d %4d %4d \n",
          LSdata[0],
          LSdata[1],
          LSdata[2],
          LSdata[3],
          LSdata[4]);
  Serial1.print(ruimte);
}

int kleurlijnberekening::vindLijnKleurStatus(unsigned int LSdata[4]) {
  static int tijds = 0;
  if ((int)(millis() - tijds) >= 500) {
    tijds = millis();
    static char ruimte[50];
    sprintf(ruimte, "%4d %4d %4d %4d %4d \n",
            LSdata[0],
            LSdata[1],
            LSdata[2],
            LSdata[3],
            LSdata[4]);
    Serial1.print(ruimte);
  }

  bool isWhite = false;
  static int tijd = 0;
  if ((int)(millis() - tijd) >= 500) {
    tijd = millis();
    for (int i = 0; i < 5; i++) {
      if ((LSdata[0] && LSdata[1] && LSdata[2] && LSdata[3] && LSdata[4]) < thWit) {
        isWhite = true;
        //Serial1.println(LSdata[2]);
      }
    }



    if (isWhite) {
      Serial1.println("wit");
      kleurstatus = 2000;
      return kleurstatus;
    }
  }
  //Serial1.println("voor de kleurberekening");
  if ((LSdata[0] >= thBruinMin) && (LSdata[1] >= thBruinMin) && (LSdata[2] >= thBruinMin) && (LSdata[3] >= thBruinMin) && (LSdata[4] >= thBruinMin)) {
    kleurstatus = 2;
    //Serial1.println("bruin");
    delay(2000);
    return kleurstatus;
  }

  if (((LSdata[1] >= thGroenMin) && (LSdata[1] <= thGroenMax)) || ((LSdata[2] >= thGroenMin) && (LSdata[2] <= thGroenMax)) || ((LSdata[3] >= thGroenMin) && (LSdata[3] <= thGroenMax))) {
    kleurstatus = 3;
    //Serial1.println("groen");
    return kleurstatus;
  }

  if ((LSdata[1] >= thZwart) || (LSdata[2] >= thZwart) || (LSdata[3] >= thZwart)) {
    kleurstatus = 1;
    //Serial1.println("zwart");
    return kleurstatus;
  }


  if ((LSdata[0] <= thGrijsMax) && (LSdata[0] >= thGrijsMin) && (LSdata[4] > thGrijsMax || LSdata[4] < thGrijsMin)) {
    kleurstatus = 4;
    Serial1.println("grijslinks");
    return kleurstatus;
  } else if ((LSdata[4] <= thGrijsMax) && (LSdata[4] >= thGrijsMin) && (LSdata[0] > thGrijsMax || LSdata[0] < thGrijsMin)) {
    kleurstatus = 4;
    Serial1.println("grijsrechts");
    return kleurstatus;
  } else if ((LSdata[0] <= thGrijsMax) && (LSdata[0] >= thGrijsMin) && (LSdata[4] <= thGrijsMax) && (LSdata[4] >= thGrijsMin)) {
    kleurstatus = 4;
    Serial1.println("grijsstoppen");
    return kleurstatus;
  }
}

int kleurlijnberekening::stuurStatus() {
  return kleurstatus;
}
