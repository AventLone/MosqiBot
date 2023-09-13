#pragma once

/*** Commands required to send to embedded computer ***/
namespace command
{
enum class Mega : uint8_t
{
    VIB,         // 0
    POWER_ON,    // 1
    INIT,        // 2
    Z,           // 3
    FLIP,        // 4
    XY,          // 5
    POWER_OFF,   // 6

    /*** For Camera ***/
    CAMERA,         // 7
    CAMERA_LOCAL,   // 8
    LOCAL_LIGHT,    // 9
    GLOBAL_LIGHT    // 10
};
}   // namespace command
