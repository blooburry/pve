#include <Zumo32U4.h>
#include "MqttService.h"
#include <Arduino_Json.h>


Zumo32U4LineSensors lijnsensor;

uint16_t lijnsensorWaardes[3] = { 0, 0, 0 };

void setup() {
  // put your setup code here, to run once:
  lijnsensor.initThreeSensors();
  calibreer();


}

void calibreer() {

  for (uint32_t i = 0; i < 500; i++) {
    lijnsensor.calibrate();
    Serial.print(F("bezig met calibreren"));
    ledGreen(1);
  }
  ledGreen(0);
}

void printNaarSerial() {
  static char ruimte[50];
  sprintf(ruimte, "%4d %4d %4d\n", 
  
  lijnsensorWaardes[0], 
  lijnsensorWaardes[1], 
  lijnsensorWaardes[2]);

  Serial.print(ruimte);

}

void loop() {
  static uint32_t tijd = 0;

  if ((uint32_t) (millis() - tijd) >= 100) {
    tijd = millis();
    lijnsensor.readCalibrated(lijnsensorWaardes);
    printNaarSerial();

    StaticJsonDocument<100> lijnJson; 

    // Fill JSON objects with sensor data
    lijnJson["sensor 1"] = lijnsensorWaardes[0];
    lijnJson["sensor 2"] = lijnsensorWaardes[1];
    lijnJson["sensor 3"] = lijnsensorWaardes[2];


    // Convert JSON objects to strings
    String lijnData;

    serializeJson(lijnJson, lijnData);

    // Send JSON data via MQTT
    mqttService.sendLijnData(lijnData.c_str());


    delay(1000);
  }
  
}