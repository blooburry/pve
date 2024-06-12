#include <Zumo32U4.h>
#include <SimpleVector.h>

using namespace std;

#ifndef XBEE_H
#define XBEE_H


class Xbee {
private:
  SimpleVector<int> sensorData; //!< vector met alle sensordata
  String input; //!< object die ontvangen data bevat

public:
 /*! constructor */
  Xbee();
  /*! destructor */
  ~Xbee();
  /*! methode die een string print naar de xbee */
  void stuurDataNaarXbee(String);
  /*! methode die ingezonden data uitprint in de xbee */
  String leesDataIn();
};

#endif
