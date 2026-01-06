#include "logger.h"
#include <iostream>

static const char* stateToStr(WasherState state) {
    switch (state)
    {
    case WasherState::Idle:
        return "Idle";
    case WasherState::Filling:
        return "Filling";
    case WasherState::Washing:
        return "Washing";
    case WasherState::Rinsing:
        return "Rinsing";
    case WasherState::Spinning:
        return "Spinning";
    case WasherState::Error:
        return "Error";
    default:
        return "unknown error";
    }
}

void Logger::logState(WasherState state) {
    std::cout << "STATE: " << stateToStr(state) << std::endl;
}

void Logger::logStatus(WasherState state,
                       int waterLevel,
                       const ActuatorStatus& actuators) {
    std::cout << "STATE: "
    << stateToStr(state)
    << " level=  " << waterLevel
    << " valve= " << actuators.valveOpen
    << " heater= " << actuators.heaterOn
    << " motor= " << actuators.motorSpeed
    << std::endl;
}