#pragma once
#include "config/config.h"
#include "include/StepperTask.hpp"
#include "include/Camera.hpp"
#include "include/VibMotor.hpp"
#include "include/LureDevice.hpp"

inline void setPin()
{
    /*** Set stepper pins ***/
    /*** X ***/
    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);
    pinMode(X_ENABLE_PIN, OUTPUT);
    digitalWrite(X_ENABLE_PIN, LOW);
    /*** Y ***/
    pinMode(Y_STEP_PIN, OUTPUT);
    pinMode(Y_DIR_PIN, OUTPUT);
    pinMode(Y_ENABLE_PIN, OUTPUT);
    digitalWrite(Y_ENABLE_PIN, LOW);
    /*** Z0 ***/
    pinMode(Z_STEP_PIN, OUTPUT);
    pinMode(Z_DIR_PIN, OUTPUT);
    pinMode(Z_ENABLE_PIN, OUTPUT);
    digitalWrite(Z_ENABLE_PIN, LOW);
    /*** Z1 ***/
    pinMode(E0_ENABLE_PIN, OUTPUT);
    digitalWrite(E0_ENABLE_PIN, LOW);
    /*** Flip ***/
    pinMode(E1_STEP_PIN, OUTPUT);
    pinMode(E1_DIR_PIN, OUTPUT);
    pinMode(E1_ENABLE_PIN, OUTPUT);
    digitalWrite(E1_ENABLE_PIN, LOW);

    /*** Set limit switch pin ***/
    pinMode(X_MIN_PIN, INPUT);
    // pinMode(X_MAX_PIN, INPUT);
    pinMode(Y_MIN_PIN, INPUT);
    // pinMode(Y_MAX_PIN, INPUT);
    pinMode(Z_MIN_PIN, INPUT);
    pinMode(FLIP_LIMIT_PIN, INPUT);
    pinMode(CAMERA_ZOOM_LIMIT, INPUT);
    pinMode(CAMERA_FOCUS_LIMIT, INPUT);

    /*** Set relay pin ***/
    pinMode(POWER_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    pinMode(MOSQUITO_KILLER_PIN, OUTPUT);

    /*** Set light pin ***/
    pinMode(LOCAL_LIGHT_PIN, OUTPUT);
    pinMode(GLOB_LIGHT_PIN, OUTPUT);
}

inline void setStepper()
{
    gStepperX.setMaxSpeed(2000);
    gStepperX.setAcceleration(2000);

    gStepperY.setMaxSpeed(2000);
    gStepperY.setAcceleration(1000);

    gStepperZ.setMaxSpeed(4000);
    gStepperZ.setAcceleration(2000);

    gStepperFlip.setMaxSpeed(600);
    gStepperFlip.setAcceleration(300);
}