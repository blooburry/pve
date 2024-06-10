#include <Zumo32U4.h>

#include <SimpleVector.h>

using namespace std;

#ifndef XBEE_H
#define XBEE_H


class Xbee {
private:
  SimpleVector<int> sensorData;
  String input;

public:
  Xbee();
  ~Xbee();
  void stuurDataNaarXbee(String);
  String leesDataIn();
};

#endif
