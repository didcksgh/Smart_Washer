#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <thread>

#include "sensorModule.h"
#include "actuatorModule.h"
#include "washerController.h"
#include "logger.h"
#include "washMode.h"

WashMode readWashModeFromUser() {

    while(true) {
        std::cout << "Select Wash Mode:\n";
        std::cout << "  1. Normal\n";
        std::cout << "  2. Quick\n";
        std::cout << "  3. Heavy\n";
        std::cout << "> ";

        
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            return WashMode::Normal;
        
        case 2:
            return WashMode::Quick;

        case 3:
            return WashMode::Heavy;
        
        default:
            std::cout << "Invalid selection. Try again.\n\n";
        
        }

    }
}

int main() {
    SensorModule sensors;
    ActuatorModule actuators;
    WasherController controller(sensors, actuators);
    Logger logger;

    const int tickMs = 500;

    WashMode selectedMode = readWashModeFromUser();

    controller.startCycle(selectedMode);


    using clock = std::chrono::steady_clock;
    auto prev = clock::now();

    bool cycleStarted = false;


    for(int i = 0; i < 800; i++) {


        //break if the door is not closed and all the water is drained
        if(cycleStarted == true && controller.getState() == WasherState::Error && sensors.getWaterLevel() == 0) {
            break;

        }

        auto now = clock::now();

        int elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - prev).count();

        prev = now;

        if(elapsedMs < 0) {
            elapsedMs = 0;
        }

        controller.update(elapsedMs);

        ActuatorStatus a = actuators.getStatus();
        int activeTarget = controller.getActiveFillTargetWaterLevel();

        sensors.update(elapsedMs, a, activeTarget);
        

        WasherState state = controller.getState();
        WashMode mode = controller.getMode();
        RinsePhase phase = controller.getPhase();
        FaultCode fault = controller.getFault();

        logger.logStatus(mode, state, phase, fault, sensors.getWaterLevel(), a);
        
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