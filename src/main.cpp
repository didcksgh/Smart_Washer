#include <iostream>
#include <chrono>
#include <thread>

#include "sensorModule.h"
#include "actuatorModule.h"
#include "washerController.h"
#include "logger.h"
#include "washMode.h"

int main() {
    SensorModule sensors;
    ActuatorModule actuators;
    WasherController controller(sensors, actuators);
    Logger logger;

    const int tickMs = 500;

    controller.startCycle(WashMode::Heavy);


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

        WasherState stateBefore = controller.getState();

        sensors.update(elapsedMs, stateBefore);
        controller.update(elapsedMs);

        ActuatorStatus a = actuators.getStatus();
        WasherState stateAfter = controller.getState();
        WashMode mode = controller.getMode();

        logger.logStatus(mode, stateAfter, sensors.getWaterLevel(), a);
        
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