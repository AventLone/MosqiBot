#pragma once
#include "config/config.h"
#include <AccelStepper.h>
#include <Arduino_FreeRTOS.h>
// #include "include/LureDevice.hpp"
#include "include/TalkUno.hpp"
#include "include/VibMotor.hpp"
#include <Servo.h>
Servo lure_servo;
bool flag_interrupt = false;

/*** Create stepper object ***/
/***
   "1" means using single-step drive mode,
   which means that each step will only move the stepper motor forward one step.
*/
AccelStepper stepper_x(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepper_y(1, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepper_z(1, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper stepper_flip(1, E1_STEP_PIN, E1_DIR_PIN);

/*** Declare task handel ***/
TaskHandle_t taskHandle_init;
TaskHandle_t taskHandle_motorVib;
TaskHandle_t taskHandle_stepperZ;
TaskHandle_t taskHandle_stepperFlip;
TaskHandle_t taskHandle_stepperXY;

/*** Interruption function triggered by the limit switch ***/
void interruptService_XY()
{
    // if (!flag_interrupt)
    // {
    //     Serial.println("Interrupt");
    // }
    vTaskSuspend(taskHandle_stepperXY);
}
void interruptService_Z()
{
    /***
       If the limit switch is triggered,
       the stepper motor will stop.
    **/
    vTaskSuspend(taskHandle_stepperZ);
}
void interruptService_Flip()
{
    vTaskSuspend(taskHandle_stepperFlip);
}

inline void powerOn()
{
    digitalWrite(POWER_PIN, HIGH);
    vTaskDelay(600 / portTICK_PERIOD_MS);   // Delay 600ms to wait for the switch of relay closing
    configTICK_RATE_HZ;
    _delay_us(100);
}
inline void powerOff()
{
    digitalWrite(POWER_PIN, LOW);
}

void readyCamera();

float distance_x, distance_y;
void task_readSerial(void* parameter)
{
    Command command;
    // UnoTalker uno_talker;
    VibMotor vib_motor;
    unsigned char vib_index;
    for (;;)
    {
        /***
           Read the serial, check if it had any data.
           And Serial.availabel() returns the number
           of bytes of data in the serial port.
        **/
        if (Serial.available())
        {
            Serial.readBytes((char*)&command, sizeof(Command));
            Serial.readBytes((char*)&distance_x, sizeof(float));
            Serial.readBytes((char*)&distance_y, sizeof(float));
            vib_index = static_cast<unsigned char>(distance_x);
            if (int(distance_x) >= MAX_DISTANCE_X || int(distance_y) >= MAX_DISTANCE_Y)
            {
                Serial.println("Out of range!");
                continue;
            }
            switch (command)
            {
                case Command::POWER_ON:
                    powerOn();
                    Serial.println("Task done");
                    break;
                case Command::INIT:
                    vTaskResume(taskHandle_init);
                    break;
                case Command::VIB:
                    vib_motor.activate(vib_index);
                    Serial.println("Task done");
                    break;
                case Command::Z:
                    // vTaskResume(taskHandle_stepperZ);
                    stepper_z.runToNewPosition(115 * z_steps_permm);
                    Serial.println("Task done");
                    break;
                case Command::FLIP:
                    vTaskResume(taskHandle_stepperFlip);
                    break;
                case Command::XY:
                    vTaskResume(taskHandle_stepperXY);
                    break;
                case Command::READY_CAMERA:
                    readyCamera();
                    Serial.println("Task done");
                    break;
                case Command::POWER_OFF:
                    powerOff();
                    Serial.println("Task done");
                    break;
                /*** For Camera ***/
                case Command::INIT_CAMERA:
                    // uno_talker.initCamera();
                    initCamera();
                    Serial.println("Task done");
                    break;
                case Command::GLOB_CAMERA:
                    // uno_talker.globCamera();
                    globCamera();
                    Serial.println("Task done");
                    break;
                case Command::LOCAL_CAMERA:
                    // uno_talker.localCamera();
                    localCamera();
                    Serial.println("Task done");
                    break;
                default:
                    Serial.println("Command format error!");
                    break;
            }
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void readyCamera()
{
    /*** Lure off ***/
    digitalWrite(FAN_PIN, LOW);
    // if (lure_servo.read() != 180)
    // {
    //     for (int pos = lure_servo.read(); pos <= 180; ++pos)   // 从0°到180°运动
    //     {                            // 每次步进一度，实际会有些偏差属正常现象
    //         lure_servo.write(pos);   // 指定舵机转向的角度
    //         vTaskDelay(30 / portTICK_PERIOD_MS);
    //     }
    // }
    lure_servo.write(180);   // 指定舵机转向的角度h
    /***************/

    vTaskDelay(2000 / portTICK_PERIOD_MS);   // Wait until mosquitos falling onto the plate

    // if (lure_servo.read() != 0)
    // {
    //     for (int pos = lure_servo.read(); pos >= 0; --pos)   // From 170° to 0°
    //     {
    //         lure_servo.write(pos);                           // 指定舵机转向的角度
    //         vTaskDelay(30 / portTICK_PERIOD_MS);
    //     }
    // }


    /*** Move Camera to the middel position ***/
    powerOn();
    long target_x = -MAX_DISTANCE_X * STEPS_PER_MM_X / 2;
    long target_y = -MAX_DISTANCE_Y * STEPS_PER_MM_Y / 2;
    while (stepper_x.currentPosition() != target_x || stepper_y.currentPosition() != target_y)
    {
        stepper_x.moveTo(target_x);
        stepper_y.moveTo(target_y);
        stepper_x.run();
        stepper_y.run();
    }
    powerOff();
    /***************************/
}

/*** Use limit switch to initialize the position of the stepper motor ***/
void task_init(void* param)
{
    for (;;)
    {
        flag_interrupt = true;   // Open the interrupt switch to prevent interrupt function send "Interrupt"
        powerOn();
        while (digitalRead(X_MIN_PIN) == LOW)
        {
            stepper_x.setSpeed(2000);
            stepper_x.runSpeed();
        }
        stepper_x.setCurrentPosition(0);
        while (digitalRead(Y_MIN_PIN) == LOW)
        {
            stepper_y.setSpeed(2000);
            stepper_y.runSpeed();
        }
        stepper_y.setCurrentPosition(0);
        while (digitalRead(FLIP_LIMIT_PIN) == LOW)
        {
            stepper_flip.setSpeed(-1300);
            stepper_flip.runSpeed();
        }
        stepper_flip.setCurrentPosition(0);
        while (digitalRead(Z_MIN_PIN) == LOW)
        {
            stepper_z.setSpeed(-2000);
            stepper_z.runSpeed();
        }
        stepper_z.setCurrentPosition(0);
        powerOff();
        flag_interrupt = false;

        /*** Lure on ***/
        // if (lure_servo.read() != 0)
        // {
        //     for (int pos = lure_servo.read(); pos >= 0; --pos)   // From 170° to 0°
        //     {
        //         lure_servo.write(pos);                           // 指定舵机转向的角度
        //         vTaskDelay(30 / portTICK_PERIOD_MS);
        //     }
        // }
        lure_servo.write(0);
        // for (int i = 0; i < 9999; ++i)
        // {
        //     digitalWrite(SERVO_PIN, HIGH);
        //     vTaskDelay(1 / portTICK_PERIOD_MS);
        //     digitalWrite(SERVO_PIN, LOW);
        //     vTaskDelay(19 / portTICK_PERIOD_MS);
        // }
        // lure_servo.write(0);   // 指定舵机转向的角度
        digitalWrite(FAN_PIN, HIGH);
        /******************/

        Serial.println("Task done");
        vTaskSuspend(NULL);
    }
}

void task_motorVib(void* param)
{
    for (;;)
    {
        Serial.println("Task done");
        vTaskSuspend(NULL);
    }
}

void task_stepperZ(void* param)
{
    uint8_t count = 0;
    for (;;)
    {
        stepper_z.runToNewPosition(120 * z_steps_permm);
        Serial.println("Task done");
        vTaskSuspend(NULL);
    }
}

void task_motorFlip(void* param)
{
    const long target_steps = 106 * 62;
    for (;;)
    {
        // localLightOff();
        stepper_z.runToNewPosition(38 * z_steps_permm);
        stepper_flip.runToNewPosition(target_steps);
        Serial.println("Task done");
        vTaskSuspend(NULL);
    }
}

void task_stepperXY(void* param)
{
    for (;;)
    {
        /*** Set the target position ***/
        long target_x = -long(distance_x * STEPS_PER_MM_X);
        long target_y = -long(distance_y * STEPS_PER_MM_Y);

        while (stepper_x.currentPosition() != target_x || stepper_y.currentPosition() != target_y)
        {
            stepper_x.moveTo(target_x);
            stepper_y.moveTo(target_y);
            stepper_x.run();
            stepper_y.run();
        }
        Serial.println("Task done");
        vTaskSuspend(NULL);   // Suspend this task
    }
}
