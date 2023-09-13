#pragma once
#include <AccelStepper.h>

/*** Create stepper object ***/
/***
   "1" means using single-step drive mode,
   which means that each step will only move the stepper motor forward one step.
*/
AccelStepper gStepperX(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper gStepperY(1, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper gStepperZ(1, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper gStepperFlip(1, E1_STEP_PIN, E1_DIR_PIN);

// float gDistanceX, gDistanceY;

inline void powerOn()
{
    digitalWrite(POWER_PIN, HIGH);
    delay(600);
}
inline void powerOff()
{
    digitalWrite(POWER_PIN, LOW);
}

void readyCamera()
{
    /*** Move Camera to the middel position ***/
    powerOn();
    long target_x = -MAX_DISTANCE_X * STEPS_PER_MM_X / 2;
    long target_y = -MAX_DISTANCE_Y * STEPS_PER_MM_Y / 2;
    while (gStepperX.currentPosition() != target_x || gStepperY.currentPosition() != target_y)
    {
        gStepperX.moveTo(target_x);
        gStepperY.moveTo(target_y);
        gStepperX.run();
        gStepperY.run();
    }
    powerOff();
}

/*** Use limit switch to initialize the position of the stepper motor ***/
void initDevice()
{
    powerOn();
    while (digitalRead(X_MIN_PIN) == LOW)
    {
        gStepperX.setSpeed(2000);
        gStepperX.runSpeed();
    }
    gStepperX.setCurrentPosition(0);
    while (digitalRead(Y_MIN_PIN) == LOW)
    {
        gStepperY.setSpeed(2000);
        gStepperY.runSpeed();
    }
    gStepperY.setCurrentPosition(0);
    while (digitalRead(FLIP_LIMIT_PIN) == LOW)
    {
        gStepperFlip.setSpeed(-1300);
        gStepperFlip.runSpeed();
    }
    gStepperFlip.setCurrentPosition(0);
    while (digitalRead(Z_MIN_PIN) == LOW)
    {
        gStepperZ.setSpeed(-2000);
        gStepperZ.runSpeed();
    }
    gStepperZ.setCurrentPosition(0);
    powerOff();
}

inline void flipVibPlate()
{
    const long target_steps = 106 * 62;
    gStepperZ.runToNewPosition(38 * z_steps_permm);
    gStepperFlip.runToNewPosition(target_steps);
}

void moveXY(float distance_x, float distance_y)
{
    /*** Set the target position ***/
    long target_x = -static_cast<long>(distance_x * STEPS_PER_MM_X);
    long target_y = -static_cast<long>(distance_y * STEPS_PER_MM_Y);

    while (gStepperX.currentPosition() != target_x || gStepperY.currentPosition() != target_y)
    {
        gStepperX.moveTo(target_x);
        gStepperY.moveTo(target_y);
        gStepperX.run();
        gStepperY.run();
    }
}
