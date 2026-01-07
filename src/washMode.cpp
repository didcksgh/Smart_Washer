#include "washMode.h"

WashConfig getWashConfig(WashMode mode) {
    WashConfig cfg;

    switch (mode) {
        case WashMode::Normal:
            cfg.targetWaterLevel = 60;
            cfg.washTimeMs = 10000;
            cfg.rinseTimeMs = 5000;
            cfg.spinTimeMs = 3000;
            cfg.heaterOnDuringWash = false;
            break;

        case WashMode::Quick:
            cfg.targetWaterLevel = 40;
            cfg.washTimeMs = 4000;
            cfg.rinseTimeMs = 3000;
            cfg.spinTimeMs = 2000;
            cfg.heaterOnDuringWash = false;
            break;

        case WashMode::Heavy:
            cfg.targetWaterLevel = 80;
            cfg.washTimeMs = 15000;
            cfg.rinseTimeMs = 7000;
            cfg.spinTimeMs = 4000;
            cfg.heaterOnDuringWash = true;
            break;

        default:
            cfg.targetWaterLevel = 60;
            cfg.washTimeMs = 10000;
            cfg.rinseTimeMs = 5000;
            cfg.spinTimeMs = 3000;
            cfg.heaterOnDuringWash = false;
            break;
    }

    return cfg;
}
