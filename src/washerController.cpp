#include "washerController.h"
#include <iostream>

WasherController::WasherController(SensorModule& sensorsRef, ActuatorModule& actuatorsRef)
    : sensors(sensorsRef), actuators(actuatorsRef) {
        state = WasherState::Idle;
        mode = WashMode::Normal;
        rinsePhase = RinsePhase::Drain;
        stateElapsedMs = 0;

        //default config values in Feature 1
        targetWaterLevel = 60;
        washTimeMs = 10000;
        rinseTimeMs = 5000;
        spinTimeMs = 3000;
        rinseTargetWaterLevel = 40;
        rinseAgitateTimeMs = 3000;
        rinsePhase = RinsePhase::Drain;
        heaterOnDuringWash = false;
        rinseCyclesTotal = 2;
        rinseCyclesCompleted = 0;

}

void WasherController::startCycle(WashMode newMode) {

    if ((state == WasherState::Idle || state == WasherState::Error) && sensors.isDoorClosed()) {
        mode = newMode;
        WashConfig cfg = getWashConfig(mode);

        targetWaterLevel = cfg.targetWaterLevel;
        rinseTargetWaterLevel = cfg.rinseTargetWaterLevel;
        washTimeMs = cfg.washTimeMs;
        rinseAgitateTimeMs = cfg.rinseAgitateTimeMs;
        rinseTimeMs = cfg.rinseTimeMs;
        spinTimeMs = cfg.spinTimeMs;
        heaterOnDuringWash = cfg.heaterOnDuringWash;
        rinseCyclesTotal = cfg.rinseCycles;
        rinseCyclesCompleted = 0;

        enterState(WasherState::Filling);
    }
}

void WasherController::update(int elapsedMs) {
    //handle error: Door is not closed
    if(state != WasherState::Idle && state != WasherState::Error ) {
        if(!sensors.isDoorClosed()) {
            enterState(WasherState::Error);
            std::cout<< "Warning! Door is not closed." << std::endl;

        }
    }

    stateElapsedMs += elapsedMs;

    //guard to prevent inifinite loop
    for(int i = 0; i < 5; i++) {
        stateChangedThisTick = false;
        switch (state) {
        case WasherState::Idle:
            handleIdle();
            break;
        case WasherState::Filling:
            handleFilling();
            break;
        case WasherState::Washing:
            handleWashing();
            break;
        case WasherState::Rinsing:
            handleRinsing();
            break;
        case WasherState::Spinning:
            handleSpinning();
            break;
        case WasherState::Error:
            handleError();
            break;
        }

        if(!stateChangedThisTick) {
        break;

        }
    }
    
}

int WasherController::getActiveFillTargetWaterLevel() const {
    if(state == WasherState::Filling) {
        return targetWaterLevel;

    }
    if(state == WasherState::Rinsing && rinsePhase == RinsePhase::Filling) {
        return rinseTargetWaterLevel;

    }
    return -1;
}

WasherState WasherController::getState() const {
    return state;
}

WashMode WasherController::getMode() const {
    return mode;
}

RinsePhase WasherController::getPhase() const {
    return rinsePhase;
}

void WasherController::enterState(WasherState newState) {
    state = newState;
    stateElapsedMs = 0;
    stateChangedThisTick = true;

    if(newState == WasherState::Rinsing) {
        rinsePhase = RinsePhase::Drain;
        rinseCyclesCompleted = 0;

    }

    if(newState == WasherState::Error) {
        rinsePhase = RinsePhase::Drain;
        rinseCyclesCompleted = 0;

    }
}

void WasherController::handleIdle() {
    actuators.setWaterValve(false);
    actuators.setHeater(false);
    actuators.setDrainPump(false);
    actuators.setMotorSpeed(0);

}

void WasherController::handleFilling() {
    actuators.setWaterValve(true);
    actuators.setHeater(false);
    actuators.setDrainPump(false);
    actuators.setMotorSpeed(0);

    if(sensors.getWaterLevel() >= targetWaterLevel) {
        actuators.setWaterValve(false);
        enterState(WasherState::Washing);

    }
}

void WasherController::handleWashing() {
    actuators.setWaterValve(false);
    actuators.setHeater(heaterOnDuringWash);
    actuators.setDrainPump(false);
    actuators.setMotorSpeed(1);

    if(stateElapsedMs >= washTimeMs) {
        enterState(WasherState::Rinsing);

    }
}

void WasherController::handleRinsing() {

    switch (rinsePhase)
    {
    case RinsePhase::Drain:
        actuators.setWaterValve(false);
        actuators.setHeater(false);
        actuators.setDrainPump(true);
        actuators.setMotorSpeed(1);

        if(sensors.getWaterLevel() <= 0) {
            stateElapsedMs = 0;
            actuators.setDrainPump(false);

            if(rinseCyclesCompleted >= rinseCyclesTotal) {
                enterState(WasherState::Spinning);

            }else {
                stateChangedThisTick = true;
                rinsePhase = RinsePhase::Filling;
                
            }

        }

        break;
    
    case RinsePhase::Filling:
        actuators.setWaterValve(true);
        actuators.setHeater(false);
        actuators.setDrainPump(false);
        actuators.setMotorSpeed(0);

        if(sensors.getWaterLevel() >= rinseTargetWaterLevel) {
            actuators.setWaterValve(false);

            stateElapsedMs = 0;
            stateChangedThisTick = true;
            rinsePhase = RinsePhase::Agitate;

        }
        break;

    case RinsePhase::Agitate:
        actuators.setWaterValve(false);
        actuators.setHeater(false);
        actuators.setDrainPump(false);
        actuators.setMotorSpeed(1);

        if(stateElapsedMs >= rinseAgitateTimeMs) {
            stateElapsedMs = 0;
            rinseCyclesCompleted++;
            stateChangedThisTick = true;
            rinsePhase = RinsePhase::Drain;
        }
        break;

    default:
        break;
    }
}

void WasherController::handleSpinning() {
    actuators.setWaterValve(false);
    actuators.setHeater(false);
    actuators.setDrainPump(true);
    actuators.setMotorSpeed(2);

    if(stateElapsedMs >= spinTimeMs) {
        enterState(WasherState::Idle);

    }
}

void WasherController::handleError() {
    actuators.setWaterValve(false);
    actuators.setHeater(false);
    actuators.setMotorSpeed(0);

    if(sensors.getWaterLevel() > 0) {
        actuators.setDrainPump(true);

    }else {
        actuators.setDrainPump(false);
    }
}
