#pragma once

#include "types.h"
#include "sensorModule.h"
#include "actuatorModule.h"

class WasherController {
public:
    WasherController(SensorModule& sensorssRef, ActuatorModule& actuatorsRef);

    void startCycle(WasherMode newMode);
    void update(int elapsedMs);
    WasherState getState() const;




private:
    SensorModule& sensors;
    ActuatorModule& actuators;

    WasherState state;
    WasherMode mode;

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


};