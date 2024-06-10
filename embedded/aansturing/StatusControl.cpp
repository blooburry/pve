#include "StatusControl.h"
#include "Motors.h"

using Status = StatusControl::Status;
using VolgendeBocht = StatusControl::VolgendeBocht;

StatusControl::StatusControl(Motors* motors): 
    motors(motors), 
    status(Status::IDLE),
    prevStatus(Status::IDLE),
    volgendeBocht(VolgendeBocht::NONE),
    proxInstructions({0, 0})
{ }

StatusControl::tick() {
    switch(status) {
        case Status::VOLG_LIJN:
            break;
        case Status::DUW_BLOK:
            motors.setSpeeds(proxInstructions[0], proxInstructions[1]); // doe wat de prox wil dat-ie doet
            break;
    }

    prevStatus = status;
}

StatusControl::proxSetSpeeds(int left, int right) {
    proxInstructions = {left, right};
}