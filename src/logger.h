#pragma once

#include "types.h"
#include "washMode.h"

class Logger {
public:
    void logState(WasherState state);
    void logMode(WashMode mode);
    void logStatus(WashMode mode, WasherState state, int waterLevel, const ActuatorStatus& actuators);

};