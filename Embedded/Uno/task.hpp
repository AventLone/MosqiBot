#pragma once
#include "config/config.h"
#include "include/Camera.hpp"
#include <Arduino_FreeRTOS.h>

// #define RECEIVE_PIN_1 9
// #define RECEIVE_PIN_2 12

Camera gCamera;

inline void powerOn()
{
    digitalWrite(POWER_PIN, HIGH);   // Activate relay
    delay(600);
}
inline void powerOff()
{
    digitalWrite(POWER_PIN, LOW);   // Activate relay
}

inline void setPin()
{
    pinMode(POWER_PIN, OUTPUT);   // Relay pin
}

#define WITH_POWER_ON(fun) \
    powerOn();             \
    fun;                   \
    powerOff();

/*** Tasks ***/
TaskHandle_t gTaskHandle_initZoom;
TaskHandle_t gTaskHandle_initFocus;

void task_initZoom(void* param)
{
    for (;;)
    {
        gCamera.initZoom();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
void task_initFocus(void* param)
{
    for (;;)
    {
        gCamera.initFocus();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void task_readSerial(void* param)
{
    for (;;)
    {
        if (Serial.available())
        {
            int command = Serial.read();
            switch (command)
            {
                case Command::GLOBAL:
                    // powerOn();
                    // gCamera.global();
                    // withPowerOn(&gCamera.global);
                    WITH_POWER_ON(gCamera.global());
                    Serial.print("Receive");
                    break;
                case Command::INIT_ZOOM:
                    powerOn();
                    // gCamera.init();
                    vTaskResume(gTaskHandle_initZoom);
                    Serial.print("Receive");
                    break;
                case Command::INIT_FOCUS:
                    // powerOn();
                    vTaskSuspend(gTaskHandle_initZoom);
                    vTaskResume(gTaskHandle_initFocus);
                    // gCamera.init();
                    Serial.print("Receive");
                    break;
                case Command::INIT_OVER:
                    powerOff();
                    vTaskSuspend(gTaskHandle_initFocus);
                    // gCamera.init();
                    Serial.print("Receive");
                    break;
                case Command::LOCAL_1:
                    // powerOn();
                    // gCamera.local(1);
                    WITH_POWER_ON(gCamera.local(1));
                    Serial.print("Receive");
                    break;
                case Command::LOCAL_2:
                    // powerOn();
                    // gCamera.local(2);
                    WITH_POWER_ON(gCamera.local(1));
                    Serial.print("Receive");
                    break;
                case Command::LOCAL_3:
                    // powerOn();
                    // gCamera.local(3);
                    WITH_POWER_ON(gCamera.local(1));
                    Serial.print("Receive");
                    break;
                default:
                    break;
            }
        }
        // powerOff();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}