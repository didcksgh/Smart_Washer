#pragma once

#include "types.h"

class Logger {
public:
    void logState(WasherState state);
    void logStatus(WasherState state, int waterLevel, const ActuatorStatus& actuators);

};