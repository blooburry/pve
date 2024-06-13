#include "xbee.h"
#include <SimpleVector.h>

Xbee xb; 

void setup() {
  Serial1.begin(9600);
 
}

void loop() {
  xb.checkInput();
  xb.checkButtons();
}
