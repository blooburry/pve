#include "xbee.h"
#include <HardwareSerial.h>

Xbee::Xbee() {
  Serial1.begin(9600);      // Start de Xbee communicatie met een baudrate van 9600
  Serial1.setTimeout(800);  // Stel de maximale tijd voor het wachten op de ingestuurde gegevens op 800 ms
}

void Xbee::checkInput() {
  if (Serial1.available() > 0) {          // Controleer of er gegevens zijn gestuurd door de XBee
    String input = Serial1.readString();  // De gegevens worden geinitialiseerd als 'input', als het tekst of numbers zijn
    input.trim();                         // Verwijder witruimte aan het begin en einde van 'input'

    // Controleer de ontvangen tekst en voer de bijbehorende actie uit
    if (input.equals("geel")) {          // Vergelijk input met 'geel'
      LedGeel();                         // Roep de LedGeel() functie aan
    } else if (input.equals("groen")) {  // Vergelijk input met 'groen'
      LedGroen();                        // Roep de LedGroen() functie aan
    } else if (input.equals("rood")) {   // Vergelijk input met 'rood'
      LedRood();                         // Roep de LedRood() functie aan
    }
  }
}

void Xbee::checkButtons() {
  if (buttonA.getSingleDebouncedPress()) {
    ButtonA();  // Controleer of knop A is ingedrukt en voer de bijbehorende actie uit
  } else if (buttonB.getSingleDebouncedPress()) {
    ButtonB();  // Controleer of knop B is ingedrukt en voer de bijbehorende actie uit
  } else if (buttonC.getSingleDebouncedPress()) {
    ButtonC();  // Controleer of knop C is ingedrukt en voer de bijbehorende actie uit
  }
}

void Xbee::LedGeel() {
  ledYellow(1);                     // Zet de gele led aan
  XbeePrint("");                    // Zorgt dat de uitgezonden bericht in de volgende line begint bij de XBee
  XbeePrint("Led geel staat aan");  // Stuur een bericht naar de XBee dat de gele led aanstaat
  delay(1000);                      // Wacht 1 seconde
  ledYellow(0);                     // Zet de gele led uit
}

void Xbee::LedGroen() {
  ledGreen(1);                       // Zet de groene LED aan
  XbeePrint("");                     // Zorg dat de uitgezonden bericht in de volgende line begint bij de XBee
  XbeePrint("Led groen staat aan");  // Stuur een bericht naar de XBee dat de groene led aanstaat
  delay(1000);                       // Wacht 1 seconde
  ledGreen(0);                       // Zet de groene led uit
}

void Xbee::LedRood() {
  ledRed(1);                        // Zet de rode led aan
  XbeePrint("");                    // Zorg dat de uitgezonden bericht in de volgende line begint bij de XBee
  XbeePrint("Led rood staat aan");  // Stuur een bericht naar de XBee dat de rode led aanstaat
  delay(1000);                      // Wacht 1 seconde
  ledRed(0);                        // Zet de rode led uit
}

void Xbee::XbeePrint(String bericht) {
  Serial1.println(bericht);  
}

void Xbee::ButtonA() {
  XbeePrint("");                   // Zorg dat de uitgezonden bericht in de volgende line begint bij de XBee
  XbeePrint("Knop A is gedrukt");  // Stuur een bericht naar de XBee
}

void Xbee::ButtonB() {
  ledYellow(1);                                              // Zet de gele LED aan
  ledGreen(1);                                               // Zet de groene LED aan
  ledRed(1);                                                 // Zet de rode LED aan
  XbeePrint("");                                             // Zorg dat de uitgezonden bericht in de volgende line begint bij de XBee
  XbeePrint("Knop B is gedrukt, dus alle lampen gaan aan");  // Stuur een bericht naar de XBee
  delay(1000);                                               // Wacht 1 seconde
  ledYellow(0);                                              // Zet de gele LED uit
  ledGreen(0);                                               // Zet de groene LED uit
  ledRed(0);                                                 // Zet de rode LED uit
}

void Xbee::ButtonC() {
  static int teller = 0;
  teller +=1;                          // Verhoog de teller met 1 elke keer dat de knop gedrukt is
  Serial1.print(F("Knop C is "));       // Stuur een bericht naar de XBee
  Serial1.print(teller);                // Stuur de waarde van de teller naar de XBee
  Serial1.println(F(" keer gedrukt"));  // Stuur een bericht naar de XBee
}
