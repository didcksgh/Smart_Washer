#include <iostream>
#include <chrono>
#include <thread>

#include "sensorModule.h"
#include "actuatorModule.h"
#include "washerController.h"

static const char* stateToStr(WasherState s) {
    switch (s) {
        case WasherState::Idle:     return "Idle";
        case WasherState::Filling:  return "Filling";
        case WasherState::Washing:  return "Washing";
        case WasherState::Rinsing:  return "Rinsing";
        case WasherState::Spinning: return "Spinning";
        case WasherState::Error:    return "Error";
        default:                    return "Unknown";
    }
}


int main() {
    SensorModule sensors;
    ActuatorModule actuators;
    WasherController controller(sensors, actuators);

    const int tickMs = 500;

    controller.startCycle(WasherMode::Normal);

    using clock = std::chrono::steady_clock;
    auto prev = clock::now();

    bool cycleStarted = false;

    for(int i = 0; i < 500; i++) {

        auto now = clock::now();

        int elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - prev).count();

        prev = now;

        if(elapsedMs < 0) {
            elapsedMs = 0;

        }

        WasherState state = controller.getState();

        sensors.update(elapsedMs, state);
        controller.update(elapsedMs);

        ActuatorStatus a = actuators.getStatus();

        std::cout
            << "state=" << stateToStr(controller.getState())
            << " level=" << sensors.getWaterLevel()
            << " valve=" << a.valveOpen
            << " heater=" << a.heaterOn
            << " motor=" << a.motorSpeed
            << std::endl;

        if (controller.getState() != WasherState::Idle) {
            cycleStarted = true;
        }

        if (cycleStarted && controller.getState() == WasherState::Idle) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(tickMs));


    }
    return 0;




}