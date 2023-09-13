#pragma once
#include <AccelStepper.h>

class Camera
{
public:
    Camera() = default;

    void set();
    // void init();

    void initZoom()
    {
        mStepperZoom.setSpeed(-800);
        mStepperZoom.runSpeed();
    }
    void initFocus()
    {
        mStepperFocus.setSpeed(800);
        mStepperFocus.runSpeed();
    }

    void global()
    {
        mStepperFocus.runToNewPosition(focus_target[0]);
    }
    void local(int local_idx)
    {
        mStepperZoom.runToNewPosition(zoom_target);
        mStepperFocus.runToNewPosition(focus_target[local_idx]);
    }

    void run(long zoom_target, long focus_target);

private:
    AccelStepper mStepperZoom{1, X_STEP_PIN, X_DIR_PIN};
    AccelStepper mStepperFocus{1, Y_STEP_PIN, Y_DIR_PIN};

    const long zoom_target{400};
    const long focus_target[4]{-680, -1830, -1845, -1860};
    // const long focus_target[2] = {-680, -1840};
};

void Camera::set()
{
    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);
    pinMode(Y_STEP_PIN, OUTPUT);
    pinMode(Y_DIR_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);
    digitalWrite(ENABLE_PIN, LOW);

    mStepperZoom.setMaxSpeed(800);
    mStepperZoom.setAcceleration(400);
    mStepperFocus.setMaxSpeed(800);
    mStepperFocus.setAcceleration(400);
}

// void Camera::init()
// {
//     mStepperZoom.runToNewPosition(-100);
//     mStepperFocus.runToNewPosition(100);
//     mStepperZoom.setCurrentPosition(0);
//     mStepperFocus.setCurrentPosition(0);
// }

void Camera::run(long zoom_target, long focus_target)
{
    while (mStepperZoom.currentPosition() != zoom_target || mStepperFocus.currentPosition() != focus_target)
    {
        mStepperZoom.moveTo(zoom_target);
        mStepperFocus.moveTo(focus_target);
        mStepperZoom.run();
        mStepperFocus.run();
    }
}