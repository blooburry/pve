#include "StatusControl.h"
#include "Motors.h"

using Status = StatusControl::Status;
using VolgendeBocht = StatusControl::VolgendeBocht;

StatusControl::StatusControl(Motors* motors): 
    motors(motors), 
    status(Status::IDLE),
    volgendeBocht(VolgendeBocht::NONE)
{ }