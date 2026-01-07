#include "washerController.h"

WasherController::WasherController(SensorModule& sensorsRef, ActuatorModule& actuatorsRef)
    : sensors(sensorsRef), actuators(actuatorsRef) {
        state = WasherState::Idle;
        mode = WashMode::Normal;
        stateElapsedMs = 0;

        //default config values in Feature 1
        targetWaterLevel = 60;
        washTimeMs = 10000;
        rinseTimeMs = 5000;
        spinTimeMs = 3000;
        heaterOnDuringWash = false;

}

void WasherController::startCycle(WashMode newMode) {
    if (state == WasherState::Idle) {
        mode = newMode;
        WashConfig cfg = getWashConfig(mode);

        targetWaterLevel = cfg.targetWaterLevel;
        washTimeMs = cfg.washTimeMs;
        rinseTimeMs = cfg.rinseTimeMs;
        spinTimeMs = cfg.spinTimeMs;
        heaterOnDuringWash = cfg.heaterOnDuringWash;

        enterState(WasherState::Filling);
    }
}

void WasherController::update(int elapsedMs) {
    stateElapsedMs += elapsedMs;

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
            handleIdle();
            break;
    }
}

WasherState WasherController::getState() const {
    return state;
}

WashMode WasherController::getMode() const {
    return mode;
}

void WasherController::enterState(WasherState newState) {
    state = newState;
    stateElapsedMs = 0;
}

void WasherController::handleIdle() {
    actuators.setWaterValve(false);
    actuators.setHeater(false);
    actuators.setMotorSpeed(0);

}

void WasherController::handleFilling() {
    actuators.setWaterValve(true);
    actuators.setHeater(false);
    actuators.setMotorSpeed(0);

    if(sensors.getWaterLevel() >= targetWaterLevel) {
        enterState(WasherState::Washing);

    }
}

void WasherController::handleWashing() {
    actuators.setWaterValve(false);
    actuators.setHeater(heaterOnDuringWash);
    actuators.setMotorSpeed(1);

    if(stateElapsedMs >= washTimeMs) {
        enterState(WasherState::Rinsing);

    }
}

void WasherController::handleRinsing() {
    actuators.setWaterValve(false);
    actuators.setHeater(false);
    actuators.setMotorSpeed(1);

    if(stateElapsedMs >= rinseTimeMs) {
        enterState(WasherState::Spinning);

    }
}

void WasherController::handleSpinning() {
    actuators.setWaterValve(false);
    actuators.setHeater(false);
    actuators.setMotorSpeed(2);

    if(stateElapsedMs >= spinTimeMs) {
        enterState(WasherState::Idle);

    }

}
