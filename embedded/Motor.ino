#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Encoders encoders;
Zumo32U4OLED display;

void setup() {

}

void loop() {

  static uint8_t lastDisplayTime;

  if ((uint8_t)(millis() - lastDisplayTime) >= 100)
  {
    lastDisplayTime = millis();

    int16_t countsLeft = encoders.getCountsLeft();
    int16_t countsRight = encoders.getCountsRight();

    // Updates de display van de Zumo
    display.clear();
    display.print(countsLeft);
    display.gotoXY(0, 1);
    display.print(countsRight);

    // Geeft informatie ook naar de serial display
    Serial.print(countsLeft);
    Serial.print(countsRight);
  }

  // Wacht voor knop druk
  bool buttonPress = buttonA.getSingleDebouncedPress();
  
  if (buttonPress) {
    Serial.print("Het beweegt.");
    // Beweeg vooruit
    motors.setSpeeds(200, 200);
    delay(2000);

    // Beweeg Links
    motors.setSpeeds(0, 200);
    delay(2000);
    motors.setSpeeds(0, -200);
    delay(2000);

    // Beweeg Rechts
    motors.setSpeeds(200, 0);
    delay(2000);
    motors.setSpeeds(-200, 0);
    delay(2000);

    // Stop
    motors.setSpeeds(0, 0); // Stop de motoren
    delay(1000); // Wacht een seconde

    // Beweeg achteruit
    motors.setSpeeds(-200, -200);
    delay(2000);

    // Stop
    motors.setSpeeds(0, 0); // Stop de motoren
    delay(1000); // Wacht een seconde
  }
}
