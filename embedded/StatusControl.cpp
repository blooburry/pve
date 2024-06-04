#include "StatusControl.h"

// Sets the status of the left motor
void StatusControl::zetLinks(bool status) {
    statusLinks = status;
}

// Sets the status of the right motor
void StatusControl::zetRechts(bool status) {
    statusRechts = status;
}

// Gets the status of the left motor
bool StatusControl::getLinks() {
    return statusLinks;
}

// Gets the status of the right motor
bool StatusControl::getRechts() {
    return statusRechts;
}