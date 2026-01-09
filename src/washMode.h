#pragma once

// Define wash modes for the system.
enum class WashMode {
    Normal,
    Quick,
    Heavy
};

// Define a configuration container for a full cycle
struct WashConfig {
    int targetWaterLevel;
    int rinseTargetWaterLevel;
    int washTimeMs;
    int rinseTimeMs;
    int rinseAgitateTimeMs;
    int spinTimeMs;
    bool heaterOnDuringWash;
};

// Declare a function that maps a WashMode to WashConfig.
WashConfig getWashConfig(WashMode mode);


