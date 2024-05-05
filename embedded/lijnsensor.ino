/* libraries and header files necessary for this program to run properly */
#include <Zumo32U4.h> 
//#include "MqttServicelijn.h"
//#include <Arduino_Json.h>
#include "Calibraties.h"
#include "SerialPrinter.h"

/*  three objects used in this code,
    the 'calibratiemachine' passes lijnsensor as an argument in order to calibrate the linesensors */

Zumo32U4LineSensors lijnsensor;
Calibraties calibratiemachine(lijnsensor);
SerialPrinter printer;

/* the array in which the calibrated sensor values are stored 
*/

uint16_t lijnsensorWaardes[3] = { 0, 0, 0 };

/* this setup function initialises the three line sensors 
    and calibrates them. 
    */
void setup() {
  // put your setup code here, to run once:
  lijnsensor.initThreeSensors();
  calibratiemachine.calibratiereken();


}

/* in the loop function the values found by the sensor
are read into the array and printed to the serial monitor
*/

void loop() {
  static uint32_t tijd = 0; // value used as a timer

  /* this if statement checks the amount time that has elapsed
  since the previous time that values were put
  into the array and printed to the serial monitor. 
  If it has been longer than a tenth of a second then the if statement triggers again
  */
  
  if ((uint32_t) (millis() - tijd) >= 100) {
    tijd = millis();
    lijnsensor.readCalibrated(lijnsensorWaardes);
    printer.printje(lijnsensorWaardes);
  }

  // the code below is currently not necessary but it will be in the future so it is commented out.
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
