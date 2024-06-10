#include "Xbee.h"

Xbee::Xbee() {}

Xbee::~Xbee() {}

void Xbee::stuurDataNaarXbee(String x) {  //print dingen naar de xbee toe. Je kan de string aanpassen met andere waardes
  Serial1.println(x);
}

String Xbee::leesDataIn() {  //deze functie leest inkomende data binnen van de xbee naar de zumo
  if (Serial1.available() > 0) {
    input = Serial1.readString();
    input.trim();
    return input;
  }
  return input;
}
