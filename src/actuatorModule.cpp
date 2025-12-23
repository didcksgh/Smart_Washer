#include "actuatorModule.h"

ActuatorModule::ActuatorModule() {

    status.valveOpen = false;
    status.heaterOn = false;
    status.motorSpeed = 0;

}

void ActuatorModule::setWaterValve(bool open) {
    status.valveOpen = open;
}

void ActuatorModule::setHeater(bool on) {
    status.heaterOn = on;
}

void ActuatorModule::setMotorSpeed(int spd) {
    if(spd > 2) {
        spd = 2;
    }

    if(spd < 0) {
        spd = 0;
    }
    status.motorSpeed = spd;
}

ActuatorStatus ActuatorModule::getStatus() const {
    return status;
}