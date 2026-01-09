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

enum class RinsePhase{
        Filling,
        Agitate,
        Drain
};

struct Sensors {
    bool doorClosed;
    int waterLevel; // 0 to 100
    int temperature;
};

struct ActuatorStatus {
    bool valveOpen;
    bool heaterOn;
    bool drainPumpOn;
    int motorSpeed; // 0: off, 1: Low, 2: High
};