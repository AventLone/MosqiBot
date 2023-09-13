#include "setup.hpp"
// #include "config/config.h"


void setup()
{
    Serial.begin(115200);
    // Serial2.begin(9600);

    setPin();
    // lure_servo.attach(6, 500, 2500);   // 修正脉冲宽度;
    // lure_servo.write(0);

    // delayMicroseconds(1000);   // 以微秒为单位时间，延时1000微秒，即1毫秒

    // setInterrupt();
    // setStepper();
    // setTask();
}

void loop()
{
    /*** Do nothing in loop() ***/
}


/*** Test ***/
// #include <Servo.h>   //加载文件库
// int pos = 0;
// Servo myservo;

// void setup()
// {
//     pinMode(SERVO_PIN, OUTPUT);
// }

// void loop()
// {
//     // digitalWrite(SERVO_PIN, HIGH);
//     // delay(1);
//     // digitalWrite(SERVO_PIN, LOW);
//     // delay(19);
// }
