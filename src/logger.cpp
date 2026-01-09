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

static const char* modeToStr(WashMode m) {
    switch(m) {
        case WashMode::Normal:
            return "Normal";

        case WashMode::Quick:
            return "Quick";

        case WashMode::Heavy:
            return "Heavy";
        
        default:
            return "Error";

    }


}

static const char* phaseToStr(RinsePhase r) {
    switch (r)
    {
    case RinsePhase::Filling:
        return "Filling";
        break;

    case RinsePhase::Agitate:
        return "Agitate";
        break;
    
    case RinsePhase::Drain:
        return "Drain";
        break;
    
    default:
        return "Error";
        break;
    }
}

void Logger::logState(WasherState state) {
    std::cout << "[STATE] " << stateToStr(state) << std::endl;
}

void Logger::logMode(WashMode mode) {
    std::cout << "[MODE] " << modeToStr(mode) << std::endl;
}

void Logger::logStatus(WashMode mode, WasherState state, RinsePhase phase,
                       int waterLevel,
                       const ActuatorStatus& actuators) {
    if(state == WasherState::Rinsing) {
        std::cout << "[MODE] " << modeToStr(mode)
        << " | "
        << " [STATE] " << stateToStr(state)
        << " | "
        << "[PHASE] " << phaseToStr(phase)
        << " | "
        << " level=" << waterLevel
        << " valve=" << actuators.valveOpen
        << " drain=" << actuators.drainPumpOn
        << " heater=" << actuators.heaterOn
        << " motor=" << actuators.motorSpeed
        << std::endl;

    } else {
    std::cout << "[MODE] " << modeToStr(mode)
    << " | "
    << " [STATE] " << stateToStr(state)
    << " | "
    << " level=" << waterLevel
    << " valve=" << actuators.valveOpen
    << " drain=" << actuators.drainPumpOn
    << " heater=" << actuators.heaterOn
    << " motor=" << actuators.motorSpeed
    << std::endl;
    }
}