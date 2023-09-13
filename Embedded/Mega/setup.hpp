#include "task.hpp"

inline void setPin()
{
    // pinMode(LED, OUTPUT);

    /*** Set stepper pin ***/
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
    pinMode(X_MAX_PIN, INPUT);
    pinMode(Y_MIN_PIN, INPUT);
    pinMode(Y_MAX_PIN, INPUT);
    pinMode(Z_MIN_PIN, INPUT);
    pinMode(FLIP_LIMIT_PIN, INPUT);

    /*** Set relay pin ***/
    pinMode(POWER_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    // pinMode(SERVO_PIN, OUTPUT);
    /*** Set light pin ***/
    pinMode(LOCAL_LIGHT_PIN, OUTPUT);
    pinMode(GLOB_LIGHT_PIN, OUTPUT);
}

inline void setInterrupt()
{
    attachInterrupt(digitalPinToInterrupt(X_MIN_PIN), interruptService_XY, FALLING);
    attachInterrupt(digitalPinToInterrupt(X_MAX_PIN), interruptService_XY, FALLING);
    attachInterrupt(digitalPinToInterrupt(Y_MIN_PIN), interruptService_XY, FALLING);
    attachInterrupt(digitalPinToInterrupt(Y_MAX_PIN), interruptService_XY, FALLING);
    // attachInterrupt(digitalPinToInterrupt(Z_MIN_PIN), interruptService_Z, CHANGE);
    // attachInterrupt(digitalPinToInterrupt(FLIP_LIMIT_PIN), interruptService_Flip, FALLING);
}

inline void setStepper()
{
    stepper_x.setMaxSpeed(2000);
    stepper_x.setAcceleration(2000);

    stepper_y.setMaxSpeed(2000);
    stepper_y.setAcceleration(1000);

    stepper_z.setMaxSpeed(4000);
    stepper_z.setAcceleration(2000);

    stepper_flip.setMaxSpeed(600);
    stepper_flip.setAcceleration(300);
}

// inline void setServo()
// {
//     lure_servo.attach(SERVO_PIN);
//     // lure_servo.write(0);
// }

/*** The bigger the number, the higher the priority. ***/
inline void setTask()
{
    xTaskCreate(task_readSerial, "Task1", 128, NULL, 1, NULL);

    xTaskCreate(task_init, "Task2", 128, NULL, 2, &taskHandle_init);
    vTaskSuspend(taskHandle_init);

    xTaskCreate(task_motorVib, "Task3", 128, NULL, 2, &taskHandle_motorVib);
    vTaskSuspend(taskHandle_motorVib);

    // xTaskCreate(task_stepperZ, "Task4", 128, NULL, 2, &taskHandle_stepperZ);
    // vTaskSuspend(taskHandle_stepperZ);

    xTaskCreate(task_stepperXY, "Task5", 512, NULL, 2, &taskHandle_stepperXY);
    vTaskSuspend(taskHandle_stepperXY);

    xTaskCreate(task_motorFlip, "Task6", 128, NULL, 2, &taskHandle_stepperFlip);
    vTaskSuspend(taskHandle_stepperFlip);
}