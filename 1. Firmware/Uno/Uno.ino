#include "task.hpp"

inline void setupTask()
{
    xTaskCreate(task_initZoom, "Task2", 128, NULL, 1, &gTaskHandle_initZoom);
    vTaskSuspend(gTaskHandle_initZoom);
    xTaskCreate(task_initFocus, "Task2", 128, NULL, 1, &gTaskHandle_initFocus);
    vTaskSuspend(gTaskHandle_initFocus);
    xTaskCreate(task_readSerial, "Task2", 128, NULL, 2, NULL);
}

void setup()
{
    Serial.begin(9600);
    setPin();
    gCamera.set();
    setupTask();

    // powerOn();
    // // gCamera.run(-700, 2000);
    // gCamera.run(800, -1020);
    // // // gCamera.init();
    // // // gCamera.local();
    // powerOff();
}

void loop()
{
    /*** Do Nothing. ***/
}

// void loop()
// {
//     if (Serial.available())
//     {
//         int command = Serial.read();
//         switch (command)
//         {
//             case Command::GLOBAL:
//                 powerOn();
//                 gCamera.global();
//                 Serial.print("Receive");
//                 break;
//             case Command::INIT:
//                 powerOn();
//                 gCamera.init();
//                 Serial.print("Receive");
//                 break;
//             case Command::LOCAL_1:
//                 powerOn();
//                 gCamera.local(1);
//                 Serial.print("Receive");
//                 break;
//             case Command::LOCAL_2:
//                 powerOn();
//                 gCamera.local(2);
//                 Serial.print("Receive");
//                 break;
//             case Command::LOCAL_3:
//                 powerOn();
//                 gCamera.local(3);
//                 Serial.print("Receive");
//                 break;
//             default:
//                 break;
//         }
//     }
//     powerOff();
//     delay(10);
// }