#pragma once

/*** Protocol ***/
enum class Command : byte
{
    /*** LureDevice ***/
    FAN_ON,
    FAN_OFF,
    MOSQUITO_KILLER_ON,
    MOSQUITO_KILLER_OFF,
    OUTLET_OPEN,
    OUTLET_CLOSE,
    /*** Stepper ***/
    VIB,
    POWER_ON,
    INIT,
    Z,
    FLIP,
    XY,
    READY_CAMERA,
    POWER_OFF,
    /*** For Camera ***/
    INIT_CAMERA,
    GLOB_CAMERA,
    LOCAL_CAMERA_1,
    LOCAL_CAMERA_2,
    LOCAL_CAMERA_3,
    /**** Out of range ***/
    OUT_RANGE
};