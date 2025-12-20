#pragma once

//state of the washing machine
enum class WasherState{
    Idle,
    Filling,
    Washing,
    Rinsing,
    Spinning,
    Error

};

//Washer mode
enum class WasherMode {
    Normal
};

struct Sensors {
    bool doorClosed;
    int waterLevel; // 0 to 100
    int temperature;
};

struct ActuatorStatus {
    bool valveOpen;
    bool heaterOn;
    int motorSpped; // 0: off, 1: Low, 2: High
};