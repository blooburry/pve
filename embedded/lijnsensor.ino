#include <Zumo32U4.h>
//#include "MqttServicelijn.h"
//#include <Arduino_Json.h>
#include "Calibraties.h"
#include "SerialPrinter.h"


Zumo32U4LineSensors lijnsensor;
Calibraties calibratiemachine(lijnsensor);
SerialPrinter printer;

uint16_t lijnsensorWaardes[3] = { 0, 0, 0 };

void setup() {
  // put your setup code here, to run once:
  lijnsensor.initThreeSensors();
  calibratiemachine.calibratiereken();


}

void loop() {
  static uint32_t tijd = 0;

  if ((uint32_t) (millis() - tijd) >= 100) {
    tijd = millis();
    lijnsensor.readCalibrated(lijnsensorWaardes);
    printer.printje(lijnsensorWaardes);
  }

   /* StaticJsonDocument<100> lijnJson; 

    // Fill JSON objects with sensor data
    lijnJson["sensor 1"] = lijnsensorWaardes[0];
    lijnJson["sensor 2"] = lijnsensorWaardes[1];
    lijnJson["sensor 3"] = lijnsensorWaardes[2];


    // Convert JSON objects to strings
    String lijnData;

    serializeJson(lijnJson, lijnData);

    // Send JSON data via MQTT
    mqttService.sendLijnData(lijnData.c_str());


    delay(1000); */

  
}
