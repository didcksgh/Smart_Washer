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
    int getActiveFillTargetWaterLevel() const;

    WasherState getState() const;
    WashMode getMode() const;
    RinsePhase getPhase() const;




private:
    SensorModule& sensors;
    ActuatorModule& actuators;

    WasherState state;
    WashMode mode;
    RinsePhase rinsePhase;

    void enterState(WasherState newState);
    void handleIdle();
    void handleFilling();
    void handleWashing();
    void handleRinsing();
    void handleSpinning();

    int stateElapsedMs;

    int targetWaterLevel;
    int rinseTargetWaterLevel;
    int washTimeMs;
    int rinseAgitateTimeMs;
    int rinseTimeMs;
    int spinTimeMs;
    bool heaterOnDuringWash;
    bool rinsingSecondDrain;
    bool stateChangedThisTick;

    


};