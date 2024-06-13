#ifndef XBEE_H
#define XBEE_H

#include <Zumo32U4.h>
#include <Zumo32U4Buttons.h>

class Xbee {
public:
  Xbee();
  void checkInput();
  void checkButtons();
  void LedGeel();
  void LedGroen();
  void LedRood();
  void XbeePrint(String bericht);
  void ButtonA();
  void ButtonB();
  void ButtonC();

private:
  Zumo32U4ButtonA buttonA;
  Zumo32U4ButtonB buttonB;
  Zumo32U4ButtonC buttonC;
};

#endif  // XBEE_H
