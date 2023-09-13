#pragma once

/*** Protocol ***/
enum class Command : byte
{
    VIB,            // 0
    POWER_ON,       // 1
    INIT,           // 2
    Z,              // 3
    FLIP,           // 4
    XY,             // 5
    READY_CAMERA,   // 6
    POWER_OFF,      // 7
    /*** For Camera ***/
    INIT_CAMERA,   // 8
    GLOB_CAMERA,   // 9
    LOCAL_CAMERA   // 10
};