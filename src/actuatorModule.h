#pragma once

#include "types.h"

class ActuatorModule {
public:
    ActuatorModule();
    void setWaterValve(bool open);
    void setHeater(bool on);
    void setDrainPump(bool on);
    void setMotorSpeed(int spd);
    
    ActuatorStatus getStatus() const;

private:
    ActuatorStatus status;

};