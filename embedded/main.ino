#include <Wire.h>
#include <Zumo32U4.h>
#include "StatusControl.h"
#include "Motors.h"

Zumo32U4ButtonA buttonA;
Zumo32U4Encoders encoders;
Zumo32U4OLED display;

StatusControl status;
Motors motors(Motors::MEDIUM_SPEED, &status);
int i = 0;

void setup() {
  Wire.begin();
  encoders.init();
  Serial.begin(9600);

  while(!Serial){}
}

void loop() {
  if(i == 0){
    Serial.println(F("===== Program start! ====="));
    Serial.print(F("Battery voltage: "));
    Serial.println(readBatteryMillivolts());
  }

  Serial.print(F("t="));
  Serial.print(i);
  Serial.println(F("s"));

  Serial.print(F("Counts left:"));
  Serial.println(encoders.getCountsLeft());
  Serial.print(F("Counts right:"));
  Serial.println(encoders.getCountsRight());

  // Wacht voor knop druk
  bool buttonPress = buttonA.getSingleDebouncedPress();
  
  if (buttonPress) {
    Serial.println(F("Button A pressed!"));
    status.zetLinks(true);
    motors.update();

    delay(1850);

    status.zetLinks(false);
    motors.update();
    Serial.println(F("Klaar!"));
  }

  motors.update();

  delay(1000);

  i += 1;
}
