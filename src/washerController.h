#pragma once

#include "types.h"
#include "sensorModule.h"
#include "actuatorModule.h"
#include "washMode.h"

class WasherController {
public:
    WasherController(SensorModule& sensorsRef, ActuatorModule& actuatorsRef);

    void startCycle(WashMode newMode);
    void update(int elapsedMs);
    WasherState getState() const;
    WashMode getMode() const;




private:
    SensorModule& sensors;
    ActuatorModule& actuators;

    WasherState state;
    WashMode mode;

    void enterState(WasherState newState);
    void handleIdle();
    void handleFilling();
    void handleWashing();
    void handleRinsing();
    void handleSpinning();

    int stateElapsedMs;

    int targetWaterLevel;
    int washTimeMs;
    int rinseTimeMs;
    int spinTimeMs;
    bool heaterOnDuringWash;


};