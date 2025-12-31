#include "sensorModule.h"

SensorModule::SensorModule() {
    sensors.doorClosed = true;
    sensors.waterLevel = 0;
    //standard room temperature
    sensors.temperature = 25;
}

void SensorModule::update(int elapsed_ms, WasherState state) {
    int increase = 0;

    if(state == WasherState::Filling) {
        //1 unit is increased by 500 ms
        increase = elapsed_ms/500;

    }

    sensors.waterLevel += increase;

    //water level should be ranged in from 0 to 100
    if(sensors.waterLevel > 100) {
        sensors.waterLevel = 100;

    }

    if(sensors.waterLevel < 0) {
        sensors.waterLevel = 0;

    }
}

bool SensorModule::isDoorClosed() const {
    return sensors.doorClosed;
    
}

int SensorModule::getWaterLevel() const {
    return sensors.waterLevel;
}

int SensorModule::getTemperature() const {
    return sensors.temperature;
}

void SensorModule::setDoorClosed(bool closed) {
    sensors.doorClosed = closed;
}

void SensorModule::setWaterLevel(int level) {
    if(level > 100) {
        level = 100;

    }

    if(level < 0) {
        level = 0;

    }

    sensors.waterLevel = level;
}

void SensorModule::setTemperature(int temperature) {
    sensors.temperature = temperature;
} 
