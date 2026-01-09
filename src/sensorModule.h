#pragma once
#include "types.h"

class SensorModule {
public:
    SensorModule();
    
    void update(int elapsed_ms, const ActuatorStatus& actuators, int activeFillTargetWaterLevel);

    bool isDoorClosed() const;
    int getWaterLevel() const;
    int getTemperature() const;

    void setDoorClosed(bool closed);
    void setWaterLevel(int lvl);
    void setTemperature(int temp);


private:
    Sensors sensors;

};

